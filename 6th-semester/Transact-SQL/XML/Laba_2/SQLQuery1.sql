--������������ ������� �� AdventureWorks2022.
USE AdventureWorks2022
GO

/*�������� ������ � �������������� sp_xml_preparedocument*/
--������ 1. �������� ���������������� �������� ��������� ProcessorOrder ��� ������� XML-��������� � ��� ���������� ��� ���������� ���������.
CREATE PROC ProcessorOrder @doc xml
AS
DECLARE @hdoc integer
EXEC sp_xml_preparedocument @hdoc OUTPUT, @doc --��������� ����������� ����������� ������ ���������.
--���������� � ������� 1. ������������ ���������� ������ ��� ������������ XML-��������� ����� ���������.
DROP PROCEDURE ProcessorOrder
CREATE PROC ProcessorOrder @doc xml
AS
BEGIN
	DECLARE @hdoc integer
	EXEC sp_xml_preparedocument @hdoc OUTPUT, @doc
	--��������� ������ �� XML-���������.
	EXEC sp_xml_removedocument @hdoc
END

/*������ 2. ������������� ������� OPENXML*/
DECLARE @idoc INT
DECLARE @xmlData XML
SET @xmlData =
N'<Customer CustomerID="1" CustomerType="S">
    <Order SalesOrderID="43860" Status="5" OrderDate="2001-08-01T00:00:00">
        <OrderDetail ProductID="761" Quantity="2"/>
        <OrderDetail ProductID="770" Quantity="1"/>
    </Order>
</Customer>'
EXEC sp_xml_preparedocument @idoc OUTPUT, @xmlData
SELECT *
	FROM OPENXML (@idoc, '/Customer/Order/OrderDetail')
	WITH (ProductID int, Quantity int)
EXEC sp_xml_removedocument @idoc

/*������ 3. ������������� ������� OPENXML � ���������� �����*/
DECLARE @idoc INT
DECLARE @xmlData XML
SET @xmlData = 
N'<Customer CustomerID="1" CustomerType="S">
    <Order SalesOrderID="43860" Status="5" OrderDate="2001-08-01T00:00:00">
        <OrderDetail ProductID="761" Quantity="2"/>
        <OrderDetail ProductID="770" Quantity="1"/>
    </Order>
</Customer>'
EXEC sp_xml_preparedocument @idoc OUTPUT, @xmlData
SELECT *
	FROM OPENXML (@idoc, '/Customer/Order/OrderDetail', 1)
	WITH (CustomerID int '../../@CustomerID',
		OrderID int '../@SalesOrderID',
		OrderDate datetime '../@OrderDate',
		ProdID int '@ProductID',
		Quantity int)
EXEC sp_xml_removedocument @idoc

/*������ 4. ���������� ������������ ���� � sp_xml_preparedocument � ������������� ������������ ���� � XPath � OPENXML*/
DECLARE @idoc INT
DECLARE @xmlData XML
SET @xmlData =
N'<Customer xmlns="urn:AW_NS" xmlns:o="urn:AW_OrderNS"
	CustomerID="1" CustomerType="S">
		<o:Order SalesOrderID="43860" Status="5"
			OrderDate="2001-08-01T00:00:00">
				<o:OrderDetail ProductID="761" Quantity="2"/>
				<o:OrderDetail ProductID="770" Quantity="1"/>
		</o:Order>
</Customer>'
EXEC sp_xml_preparedocument @idoc OUTPUT, @xmlData,
'<ROOT xmlns:rootNS="urn:AW_NS" xmlns:orderNS="urn:AW_OrderNS" />'
SELECT *
	FROM OPENXML (@idoc, '/rootNS:Customer/orderNS:Order/orderNS:OrderDetail')
	WITH (	OrderID		int			'../@SalesOrderID',
			CustomerID	int			'../../@CustomerID',
			OrderDate	datetime	'../@OrderDate',
			ProdID		int			'@ProductID',
			Quantity	int)
EXEC sp_xml_removedocument @idoc