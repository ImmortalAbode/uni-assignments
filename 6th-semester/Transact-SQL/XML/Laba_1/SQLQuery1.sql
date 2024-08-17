USE AdventureWorks2022
GO

--CustomerType был убран из всех примеров, так как этот столбец отсутствует в таблице.
/*ЗАПРОСЫ В РЕЖИМЕ RAW.*/
--Пример 1. Получение XML-фрагмент, содержащего данные заказа при использовании фразы FOR XML в режиме RAW. 
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW
--Пример 2. Те же данные в виде элементов вместо атрибутов, определяя опцию ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW, ELEMENTS
--Пример 3. Те же самые данные, используя корневой элемент, определенный с помощью опции ROOT и изменяя имя элемента 
--строки при помощи необязательного аргумента опции RAW.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW('Order'), ROOT('Orders')
--Пример 4. Добавление опции ELENENTS к примеру 3.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW('Order'), ROOT('Orders'), ELEMENTS

/*ЗАПРОСЫ В РЕЖИМЕ AUTO*/
--Пример 1. Запрос в режиме AUTO, чтобы возвратить XML фрагмент, содержащий список заказов.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO
--Пример 2. Те же самые данные в виде элементов, а не в виде атрибутов, определяя опцию ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS
--Пример 3. Использование опции ROOT.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS, ROOT('Orders')

/*ЗАПРОСЫ В РЕЖИМЕ EXPLICIT*/
--Пример 1. Создание XML, комбинируя атрибуты и элементы для столбцов SalesOrderID для OrderDate.
SELECT 1 AS Tag,
	NULL AS Parent,
	SalesOrderID AS [Invoice!1!InvoiceNo],
	OrderDate AS [Invoice!1!Date!Element]
FROM Sales.SalesOrderHeader
FOR XML EXPLICIT

/*ЗАПРОСЫ В РЕЖИМЕ PATH*/
--(примеры в AW2022 отличаются от AW2019)
--Пример 1. Запрос в режиме PATH, чтобы возвратить XML фрагмент, содержащий список служащих.
SELECT pp.BusinessEntityID AS "@EmpID",
    FirstName AS "EmpName/First",
    LastName AS "EmpName/Last"
FROM Person.Person pp INNER JOIN
    HumanResources.Employee ON pp.BusinessEntityID = HumanResources.Employee.BusinessEntityID
ORDER BY pp.BusinessEntityID
FOR XML PATH
--Пример 2. Использование дополнительного аргумента ElementName режима PATH, чтобы изменить название элемента строки, принятого по умолчанию.
SELECT pp.BusinessEntityID AS "@EmpID",
    FirstName AS "EmpName/First",
    LastName AS "EmpName/Last"
FROM Person.Person pp INNER JOIN
    HumanResources.Employee ON pp.BusinessEntityID = HumanResources.Employee.BusinessEntityID
ORDER BY pp.BusinessEntityID
FOR XML PATH('Employee')

/*СИНТАКСИС ДЛЯ ПОЛУЧЕНИЯ ВЛОЖЕННЫХ XML-ДОКУМЕНТОВ*/
--Пример 1. Использование режима AUTO.
--Все столбцы выведены как атрибуты, потому что не определена опция ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO
--Добавление опции ELEMENTS.
SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
	ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS
--Пример 2. Использование TYPE для получения типа данных xml в подзапросе.
-- Использование директивы TYPE, чтобы вкладывать запросы FOR XML.
SELECT Name CategoryName,
	(SELECT Name SubCategoryName
	FROM Production.ProductSubCategory SubCategory
	WHERE SubCategory.ProductCategoryID=Category.ProductCategoryID
	FOR XML AUTO, TYPE, ELEMENTS)
FROM Production.ProductCategory Category
FOR XML AUTO
--Пример 3. Вложение таблиц при использовании режима EXPLICIT.
--Следующий пример показывает, как нужно объединить два запроса при использовании оператора UNION, чтобы получить элементы Invoice и LineItem.
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
