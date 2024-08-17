--Используется учебная БД AdventureWorks2022.
USE AdventureWorks2022
GO

/*Создание некластеризованного возрастающего индекса с именем AK_Employee_LoginID по столбцу LoginID для таблицы
 *HumanResources.Employee базы данных AdwentureWorks2022.
 */
CREATE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)

--Удаление созданного индекса.
DROP INDEX HumanResources.Employee .AK_Employee_LoginID;

--Предыдущий пример с выключенными замками уровня строк.
CREATE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH (ALLOW_ROW_LOCKS = OFF)

--Предыдущий пример с включенной опцией онлайн.
CREATE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH (ONLINE = ON)

/*Создание уникального возрастающего некластеризованного индекса с имененм AK_Employee_LoginID по столбцу LoginID в
 *таблице HumanResources.Employee базы данных AdventureWorks2022 с включенной опцией игнорирования дубликатов ключей.
 */
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH (IGNORE_DUP_KEY = ON);

/*Создание уникального возрастающего некластеризованного индекса с имененм AK_Employee_LoginID по столбцу LoginID в
 *таблице HumanResources.Employee базы данных AdventureWorks2022.
 */
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)

/*Включение столбцов Gender и NationalIDNumber в индекс с именем AK_Employee_LoginID по столбцу LoginID в таблице
 *HumanResources.Employee базы данных AdventureWorks2022.
 */
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
INCLUDE ([Gender], [NationalIDNumber])

--Установка значения опции FILLFACTOR в 65% и установка значения опции PAD_INDEX в ON при создании индекса.
CREATE UNIQUE NONCLUSTERED INDEX [AK_Employee_LoginID]
ON [HumanResources].[Employee] ( [LoginID] ASC)
WITH ( FILLFACTOR = 65, PAD_INDEX = ON)

--Получение информации об индексах для таблицы Production.Product при использовании системной хранимой процедуры sp_helpindex.
EXEC sp_helpindex [Production.Product]

--Получение средней фрагментации по всем индексам на таблицу Production.Product при использовании sys.dm_db_index_physical_stats.\
SELECT a.index_id, name, avg_fragmentation_in_percent
FROM sys.dm_db_index_physical_stats (DB_ID(N'AdventureWorks2022'),
	OBJECT_ID(N'Production.Product'), NULL, NULL, NULL) AS a
	JOIN sys.indexes AS b ON a.object_id = b.object_id AND a.index_id =
b.index_id;

--Синтаксис команды ALTER INDEX для реорганизации индекса AK_Product_Name.
ALTER INDEX AK_Product_Name ON Production.Product
REORGANIZE
--Реорганизация всех индексов таблицы.
ALTER INDEX ALL ON Production.Product
REORGANIZE

--Синтаксис команды ALTER INDEX, для перестроения индекса AK_Product_Name таблицы Production.Product.
ALTER INDEX AK_Product_Name ON Production.Product
REBUILD

--Создание первичного индекса XML по xml столбцу с помощью команды CREATE PRIMARY XML INDEX.
CREATE PRIMARY XML INDEX PXML_ProductModel_CatalogDescription
ON Production.ProductModel (CatalogDescription)

--Создание индекса типа Path, который использует первичный индекс, созданный ранее.
CREATE XML INDEX XMLPATH_ProductModel_CatalogDescription
ON Production.ProductModel(CatalogDescription)
USING XML INDEX PXML_ProductModel_CatalogDescription
FOR PATH

--Создание индекса типа Path, который использует первичный индекс, созданный ранее.
CREATE XML INDEX XMLPROPERTY_ProductModel_CatalogDescription
ON Production.ProductModel(CatalogDescription)
USING XML INDEX PXML_ProductModel_CatalogDescription
FOR PROPERTY

--Создание индекса типа Value, который использует первичный индекс, созданный ранее.
CREATE XML INDEX XMLVALUE_ProductModel_CatalogDescription
ON Production.ProductModel(CatalogDescription)
USING XML INDEX PXML_ProductModel_CatalogDescription
FOR VALUE

