--Используется учебная БД AdventureWorks2022.
USE AdventureWorks2022
GO

--1.Определить, какие индексы уже созданы в собственной БД. При этом следует использовать разные способы получения информации об индексах.
--Определим индексы, используемые в БД AdventureWorks2022 в используемых далее таблицах.
EXEC sp_helpindex 'Sales.SalesOrderDetail'
EXEC sp_helpindex 'Production.Product'
EXEC sp_helpindex 'Production.ProductSubcategory'
EXEC sp_helpindex 'Production.ProductCategory'

--2. Сформулировать 5-6 сложных запросов SELECT к собственной БД, содержащих соединения таблиц, сортировку, группировку данных.
--Выборка продуктов и соответствующих категорий.
SELECT p.Name AS ProductName, ps.Name AS CategoryName
	FROM Production.Product AS p INNER JOIN Production.ProductSubcategory AS ps ON p.ProductSubcategoryID = ps.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS pc ON ps.ProductCategoryID = pc.ProductCategoryID
ORDER BY ps.Name, p.Name

--Выборка среднего объема продаж по категориям товаров.
SELECT pc.Name AS CategoryName, AVG(od.OrderQty) AS AvgQuantity
	FROM Sales.SalesOrderDetail AS od
	JOIN Production.Product AS p ON od.ProductID = p.ProductID
	JOIN Production.ProductSubcategory AS ps ON p.ProductSubcategoryID = ps.ProductSubcategoryID
	JOIN Production.ProductCategory AS pc ON ps.ProductCategoryID = pc.ProductCategoryID
GROUP BY pc.Name
ORDER BY AvgQuantity DESC

--Выборка продуктов, которые не были заказаны.
SELECT p.ProductID, p.Name AS ProductName
	FROM Production.Product AS p
	LEFT JOIN Sales.SalesOrderDetail AS od ON p.ProductID = od.ProductID
WHERE od.ProductID IS NULL

--Получить среднюю цену продуктов для каждой категории продуктов.
SELECT pc.Name AS Category, AVG(p.ListPrice) AS AvgPrice
	FROM Production.Product p
	JOIN Production.ProductSubcategory psc ON p.ProductSubcategoryID = psc.ProductSubcategoryID
	JOIN Production.ProductCategory pc ON psc.ProductCategoryID = pc.ProductCategoryID
GROUP BY pc.Name

--Подсчитать общее количество заказанных продуктов и сумму продаж для каждого продукта, отсортированных по общей сумме продаж.
SELECT p.Name AS ProductName, SUM(sod.OrderQty) AS TotalQuantity, SUM(sod.OrderQty * sod.UnitPrice) AS TotalSales
	FROM Production.Product p
	JOIN Sales.SalesOrderDetail sod ON p.ProductID = sod.ProductID
GROUP BY p.Name
ORDER BY TotalSales DESC

--Получить список продуктов, их цены и количество, для каждого заказа, отсортированных по номеру заказа.
SELECT sod.SalesOrderID, p.Name AS ProductName, sod.UnitPrice AS Price, sod.OrderQty AS Quantity
	FROM Production.Product p
	JOIN Sales.SalesOrderDetail sod ON p.ProductID = sod.ProductID
ORDER BY sod.SalesOrderID

--3.Попытаться улучшить производительность запросов с помощью создания индексов (после сравнения предполагаемого и фактического плана выполнения).
CREATE UNIQUE NONCLUSTERED INDEX [AK_Product_Name]
ON [Production].[Product] ([Name]);
CREATE UNIQUE NONCLUSTERED INDEX [AK_ProductSubcategory_Name]
ON [Production].[ProductSubcategory] ([Name]);
CREATE UNIQUE NONCLUSTERED INDEX [AK_ProductСategory_Name]
ON [Production].[ProductCategory] ([Name]);
CREATE NONCLUSTERED INDEX [IX_SalesOrderDetail_ProductID]
ON [Sales].[SalesOrderDetail] ([ProductID]);

DROP INDEX Production.Product .AK_Product_Name;
DROP INDEX Production.ProductSubcategory .AK_ProductSubcategory_Name;
DROP INDEX Production.ProductCategory .AK_ProductСategory_Name;
DROP INDEX Sales.SalesOrderDetail .IX_SalesOrderDetail_ProductID;