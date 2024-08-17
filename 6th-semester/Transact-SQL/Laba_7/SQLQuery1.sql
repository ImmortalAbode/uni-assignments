--Используется учебная БД AdventureWorks2022.
USE AdventureWorks2022
GO

--Пример создания простой хранимой процедуры.
CREATE PROC Production.LongLeadProducts
AS
	SELECT Name, ProductNumber
	FROM Production.Product
	WHERE DaysToManufacture >= 1
GO

--Вызов хранимой процедуры LongLeadProducts.
EXEC Production.LongLeadProducts

--Пример изменения хранимой процедуры LongLeadProducts.
ALTER PROC Production.LongLeadProducts
AS
	SELECT Name, ProductNumber, DaysToManufacture
	FROM Production.Product
	WHERE DaysToManufacture >= 1
	ORDER BY DaysToManufacture DESC, Name
GO

EXEC Production.LongLeadProducts

--Определение объектов, которые зависят от хранимой процедуры LongLeadProducts.
EXEC sp_depends @objname = N'Production.LongLeadProducts'

--Пример добавления входного параметра @MinimumLength для хранимой процедуры LongLeadProducts.
ALTER PROC Production.LongLeadProducts
	@MinimumLength int = 1 --defaultvalue
AS
IF (@MinimumLength < 0) --validate
BEGIN
	RAISERROR('Invalid lead time.', 14, 1)
	RETURN
END

SELECT Name, ProductNumber, DaysToManufacture
FROM Production.Product
WHERE DaysToManufacture >= @MinimumLength
ORDER BY DaysToManufacture DESC, Name

--Вызов хранимой процедуры LongLeadProducts с параметром @MinimumuLength = 4.
EXEC Production.LongLeadProducts @MinimumLength=4

--Вызов хранимой процедуры LongLeadProducts с параметром @MinimumLength по позиции.
EXEC Production.LongLeadProducts 4

--Пример использования выходных параметров в хранимых процедурах - выходной параметр @DeptID в процедуре AddDepartment.
CREATE PROC HumanResources.AddDepartment
	@Name nvarchar(50), @GroupName nvarchar(50),
	@DeptID smallint OUTPUT
AS
INSERT INTO HumanResources.Department (Name, GroupName)
	VALUES (@Name, @GroupName)
SET @DeptID = SCOPE_IDENTITY()

--Сохранение результатов выполнения хранимой процедуры AddDepartment с выходным параметром @DeptID.
DECLARE @dept int
EXEC HumanResources.AddDepartment 'Refunds', '', @dept OUTPUT
SELECT @dept

--Изменение хранимой процедуры AddDepartment для возвращения результата выполнения с помощью оператора RETURN.
ALTER PROC HumanResources.AddDepartment
	@Name nvarchar(50), @GroupName nvarchar(50),
	@DeptID smallint OUTPUT
AS
IF ((@Name = '') OR (@GroupName = ''))
	RETURN -1
INSERT INTO HumanResources.Department (Name, GroupName)
VALUES (@Name, @GroupName)
SET @DeptID = SCOPE_IDENTITY()
RETURN 0

--Сохранение результата выполнения хранимой процедуры AddDepartment в локальную переменную @dept или @result.
DECLARE @dept int, @result int
EXEC @result = HumanResources.AddDepartment 'Refunds', '', @dept OUTPUT
IF (@result = 0)
	SELECT @dept
ELSE
	SELECT 'Error during insert'

--Создание скалярной функции SumSold, которая подсчитывает общее количество продаж для определенного продукта в БД AdventureWorks2022 и возвращает общее количество как int.
CREATE FUNCTION Sales.SumSold(@ProductID int) RETURNS int
AS
BEGIN
	DECLARE @ret int
	SELECT @ret = SUM(OrderQty)
	FROM Sales.SalesOrderDetail WHERE ProductID = @ProductID
	IF (@ret IS NULL)
		SET @ret = 0
	RETURN @ret
END

--Пример выполнения оператора SELECT, который возвращает поля ProductID, Name, и результат скалярной функции SumSold для каждого продукта, записанного в базе данных AdventureWorks2022.
SELECT ProductID, Name, Sales.SumSold(ProductID) AS SumSold
FROM Production.Product

--Создание подставляемой табличной фунции, которая возвращает имена подчиненных для определенного менеджера в БД AdventureWorks2022.
CREATE FUNCTION HumanResources.EmployeesForManager
	(@ManagerId int)
	RETURNS TABLE
	AS
	RETURN (
		SELECT FirstName, LastName
		FROM HumanResources.Employee Employee
		INNER JOIN Person.Person Person
		ON Employee.BusinessEntityID = Person.BusinessEntityID
		WHERE ManagerID = @ManagerId)

--Вызов подставляемой табличной функции
--Следующие примеры позволяют получить имена всех служащих для двух менеджеров.
SELECT * FROM HumanResources.EmployeesForManager(3)
-- OR
SELECT * FROM HumanResources.EmployeesForManager(6)

--Пример мультиоператорной табличной функции
/*Следующий пример создает табличную переменную с двумя столбцами, названную
 *@tbl_Employees. Второй столбец изменяется в зависимости от требуемого значения
 *параметра @format*/
CREATE FUNCTION HumanResources. EmployeeNames
	(@format nvarchar(9))
	RETURNS @tbl_Employees TABLE
	(EmployeeID int PRIMARY KEY, [Employee Name] nvarchar(100))
	AS
	BEGIN
		IF (@format = 'SHORTNAME')
			INSERT @tbl_Employees
			SELECT BusinessEntityID, LastName
			FROM HumanResources.vEmployeeDepartment
		ELSE IF (@format = 'LONGNAME')
			INSERT @tbl_Employees
			SELECT BusinessEntityID, (FirstName + ' ' + LastName)
			FROM HumanResources.vEmployeeDepartment
		RETURN
	END

--Вызов мультиоператорной табличной функции
--Вы можете вызвать функцию в выражении FROM вместо таблицы или представления.
--Следующие примеры позволяют получить имя служащего в длинном или коротком формате.
SELECT * FROM HumanResources.EmployeeNames('LONGNAME')
-- OR
SELECT * FROM HumanResources.EmployeeNames('SHORTNAME')

--Пример применения TRY…CATCH
--В этом примере хранимая процедура AddData пытается вставить два значения в таблицу
--TestData. Первый столбец таблицы TestData – целочисленный первичный ключ, а второй
--столбец имеет целочисленный тип данных. Блок TRY…CATCH в хранимой процедуре
--AddData защищает оператор INSERT для таблицы TestData и возвращает номер и
--сообщение об ошибке в части логики блока CATCH, использующей функции
--ERROR_NUMBER и ERROR_MESSAGE.
CREATE TABLE dbo.TableWithKey (ColA int PRIMARY KEY, ColB int)
GO
CREATE PROCEDURE dbo.AddData @a int, @b int
AS
BEGIN TRY
	INSERT INTO TableWithKey VALUES (@a, @b)
END TRY
BEGIN CATCH
	SELECT ERROR_NUMBER() ErrorNumber, ERROR_MESSAGE() [Message]
END CATCH
GO

EXEC dbo.AddData 1, 1
EXEC dbo.AddData 2, 2
EXEC dbo.AddData 1, 3 --violates the primary key
