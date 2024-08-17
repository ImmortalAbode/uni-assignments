USE AdventureWorks2022
GO

--CustomerType ��� ����� �� ���� ��������, ��� ��� ���� ������� ����������� � �������.
/*������� � ������ RAW.*/
--������ 1. ��������� XML-��������, ����������� ������ ������ ��� ������������� ����� FOR XML � ������ RAW. 
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW
--������ 2. �� �� ������ � ���� ��������� ������ ���������, ��������� ����� ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW, ELEMENTS
--������ 3. �� �� ����� ������, ��������� �������� �������, ������������ � ������� ����� ROOT � ������� ��� �������� 
--������ ��� ������ ��������������� ��������� ����� RAW.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW('Order'), ROOT('Orders')
--������ 4. ���������� ����� ELENENTS � ������� 3.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW('Order'), ROOT('Orders'), ELEMENTS

/*������� � ������ AUTO*/
--������ 1. ������ � ������ AUTO, ����� ���������� XML ��������, ���������� ������ �������.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO
--������ 2. �� �� ����� ������ � ���� ���������, � �� � ���� ���������, ��������� ����� ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS
--������ 3. ������������� ����� ROOT.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS, ROOT('Orders')

/*������� � ������ EXPLICIT*/
--������ 1. �������� XML, ���������� �������� � �������� ��� �������� SalesOrderID ��� OrderDate.
SELECT 1 AS Tag,
	NULL AS Parent,
	SalesOrderID AS [Invoice!1!InvoiceNo],
	OrderDate AS [Invoice!1!Date!Element]
FROM Sales.SalesOrderHeader
FOR XML EXPLICIT

/*������� � ������ PATH*/
--(������� � AW2022 ���������� �� AW2019)
--������ 1. ������ � ������ PATH, ����� ���������� XML ��������, ���������� ������ ��������.
SELECT pp.BusinessEntityID AS "@EmpID",
    FirstName AS "EmpName/First",
    LastName AS "EmpName/Last"
FROM Person.Person pp INNER JOIN
    HumanResources.Employee ON pp.BusinessEntityID = HumanResources.Employee.BusinessEntityID
ORDER BY pp.BusinessEntityID
FOR XML PATH
--������ 2. ������������� ��������������� ��������� ElementName ������ PATH, ����� �������� �������� �������� ������, ��������� �� ���������.
SELECT pp.BusinessEntityID AS "@EmpID",
    FirstName AS "EmpName/First",
    LastName AS "EmpName/Last"
FROM Person.Person pp INNER JOIN
    HumanResources.Employee ON pp.BusinessEntityID = HumanResources.Employee.BusinessEntityID
ORDER BY pp.BusinessEntityID
FOR XML PATH('Employee')

/*��������� ��� ��������� ��������� XML-����������*/
--������ 1. ������������� ������ AUTO.
--��� ������� �������� ��� ��������, ������ ��� �� ���������� ����� ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO
--���������� ����� ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS
--������ 2. ������������� TYPE ��� ��������� ���� ������ xml � ����������.
-- ������������� ��������� TYPE, ����� ���������� ������� FOR XML.
SELECT Name CategoryName,
	(SELECT Name SubCategoryName
	FROM Production.ProductSubCategory SubCategory
	WHERE SubCategory.ProductCategoryID=Category.ProductCategoryID
	FOR XML AUTO, TYPE, ELEMENTS)
FROM Production.ProductCategory Category
FOR XML AUTO
--������ 3. �������� ������ ��� ������������� ������ EXPLICIT.
--��������� ������ ����������, ��� ����� ���������� ��� ������� ��� ������������� ��������� UNION, ����� �������� �������� Invoice � LineItem.
SELECT 1 AS Tag,
	NULL AS Parent,
	SalesOrderID AS [Invoice!1!InvoiceNo],
	OrderDate AS [Invoice!1!Date!Element],
	NULL AS [LineItem!2!ProductID],
	NULL AS [LineItem!2]
FROM Sales.SalesOrderHeader
UNION ALL
SELECT 2 AS Tag,
	1 AS Parent,
	OrderDetail.SalesOrderID,
	NULL,
	OrderDetail.ProductID,
	Product.Name
FROM Sales.SalesOrderDetail OrderDetail JOIN
	Sales.SalesOrderHeader OrderHeader
	ON OrderDetail.SalesOrderID = OrderHeader.SalesOrderID
		JOIN Production.Product Product
	ON OrderDetail.ProductID = Product.ProductID
ORDER BY [Invoice!1!InvoiceNo], [LineItem!2!ProductID]
FOR XML EXPLICIT
