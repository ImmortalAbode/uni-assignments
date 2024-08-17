--������������ ������� �� AdventureWorks2022.
USE AdventureWorks2022
GO

--�������� ������������� HumanResources.vEmployee, ������� ������� �� �������� ���������� ������ � ���� ������ AdwentureWorks2022.
CREATE VIEW [HumanResources].[vEmployee] 
AS 
SELECT 
    e.[BusinessEntityID]
    ,p.[Title]
    ,p.[FirstName]
    ,p.[MiddleName]
    ,p.[LastName]
    ,p.[Suffix]
    ,e.[JobTitle]  
    ,pp.[PhoneNumber]
    ,pnt.[Name] AS [PhoneNumberType]
    ,ea.[EmailAddress]
    ,p.[EmailPromotion]
    ,a.[AddressLine1]
    ,a.[AddressLine2]
    ,a.[City]
    ,sp.[Name] AS [StateProvinceName] 
    ,a.[PostalCode]
    ,cr.[Name] AS [CountryRegionName] 
    ,p.[AdditionalContactInfo]
FROM [HumanResources].[Employee] e
	INNER JOIN [Person].[Person] p
	ON p.[BusinessEntityID] = e.[BusinessEntityID]
    INNER JOIN [Person].[BusinessEntityAddress] bea 
    ON bea.[BusinessEntityID] = e.[BusinessEntityID] 
    INNER JOIN [Person].[Address] a 
    ON a.[AddressID] = bea.[AddressID]
    INNER JOIN [Person].[StateProvince] sp 
    ON sp.[StateProvinceID] = a.[StateProvinceID]
    INNER JOIN [Person].[CountryRegion] cr 
    ON cr.[CountryRegionCode] = sp.[CountryRegionCode]
    LEFT OUTER JOIN [Person].[PersonPhone] pp
    ON pp.BusinessEntityID = p.[BusinessEntityID]
    LEFT OUTER JOIN [Person].[PhoneNumberType] pnt
    ON pp.[PhoneNumberTypeID] = pnt.[PhoneNumberTypeID]
    LEFT OUTER JOIN [Person].[EmailAddress] ea
    ON p.[BusinessEntityID] = ea.[BusinessEntityID]

--��������� ������������� HumanResources.vEmployee � ���� ������ AdventureWorks2022. ��� ������� �� ������������� ��� ���������� � �������� ������.
ALTER VIEW [HumanResources].[vEmployee]
AS
SELECT
    e.[BusinessEntityID] AS [EmployeeID],
    p.[Title],
    p.[FirstName],
    p.[MiddleName],
    p.[LastName],
    p.[Suffix],
    e.[JobTitle],
    pp.[PhoneNumber] AS [Phone],
    ea.[EmailAddress]
FROM [HumanResources].[Employee] e
    INNER JOIN [Person].[Person] p
    ON p.[BusinessEntityID] = e.[BusinessEntityID]
    LEFT OUTER JOIN [Person].[PersonPhone] pp
    ON pp.[BusinessEntityID] = p.[BusinessEntityID]
    LEFT OUTER JOIN [Person].[EmailAddress] ea
    ON p.[BusinessEntityID] = ea.[BusinessEntityID]

--�������� ������������� HumanResources.vEmployee �� ���� ������ AdventureWorks2022.
DROP VIEW [HumanResources].[vEmployee]

--����������� ������ ���� ��������� ������������� � ���� ������ AdventureWorks2022.
SELECT * FROM sys.views

--����������� ������ ������������� HumanResources.vEmployee ���� ������ AdventureWorks.
EXEC sp_helptext 'HumanResources.vEmployee'

--��������� ������ ���� �������� ���� ������, ������� ����� ������ ����������� �� ������� HumanResources.Employee ���� ������ AdventureWorks2022.
SELECT DISTINCT OBJECT_NAME(object_id) AS Name
FROM sys.sql_dependencies
	WHERE referenced_major_id =
	OBJECT_ID(N'AdventureWorks2022.HumanResources.Employee')

--��������� ������������� HumanResources.vEmployee � ���� ������ AdventureWorks2022 � ������ ����������.
ALTER VIEW [HumanResources].[vEmployee]
WITH ENCRYPTION
AS
SELECT
    e.[BusinessEntityID] AS [EmployeeID],
    p.[Title],
    p.[FirstName],
    p.[MiddleName],
    p.[LastName],
    p.[Suffix],
    e.[JobTitle],
    pp.[PhoneNumber] AS [Phone],
    ea.[EmailAddress]
FROM [HumanResources].[Employee] e
    INNER JOIN [Person].[Person] p
    ON p.[BusinessEntityID] = e.[BusinessEntityID]
    LEFT OUTER JOIN [Person].[PersonPhone] pp
    ON pp.[BusinessEntityID] = p.[BusinessEntityID]
    LEFT OUTER JOIN [Person].[EmailAddress] ea
    ON p.[BusinessEntityID] = ea.[BusinessEntityID]

EXEC sp_helptext 'HumanResources.vEmployee'

/*�������� ����������� ����������������� ������� � ������ IX_vStateProvinceCountryRegion 
 *�� ������������� Person.vStateProvinceCountryRegion ���� ������ AdventureWorks2022.*/
CREATE UNIQUE CLUSTERED INDEX [IX_vStateProvinceCountryRegion] ON
[Person].[vStateProvinceCountryRegion]
(
	[StateProvinceID] ASC, [CountryRegionCode] ASC
)
