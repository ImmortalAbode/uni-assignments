--Используется учебная БД AdventureWorks2022.
USE AdventureWorks2022
GO

--PRIMARY KEY
--Пример создания таблицы с PRIMARY KEY
--В разделе CONSTRAINT (ограничение) задаем ограничение PK_Department_DepartmentID
--Создается класетерный индекс 
CREATE TABLE [HumanResources].[Department2](
	[DepartmentID] [smallint] IDENTITY(1,1) NOT NULL,
	[Name] [dbo].[Name] NOT NULL,
	[GroupName] [dbo].[Name] NOT NULL,
	[ModifiedDate] [datetime] NOT NULL,
CONSTRAINT [PK_Department_DepartmentID_2] PRIMARY KEY CLUSTERED
	([DepartmentID] ASC )WITH (IGNORE_DUP_KEY = OFF)
ON [PRIMARY] )

--Когда IGNORE_DUP_KEY установлено в значение OFF,
--SQL Server генерирует ошибку при попытке вставки или обновления данных,
--которые приводят к дублированию значений ключа индекса.

--Когда она установлена в значение ON,
--SQL Server не генерирует ошибку, если попытка вставки или обновления данных приводит к
--дублированию значений ключа индекса. Вместо этого SQL Server просто пропускает такие 
--дублирующиеся ключи и продолжает выполнение операции вставки или обновления.

--DEFAULT
--Таблица с столбцом, например, ВремяИзменения с созданием ограничения DF_Location_ModifiedDate
--DEFAULT - ограничение, задает по умолч. значение атрибута ВремяИзменения 
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
--Это ограничение гарантирует, что значение столбца EndDate больше или
--равно значения столбца StartDate или является null-значением.
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

--Как отключить ограничения
ALTER TABLE [Sales].[SalesOrderHeader] WITH NOCHECK ADD CONSTRAINT
	[FK_SalesOrderHeader_Customer_CustomerID] FOREIGN KEY([CustomerID])
	REFERENCES [Sales].[Customer] ([CustomerID])
--Отключение
ALTER TABLE [Sales].[SalesOrderHeader]
NOCHECK
CONSTRAINT [FK_SalesOrderHeader_Customer_CustomerID]
--Включение
ALTER TABLE [Sales].[SalesOrderHeader]
CHECK
CONSTRAINT [FK_SalesOrderHeader_Customer_CustomerID]



--Реализация триггера INSERT
--В следующем коде демонстрируется создание триггера INSERT insrtWorkOrder на таблице
--Production.WorkOrder базы данных AdventureWorks. Заметьте, что таблица inserted
--используется для работы со значениями, которые вызвали выполнение триггера.
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

--Реализация триггера DELETE
--В следующем коде демонстрируется создание триггера DELETE delCustomer на таблице
--Sales.Customer базы данных AdventureWorks.
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

--Реализация триггера UPDATE
--В следующем коде демонстрируется создание триггера UPDATE updtProductReview на
--таблице Production.ProductReview базы данных AdventureWorks.
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

--Реализация триггера INSTEAD OF
--В следующем коде демонстрируется создание триггера INSTEAD OF delEmployee на таблице
--HumanResources.Employee база данных AdventureWorks.
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

--Отмена вложения:
sp_configure 'nested triggers', 0;

--Триггер не вызывает себя рекурсивно, пока не
--установлена опция базы данных RECURSIVE_TRIGGERS (влияет только на прямую рекурсию)
ALTER DATABASE AdventureWorks SET RECURSIVE_TRIGGERS ON
sp_dboption databasename, 'recursive triggers', True

--Как создать коллекции схем XML
--Чтобы создать коллекцию схемы XML, используйте оператор CREATE XML SCHEMA
--COLLECTION (создание коллекции схемы XML). Синтаксис для оператора CREATE XML
--SCHEMA COLLECTION:
CREATE XML SCHEMA COLLECTION sql_identifier AS Expression

--sql_identifier - Идентификатор Transact-SQL для коллекции схемы XML
--Expression - Значение XML, содержащее один или более документов схемы XML
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
--Удаление коллекции схем XML
DROP XML SCHEMA COLLECTION ResumeSchemaCollection
--Получить информацию о коллекциях схем в базе данных, сделав запрос к представлению системного каталога sys.xml_schema_collections
SELECT * FROM sys.xml_schema_collections
--Получить индивидуальные пространства имен XML, определенные в коллекциях схем базы данных, сделав запрос к представлению системного каталога
--sys.xml_schema_namespaces
SELECT * FROM sys.xml_schema_namespaces
--Просмотреть компоненты XML, определенные в базе данных, с помощью представления системного каталога sys.xml_schema_components
SELECT * FROM sys.xml_schema_components

--Следующий пример показывает, как определить таблицу с использованием xml столбца,
--связанного с коллекцией схем XML ResumeSchemaCollection.
CREATE TABLE HumanResources.EmployeeResume
(EmployeeID int,
Resume xml (ResumeSchemaCollection))

--объявить типизированные xml переменные
DECLARE @resumeDoc xml (ResumeSchemaCollection)

--как назначить типизированное значение xml.
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

--ограничивается ли значение типизированного xml столбца или
--переменной одним документом или может содержать фрагмент, составленный из множества
--документов, с помощью спецификаций DOCUMENT или CONTENT в определении
CREATE TABLE HumanResources.EmployeeResume
(EmployeeID int, Resume xml 
(DOCUMENT ResumeSchemaCollection))