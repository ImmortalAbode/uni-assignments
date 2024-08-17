--������������ ������� �� AdventureWorks2022.
USE AdventureWorks2022
GO

/*�������� ������������������� ������������� ������� � ������ AK_Employee_LoginID �� ������� LoginID ��� �������
 *HumanResources.Employee ���� ������ AdwentureWorks2022.
 */
CREATE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)

--�������� ���������� �������.
DROP INDEX HumanResources.Employee .AK_Employee_LoginID;

--���������� ������ � ������������ ������� ������ �����.
CREATE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH (ALLOW_ROW_LOCKS = OFF)

--���������� ������ � ���������� ������ ������.
CREATE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH (ONLINE = ON)

/*�������� ����������� ������������� ������������������� ������� � ������� AK_Employee_LoginID �� ������� LoginID �
 *������� HumanResources.Employee ���� ������ AdventureWorks2022 � ���������� ������ ������������� ���������� ������.
 */
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH (IGNORE_DUP_KEY = ON);

/*�������� ����������� ������������� ������������������� ������� � ������� AK_Employee_LoginID �� ������� LoginID �
 *������� HumanResources.Employee ���� ������ AdventureWorks2022.
 */
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)

/*��������� �������� Gender � NationalIDNumber � ������ � ������ AK_Employee_LoginID �� ������� LoginID � �������
 *HumanResources.Employee ���� ������ AdventureWorks2022.
 */
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
INCLUDE ([Gender], [NationalIDNumber])

--��������� �������� ����� FILLFACTOR � 65% � ��������� �������� ����� PAD_INDEX � ON ��� �������� �������.
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH ( FILLFACTOR = 65, PAD_INDEX = ON)

--��������� ���������� �� �������� ��� ������� Production.Product ��� ������������� ��������� �������� ��������� sp_helpindex.
EXEC sp_helpindex [Production.Product]

--��������� ������� ������������ �� ���� �������� �� ������� Production.Product ��� ������������� sys.dm_db_index_physical_stats.\
SELECT a.index_id, name, avg_fragmentation_in_percent
FROM sys.dm_db_index_physical_stats (DB_ID(N'AdventureWorks2022'),
	OBJECT_ID(N'Production.Product'), NULL, NULL, NULL) AS a
	JOIN sys.indexes AS b ON a.object_id = b.object_id AND a.index_id =
b.index_id;

--��������� ������� ALTER INDEX ��� ������������� ������� AK_Product_Name.
ALTER INDEX AK_Product_Name ON Production.Product
REORGANIZE
--������������� ���� �������� �������.
ALTER INDEX ALL ON Production.Product
REORGANIZE

--��������� ������� ALTER INDEX, ��� ������������ ������� AK_Product_Name ������� Production.Product.
ALTER INDEX AK_Product_Name ON Production.Product
REBUILD

--�������� ���������� ������� XML �� xml ������� � ������� ������� CREATE PRIMARY XML INDEX.
CREATE PRIMARY XML INDEX PXML_ProductModel_CatalogDescription
ON Production.ProductModel (CatalogDescription)

--�������� ������� ���� Path, ������� ���������� ��������� ������, ��������� �����.
CREATE XML INDEX XMLPATH_ProductModel_CatalogDescription
ON Production.ProductModel(CatalogDescription)
USING XML INDEX PXML_ProductModel_CatalogDescription
FOR PATH

--�������� ������� ���� Path, ������� ���������� ��������� ������, ��������� �����.
CREATE XML INDEX XMLPROPERTY_ProductModel_CatalogDescription
ON Production.ProductModel(CatalogDescription)
USING XML INDEX PXML_ProductModel_CatalogDescription
FOR PROPERTY

--�������� ������� ���� Value, ������� ���������� ��������� ������, ��������� �����.
CREATE XML INDEX XMLVALUE_ProductModel_CatalogDescription
ON Production.ProductModel(CatalogDescription)
USING XML INDEX PXML_ProductModel_CatalogDescription
FOR VALUE

