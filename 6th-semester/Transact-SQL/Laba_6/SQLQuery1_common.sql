--������������ ������� �� AdventureWorks2022.
USE AdventureWorks2022
GO

--PRIMARY KEY
--������ �������� ������� � PRIMARY KEY
--� ������� CONSTRAINT (�����������) ������ ����������� PK_Department_DepartmentID
--��������� ����������� ������ 
CREATE TABLE [HumanResources].[Department2](
	[DepartmentID] [smallint] IDENTITY(1,1) NOT NULL,
	[Name] [dbo].[Name] NOT NULL,
	[GroupName] [dbo].[Name] NOT NULL,
	[ModifiedDate] [datetime] NOT NULL,
CONSTRAINT [PK_Department_DepartmentID_2] PRIMARY KEY CLUSTERED
	([DepartmentID] ASC )WITH (IGNORE_DUP_KEY = OFF)
ON [PRIMARY] )

--����� IGNORE_DUP_KEY ����������� � �������� OFF,
--SQL Server ���������� ������ ��� ������� ������� ��� ���������� ������,
--������� �������� � ������������ �������� ����� �������.

--����� ��� ����������� � �������� ON,
--SQL Server �� ���������� ������, ���� ������� ������� ��� ���������� ������ �������� �
--������������ �������� ����� �������. ������ ����� SQL Server ������ ���������� ����� 
--������������� ����� � ���������� ���������� �������� ������� ��� ����������.

--DEFAULT
--������� � ��������, ��������, �������������� � ��������� ����������� DF_Location_ModifiedDate
--DEFAULT - �����������, ������ �� �����. �������� �������� �������������� 
CREATE TABLE [Production].[Location2](
	[LocationID] [smallint] IDENTITY(1,1) NOT NULL,
	[Name] [dbo].[Name] NOT NULL,
	[CostRate] [smallmoney] NOT NULL CONSTRAINT
	[DF_Location_CostRate2] DEFAULT ((0.00)),
	[Availability] [decimal](8, 2) NOT NULL CONSTRAINT
	[DF_Location_Availability2] DEFAULT ((0.00)),
	[ModifiedDate] [datetime] NOT NULL CONSTRAINT [DF_Location_ModifiedDate2]
	DEFAULT (getdate())
)

--CHECK
--��� ����������� �����������, ��� �������� ������� EndDate ������ ���
--����� �������� ������� StartDate ��� �������� null-���������.
ALTER TABLE [HumanResources].[EmployeeDepartmentHistory] WITH CHECK
	ADD CONSTRAINT [CK_EmployeeDepartmentHistory_EndDate2]
	CHECK (([EndDate]>=[StartDate] OR [EndDate] IS NULL))

--unique
CREATE TABLE [HumanResources].[Employee2](
	[EmployeeID] [int] IDENTITY(1,1) NOT NULL,
	[NationalIDNumber] [nvarchar](15) NOT NULL UNIQUE NONCLUSTERED,
	[ContactID] [int] NOT NULL
)


--FOREIGN KEY
ALTER TABLE [Sales].[SalesOrderHeader] WITH CHECK ADD CONSTRAINT
	[FK_SalesOrderHeader_Customer_CustomerID] FOREIGN KEY([CustomerID])
	REFERENCES [Sales].[Customer] ([CustomerID])

--��� ��������� �����������
ALTER TABLE [Sales].[SalesOrderHeader] WITH NOCHECK ADD CONSTRAINT
	[FK_SalesOrderHeader_Customer_CustomerID] FOREIGN KEY([CustomerID])
	REFERENCES [Sales].[Customer] ([CustomerID])
--����������
ALTER TABLE [Sales].[SalesOrderHeader]
NOCHECK
CONSTRAINT [FK_SalesOrderHeader_Customer_CustomerID]
--���������
ALTER TABLE [Sales].[SalesOrderHeader]
CHECK
CONSTRAINT [FK_SalesOrderHeader_Customer_CustomerID]



--���������� �������� INSERT
--� ��������� ���� ��������������� �������� �������� INSERT insrtWorkOrder �� �������
--Production.WorkOrder ���� ������ AdventureWorks. ��������, ��� ������� inserted
--������������ ��� ������ �� ����������, ������� ������� ���������� ��������.
GO;
CREATE TRIGGER insrtWorkOrder ON Production.WorkOrder
AFTER INSERT AS
BEGIN
	SET NOCOUNT ON;
	INSERT INTO Production.TransactionHistory(
		ProductID,
		ReferenceOrderID,
		TransactionType,
		TransactionDate,
		Quantity,
		ActualCost)
	SELECT inserted.ProductID,
	inserted.WorkOrderID,
	'W', GETDATE(), inserted.OrderQty, 0
	FROM inserted;
END;

--���������� �������� DELETE
--� ��������� ���� ��������������� �������� �������� DELETE delCustomer �� �������
--Sales.Customer ���� ������ AdventureWorks.
GO;
CREATE TRIGGER delCustomer ON Sales.Customer
AFTER DELETE AS
BEGIN
	SET NOCOUNT ON;
	EXEC  msdb.dbo.sp_send_dbmail
		@profile_name = 'AdventureWorksEmailProfile',
		@recipients = 'SalesManagers@Adventure-Works.com',
		@subject = 'Customer Deleted',
		@body = 'A customer has been deleted from the database.';
END;

--���������� �������� UPDATE
--� ��������� ���� ��������������� �������� �������� UPDATE updtProductReview ��
--������� Production.ProductReview ���� ������ AdventureWorks.
GO;
CREATE TRIGGER updtProductReview ON Production.ProductReview
AFTER UPDATE NOT FOR REPLICATION AS
BEGIN
	SET NOCOUNT ON;
	UPDATE Production.ProductReview
		SET Production.ProductReview.ModifiedDate = GETDATE()
	FROM inserted
		WHERE inserted.ProductReviewID = Production.ProductReview.ProductReviewID;
END;

--���������� �������� INSTEAD OF
--� ��������� ���� ��������������� �������� �������� INSTEAD OF delEmployee �� �������
--HumanResources.Employee ���� ������ AdventureWorks.
GO;
CREATE TRIGGER delEmployee ON HumanResources.Employee
INSTEAD OF DELETE NOT FOR REPLICATION AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @DeleteCount int;
	SELECT @DeleteCount = COUNT(*) FROM deleted;
	IF @DeleteCount > 0
	BEGIN
		RAISERROR
		(N'Employees cannot be deleted. They can only be marked as not current.', --Message
		10, -- Severity.
		1); -- State.
		-- Roll back any active or uncommittable transactions
		IF @@TRANCOUNT > 0
		BEGIN
			ROLLBACK TRANSACTION;
		END
	END;
END;

--������ ��������:
sp_configure 'nested triggers', 0;

--������� �� �������� ���� ����������, ���� ��
--����������� ����� ���� ������ RECURSIVE_TRIGGERS (������ ������ �� ������ ��������)
ALTER DATABASE AdventureWorks SET RECURSIVE_TRIGGERS ON
sp_dboption databasename, 'recursive triggers', True

--��� ������� ��������� ���� XML
--����� ������� ��������� ����� XML, ����������� �������� CREATE XML SCHEMA
--COLLECTION (�������� ��������� ����� XML). ��������� ��� ��������� CREATE XML
--SCHEMA COLLECTION:
CREATE XML SCHEMA COLLECTION sql_identifier AS Expression

--sql_identifier - ������������� Transact-SQL ��� ��������� ����� XML
--Expression - �������� XML, ���������� ���� ��� ����� ���������� ����� XML
CREATE XML SCHEMA COLLECTION ResumeSchemaCollection AS 
N'<?xml version="1.0"?>
<xsd:schema targetNamespace="http://schemas.adventure-works.com/EmployeeResume" 
           xmlns:xsd="http://www.w3.org/2001/XMLSchema" 
           xmlns="http://schemas.adventure-works.com/EmployeeResume" 
           elementFormDefault="qualified" 
           attributeFormDefault="unqualified">
  <xsd:element name="resume">
    <xsd:complexType>
      <xsd:sequence>
        <xsd:element name="name" type="xsd:string" minOccurs="1" maxOccurs="1"/>
        <xsd:element name="employmentHistory">
          <xsd:complexType>
            <xsd:sequence minOccurs="1" maxOccurs="unbounded">
              <xsd:element name="employer">
                <xsd:complexType>
                  <xsd:simpleContent>
                    <xsd:extension base="xsd:string">
                      <xsd:attribute name="endDate" use="optional"/>
                    </xsd:extension>
                  </xsd:simpleContent>
                </xsd:complexType>
              </xsd:element>
            </xsd:sequence>
          </xsd:complexType>
        </xsd:element>
      </xsd:sequence>
    </xsd:complexType>
  </xsd:element>
</xsd:schema>';
--�������� ��������� ���� XML
DROP XML SCHEMA COLLECTION ResumeSchemaCollection
--�������� ���������� � ���������� ���� � ���� ������, ������ ������ � ������������� ���������� �������� sys.xml_schema_collections
SELECT * FROM sys.xml_schema_collections
--�������� �������������� ������������ ���� XML, ������������ � ���������� ���� ���� ������, ������ ������ � ������������� ���������� ��������
--sys.xml_schema_namespaces
SELECT * FROM sys.xml_schema_namespaces
--����������� ���������� XML, ������������ � ���� ������, � ������� ������������� ���������� �������� sys.xml_schema_components
SELECT * FROM sys.xml_schema_components

--��������� ������ ����������, ��� ���������� ������� � �������������� xml �������,
--���������� � ���������� ���� XML ResumeSchemaCollection.
CREATE TABLE HumanResources.EmployeeResume
(EmployeeID int,
Resume xml (ResumeSchemaCollection))

--�������� �������������� xml ����������
DECLARE @resumeDoc xml (ResumeSchemaCollection)

--��� ��������� �������������� �������� xml.
INSERT INTO HumanResources.EmployeeResume
VALUES
(1,
'<?xml version="1.0" ?>
<resume
		xmlns="http://schemas.adventure-works.com/EmployeeResume">
	<name>Guy Gilbert</name>
	<employmentHistory>
		<employer endDate="2000-07-07">Northwind Traders</employer>
		<employer>Adventure Works</employer>
	</employmentHistory>
</resume>')

--�������������� �� �������� ��������������� xml ������� ���
--���������� ����� ���������� ��� ����� ��������� ��������, ������������ �� ���������
--����������, � ������� ������������ DOCUMENT ��� CONTENT � �����������
CREATE TABLE HumanResources.EmployeeResume
(EmployeeID int, Resume xml 
(DOCUMENT ResumeSchemaCollection))