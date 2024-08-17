--������������ ������� �� AdventureWorks2022.
USE AdventureWorks2022
GO

--1.����������, ����� ������� ��� ������� � ����������� ��. ��� ���� ������� ������������ ������ ������� ��������� ���������� �� ��������.
--��������� �������, ������������ � �� AdventureWorks2022 � ������������ ����� ��������.
EXEC sp_helpindex 'Sales.SalesOrderDetail'
EXEC sp_helpindex 'Production.Product'
EXEC sp_helpindex 'Production.ProductSubcategory'
EXEC sp_helpindex 'Production.ProductCategory'

--2. �������������� 5-6 ������� �������� SELECT � ����������� ��, ���������� ���������� ������, ����������, ����������� ������.
--������� ��������� � ��������������� ���������.
SELECT p.Name AS ProductName, ps.Name AS CategoryName
	FROM Production.Product AS p INNER JOIN Production.ProductSubcategory AS ps ON p.ProductSubcategoryID = ps.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS pc ON ps.ProductCategoryID = pc.ProductCategoryID
ORDER BY ps.Name, p.Name

--������� �������� ������ ������ �� ���������� �������.
SELECT pc.Name AS CategoryName, AVG(od.OrderQty) AS AvgQuantity
	FROM Sales.SalesOrderDetail AS od
	JOIN Production.Product AS p ON od.ProductID = p.ProductID
	JOIN Production.ProductSubcategory AS ps ON p.ProductSubcategoryID = ps.ProductSubcategoryID
	JOIN Production.ProductCategory AS pc ON ps.ProductCategoryID = pc.ProductCategoryID
GROUP BY pc.Name
ORDER BY AvgQuantity DESC

--������� ���������, ������� �� ���� ��������.
SELECT p.ProductID, p.Name AS ProductName
	FROM Production.Product AS p
	LEFT JOIN Sales.SalesOrderDetail AS od ON p.ProductID = od.ProductID
WHERE od.ProductID IS NULL

--�������� ������� ���� ��������� ��� ������ ��������� ���������.
SELECT pc.Name AS Category, AVG(p.ListPrice) AS AvgPrice
	FROM Production.Product p
	JOIN Production.ProductSubcategory psc ON p.ProductSubcategoryID = psc.ProductSubcategoryID
	JOIN Production.ProductCategory pc ON psc.ProductCategoryID = pc.ProductCategoryID
GROUP BY pc.Name

--���������� ����� ���������� ���������� ��������� � ����� ������ ��� ������� ��������, ��������������� �� ����� ����� ������.
SELECT p.Name AS ProductName, SUM(sod.OrderQty) AS TotalQuantity, SUM(sod.OrderQty * sod.UnitPrice) AS TotalSales
	FROM Production.Product p
	JOIN Sales.SalesOrderDetail sod ON p.ProductID = sod.ProductID
GROUP BY p.Name
ORDER BY TotalSales DESC

--�������� ������ ���������, �� ���� � ����������, ��� ������� ������, ��������������� �� ������ ������.
SELECT sod.SalesOrderID, p.Name AS ProductName, sod.UnitPrice AS Price, sod.OrderQty AS Quantity
	FROM Production.Product p
	JOIN Sales.SalesOrderDetail sod ON p.ProductID = sod.ProductID
ORDER BY sod.SalesOrderID

--3.���������� �������� ������������������ �������� � ������� �������� �������� (����� ��������� ��������������� � ������������ ����� ����������).
CREATE UNIQUE NONCLUSTERED INDEX [AK_Product_Name]
ON [Production].[Product] ([Name]);
CREATE UNIQUE NONCLUSTERED INDEX [AK_ProductSubcategory_Name]
ON [Production].[ProductSubcategory] ([Name]);
CREATE UNIQUE NONCLUSTERED INDEX [AK_Product�ategory_Name]
ON [Production].[ProductCategory] ([Name]);
CREATE NONCLUSTERED INDEX [IX_SalesOrderDetail_ProductID]
ON [Sales].[SalesOrderDetail] ([ProductID]);

DROP INDEX Production.Product .AK_Product_Name;
DROP INDEX Production.ProductSubcategory .AK_ProductSubcategory_Name;
DROP INDEX Production.ProductCategory .AK_Product�ategory_Name;
DROP INDEX Sales.SalesOrderDetail .IX_SalesOrderDetail_ProductID;