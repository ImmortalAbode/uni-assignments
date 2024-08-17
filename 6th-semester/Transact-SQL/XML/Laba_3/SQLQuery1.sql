/*Выполнение примеров для каждого метода типа данных XML, приведенного на сайте:
https://docs.microsoft.com/ru-ru/sql/t-sql/xml/xml-data-type-methods?view=sql-server-ver15 
Примеры адаптированы под используемую БД AdwentureWorks2022*/

--Используется учебная БД AdventureWorks2022.
USE AdventureWorks2022
GO

/*Примеры использования метода query() для типа данных xml*/
--A. Использование метода query() для переменной типа xml.
DECLARE @myDoc XML  
SET @myDoc = 
'<Root>  
	<ProductDescription ProductID="1" ProductName="Road Bike">  
		<Features>  
			<Warranty>1 year parts and labor</Warranty>  
			<Maintenance>3 year parts and labor extended maintenance is available</Maintenance>  
		</Features>  
	</ProductDescription>  
</Root>'  
SELECT @myDoc.query('/Root/ProductDescription/Features')
--B. Использование метода query() для столбца типа XML.
SELECT CatalogDescription.query('  
	declare namespace PD="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
		<Product ProductModelID="{ /PD:ProductDescription[1]/@ProductModelID }" />  
') as Result  
FROM Production.ProductModel
where CatalogDescription.exist('  
	declare namespace PD="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
	declare namespace wm="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelWarrAndMain";  
		 /PD:ProductDescription/PD:Features/wm:Warranty ') = 1
--Замечание к B. Использование WITH XMLNAMESPACES для первоначального определения префиксов и использования их в запросе.
WITH XMLNAMESPACES 
(  
   'http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription' AS PD,  
   'http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelWarrAndMain' AS WM
)  
SELECT CatalogDescription.query('<Product ProductModelID="{ /PD:ProductDescription[1]/@ProductModelID }" />')
       AS Result  
FROM Production.ProductModel  
WHERE CatalogDescription.exist('/PD:ProductDescription/PD:Features/WM:Warranty ') = 1;





/*Примеры использования метода value() для типа данных xml*/
--A. Использование метода value() над переменной типа xml.
DECLARE @myDoc XML  
DECLARE @ProdID INT  
SET @myDoc = 
'<Root>  
	<ProductDescription ProductID="1" ProductName="Road Bike">  
		<Features>  
			<Warranty>1 year parts and labor</Warranty>  
			<Maintenance>3 year parts and labor extended maintenance is available</Maintenance>  
		</Features>  
	</ProductDescription>  
</Root>'  
SET @ProdID =  @myDoc.value('(/Root/ProductDescription/@ProductID)[1]', 'int' )  
SELECT @ProdID
--B. Использование метода value() для извлечения значения из столбца типа xml.
SELECT CatalogDescription.value('             
    declare namespace PD="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";             
       (/PD:ProductDescription/@ProductModelID)[1]', 'int') AS Result             
FROM Production.ProductModel             
WHERE CatalogDescription IS NOT NULL             
ORDER BY Result DESC
--С. Использование методов value() и exist() для извлечения значений из столбца типа xml.
SELECT CatalogDescription.value('  
     declare namespace PD="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
           (/PD:ProductDescription/@ProductModelID)[1] ', 'int') AS Result  
FROM  Production.ProductModel  
WHERE CatalogDescription.exist('  
     declare namespace PD="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
     declare namespace wm="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelWarrAndMain";  
     /PD:ProductDescription/PD:Features/wm:Warranty ') = 1
--D. Использование метода exist() вместо метода value() для увеличение производительности сравнения с реляционным значением.
CREATE TABLE T (c1 INT, c2 VARCHAR(10), c3 XML)  
GO 
INSERT INTO T (c1, c2, c3)
VALUES (1, 'value1', '<root a="1"/>');
DELETE FROM T
	WHERE c1 = 1
SELECT c1, c2, c3   
FROM T  
WHERE c3.value( '(/root[@a=sql:column("c1")]/@a)[1]', 'integer') = c1  
GO





/*Примеры использования метода exist() для типа данных xml*/
--Пример: указание метода exist() по отношению к переменной типа xml.
DECLARE @x XML;  
DECLARE @f BIT;  
SET @x = '<root Somedate = "2002-01-01Z"/>';  
SET @f = @x.exist('/root[(@Somedate cast as xs:date?) eq xs:date("2002-01-01Z")]');  
SELECT @f;
--Аналогичный пример.
DECLARE @x XML;  
DECLARE @f BIT;  
SET @x = '<Somedate>2002-01-01Z</Somedate>';  
SET @f = @x.exist('/Somedate[(text()[1] cast as xs:date ?) = xs:date("2002-01-01Z") ]')  
SELECT @f;

--Пример: применение метода exist() по отношению к типизированной переменной xml.
DECLARE @x XML (Production.ManuInstructionsSchemaCollection);  
SELECT @x=Instructions  
FROM Production.ProductModel  
WHERE ProductModelID=67;  
--SELECT @x  
DECLARE @f INT;  
SET @f = @x.exist(' declare namespace AWMI="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions";  
    /AWMI:root/AWMI:Location[@LocationID=50]  
');  
SELECT @f;

--Пример: применение метода exist() по отношению к столбцу типа xml.
SELECT ProductModelID, CatalogDescription.query('  
declare namespace pd="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
    <Product   
        ProductModelID= "{ sql:column("ProductModelID") }"   
        />  
') AS Result  
FROM Production.ProductModel  
WHERE CatalogDescription.exist('  
    declare namespace  pd="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
     /pd:ProductDescription[not(pd:Specifications)]'  
    ) = 1;
--Замечание относительно указания пространств имен.
WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription' AS pd)  
SELECT ProductModelID, CatalogDescription.query('  
    <Product   
        ProductModelID= "{ sql:column("ProductModelID") }"   
        />  
') AS Result  
FROM Production.ProductModel  
WHERE CatalogDescription.exist('  
     /pd:ProductDescription[not(pd:Specifications)]'  
    ) = 1;





/*Примеры использования метода modify() для типа данных xml*/
--Применение оператора insert в методе XQuery modify.
DECLARE @myDoc XML;         
SET @myDoc = '<Root>         
    <ProductDescription ProductID="1" ProductName="Road Bike">         
        <Features>         
        </Features>         
    </ProductDescription>         
</Root>'  ;       
SELECT @myDoc;     
-- insert first feature child (no need to specify as first or as last)         
SET @myDoc.modify('         
insert <Maintenance>3 year parts and labor extended maintenance is available</Maintenance>   
into (/Root/ProductDescription/Features)[1]') ;  
SELECT @myDoc ;        
-- insert second feature. We want this to be the first in sequence so use 'as first'         
SET @myDoc.modify('         
insert <Warranty>1 year parts and labor</Warranty>          
as first         
into (/Root/ProductDescription/Features)[1]         
')  ;       
SELECT @myDoc  ;       
-- insert third feature child. This one is the last child of <Features> so use 'as last'         
SELECT @myDoc         
SET @myDoc.modify('         
insert <Material>Aluminium</Material>          
as last         
into (/Root/ProductDescription/Features)[1]         
')         
SELECT @myDoc ;        
-- Add fourth feature - this time as a sibling (and not a child)         
-- 'after' keyword is used (instead of as first or as last child)         
SELECT @myDoc  ;       
SET @myDoc.modify('         
insert <BikeFrame>Strong long lasting</BikeFrame>   
after (/Root/ProductDescription/Features/Material)[1]         
')  ;       
SELECT @myDoc;  
GO

--Применение оператора delete в методе XQuery modify.
DECLARE @myDoc XML  
SET @myDoc = '<?Instructions for=TheWC.exe ?>   
<Root>  
 <!-- instructions for the 1st work center -->  
<Location LocationID="10"   
            LaborHours="1.1"  
            MachineHours=".2" >Some text 1  
<step>Manufacturing step 1 at this work center</step>  
<step>Manufacturing step 2 at this work center</step>  
</Location>  
</Root>'  
SELECT @myDoc  
-- delete an attribute  
SET @myDoc.modify('  
  delete /Root/Location/@MachineHours  
')  
SELECT @myDoc  
-- delete an element  
SET @myDoc.modify('  
  delete /Root/Location/step[2]  
')  
SELECT @myDoc  
-- delete text node (in <Location>  
SET @myDoc.modify('  
  delete /Root/Location/text()  
')  
SELECT @myDoc  
-- delete all processing instructions  
SET @myDoc.modify('  
  delete //processing-instruction()  
')  
SELECT @myDoc

--Применение оператора replace value of в методе XQuery modify.
DECLARE @myDoc XML;  
SET @myDoc = '<Root>  
<Location LocationID="10"   
            LaborHours="1.1"  
            MachineHours=".2" >Manufacturing steps are described here.  
<step>Manufacturing step 1 at this work center</step>  
<step>Manufacturing step 2 at this work center</step>  
</Location>  
</Root>';  
SELECT @myDoc;  
-- update text in the first manufacturing step  
SET @myDoc.modify('  
  replace value of (/Root/Location/step[1]/text())[1]  
  with "new text describing the manu step"  
');  
SELECT @myDoc;  
-- update attribute value  
SET @myDoc.modify('  
  replace value of (/Root/Location/@LaborHours)[1]  
  with "100.0"  
');  
SELECT @myDoc;





/*Примеры использования метода nodes() для типа данных xml*/
--Применение метода nodes() к переменной типа данных xml.
DECLARE @x XML   
SET @x='<Root>  
    <row id="1"><name>Larry</name><oflw>some text</oflw></row>  
    <row id="2"><name>moe</name></row>  
    <row id="3" />  
</Root>'  
SELECT T.c.query('.') AS result  
FROM   @x.nodes('/Root/row') T(c)  
GO
--Задание метода nodes() для столбца типа данных xml.
SELECT C.query('.') as result  
FROM Production.ProductModel  
CROSS APPLY Instructions.nodes('  
	declare namespace MI="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions";  
	/MI:root/MI:Location') as T(C)  
WHERE ProductModelID=7
--Применение метода nodes() к набору строк, возвращенному другим методом nodes().
SELECT ProductModelID, Locations.value('./@LocationID','int') AS LocID,  
steps.query('.') AS Step         
FROM Production.ProductModel         
CROSS APPLY Instructions.nodes('         
	declare namespace MI="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions";         
	/MI:root/MI:Location') AS T1(Locations)         
CROSS APPLY T1.Locations.nodes('         
	declare namespace MI="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions";         
	./MI:step ') AS T2(steps)         
WHERE ProductModelID=7         
GO
--Замечание относительно указания пространств имен.
WITH XMLNAMESPACES (  
   'http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions' AS MI)  
SELECT ProductModelID, Locations.value('./@LocationID','int') AS LocID,  
steps.query('.') AS Step         
FROM Production.ProductModel         
CROSS APPLY Instructions.nodes('         
	/MI:root/MI:Location') AS T1(Locations)         
CROSS APPLY T1.Locations.nodes('         
	./MI:step ') as T2(steps)         
WHERE ProductModelID=7         
GO





/*Связывание реляционных столбцов и переменных*/
--Получение реляционного значения внутри XML с помощью функции sql:column().
SELECT P.ProductID, CatalogDescription.query('  
declare namespace pd="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
       <Product   
           ProductID=       "{ sql:column("P.ProductID") }"  
           ProductName=     "{ sql:column("P.Name") }"  
           ProductPrice=    "{ sql:column("P.ListPrice") }"  
           ProductModelID= "{ sql:column("PM.ProductModelID") }" >  
           { if (not(empty(/pd:ProductDescription))) then  
             attribute ProductModelName { /pd:ProductDescription[1]/@ProductModelName }  
            else   
               ()  
}  
        </Product>  
') as Result  
FROM Production.ProductModel PM, Production.Product P  
WHERE PM.ProductModelID = P.ProductModelID  
AND   CatalogDescription is not NULL  
ORDER By PM.ProductModelID
--Передача переменной Transact-SQL в XML с помощью функции sql:variable().
DECLARE @price money  
SET @price=2500.00  
SELECT ProductID, Production.ProductModel.ProductModelID,CatalogDescription.query('  
declare namespace pd="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelDescription";  
       <Product   
           ProductID="{ sql:column("Production.Product.ProductID") }"  
           ProductModelID= "{ sql:column("Production.Product.ProductModelID") }"  
           ProductModelName="{/pd:ProductDescription[1]/@ProductModelName }"  
           ListPrice="{ sql:column("Production.Product.ListPrice") }"  
           DiscountPrice="{ sql:variable("@price") }"  
        />')   
FROM Production.Product   
JOIN Production.ProductModel  
ON Production.Product.ProductModelID = Production.ProductModel.ProductModelID  
WHERE ProductID=771
