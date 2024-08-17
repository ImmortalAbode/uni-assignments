--������������ ������� �� AdventureWorks2022.
USE AdventureWorks2022
GO

--������ �������� ������� �������� ���������.
CREATE PROC Production.LongLeadProducts
AS
	SELECT Name, ProductNumber
	FROM Production.Product
	WHERE DaysToManufacture >= 1
GO

--����� �������� ��������� LongLeadProducts.
EXEC Production.LongLeadProducts

--������ ��������� �������� ��������� LongLeadProducts.
ALTER PROC Production.LongLeadProducts
AS
	SELECT Name, ProductNumber, DaysToManufacture
	FROM Production.Product
	WHERE DaysToManufacture >= 1
	ORDER BY DaysToManufacture DESC, Name
GO

EXEC Production.LongLeadProducts

--����������� ��������, ������� ������� �� �������� ��������� LongLeadProducts.
EXEC sp_depends @objname = N'Production.LongLeadProducts'

--������ ���������� �������� ��������� @MinimumLength ��� �������� ��������� LongLeadProducts.
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

--����� �������� ��������� LongLeadProducts � ���������� @MinimumuLength = 4.
EXEC Production.LongLeadProducts @MinimumLength=4

--����� �������� ��������� LongLeadProducts � ���������� @MinimumLength �� �������.
EXEC Production.LongLeadProducts 4

--������ ������������� �������� ���������� � �������� ���������� - �������� �������� @DeptID � ��������� AddDepartment.
CREATE PROC HumanResources.AddDepartment
	@Name nvarchar(50), @GroupName nvarchar(50),
	@DeptID smallint OUTPUT
AS
INSERT INTO HumanResources.Department (Name, GroupName)
	VALUES (@Name, @GroupName)
SET @DeptID = SCOPE_IDENTITY()

--���������� ����������� ���������� �������� ��������� AddDepartment � �������� ���������� @DeptID.
DECLARE @dept int
EXEC HumanResources.AddDepartment 'Refunds', '', @dept OUTPUT
SELECT @dept

--��������� �������� ��������� AddDepartment ��� ����������� ���������� ���������� � ������� ��������� RETURN.
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

--���������� ���������� ���������� �������� ��������� AddDepartment � ��������� ���������� @dept ��� @result.
DECLARE @dept int, @result int
EXEC @result = HumanResources.AddDepartment 'Refunds', '', @dept OUTPUT
IF (@result = 0)
	SELECT @dept
ELSE
	SELECT 'Error during insert'

--�������� ��������� ������� SumSold, ������� ������������ ����� ���������� ������ ��� ������������� �������� � �� AdventureWorks2022 � ���������� ����� ���������� ��� int.
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

--������ ���������� ��������� SELECT, ������� ���������� ���� ProductID, Name, � ��������� ��������� ������� SumSold ��� ������� ��������, ����������� � ���� ������ AdventureWorks2022.
SELECT ProductID, Name, Sales.SumSold(ProductID) AS SumSold
FROM Production.Product

--�������� ������������� ��������� ������, ������� ���������� ����� ����������� ��� ������������� ��������� � �� AdventureWorks2022.
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

--����� ������������� ��������� �������
--��������� ������� ��������� �������� ����� ���� �������� ��� ���� ����������.
SELECT * FROM HumanResources.EmployeesForManager(3)
-- OR
SELECT * FROM HumanResources.EmployeesForManager(6)

--������ ����������������� ��������� �������
/*��������� ������ ������� ��������� ���������� � ����� ���������, ���������
 *@tbl_Employees. ������ ������� ���������� � ����������� �� ���������� ��������
 *��������� @format*/
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

--����� ����������������� ��������� �������
--�� ������ ������� ������� � ��������� FROM ������ ������� ��� �������������.
--��������� ������� ��������� �������� ��� ��������� � ������� ��� �������� �������.
SELECT * FROM HumanResources.EmployeeNames('LONGNAME')
-- OR
SELECT * FROM HumanResources.EmployeeNames('SHORTNAME')

--������ ���������� TRY�CATCH
--� ���� ������� �������� ��������� AddData �������� �������� ��� �������� � �������
--TestData. ������ ������� ������� TestData � ������������� ��������� ����, � ������
--������� ����� ������������� ��� ������. ���� TRY�CATCH � �������� ���������
--AddData �������� �������� INSERT ��� ������� TestData � ���������� ����� �
--��������� �� ������ � ����� ������ ����� CATCH, ������������ �������
--ERROR_NUMBER � ERROR_MESSAGE.
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
