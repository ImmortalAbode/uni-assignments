--Используется учебная БД AdventureWorks2022.
USE AdventureWorks2022
GO

--Реализация триггера INSERT
--В следующем коде демонстрируется создание триггера INSERT insrtWorkOrder на таблице
--Production.WorkOrder базы данных AdventureWorks. Заметьте, что таблица inserted
--используется для работы со значениями, которые вызвали выполнение триггера.
GO;
CREATE TRIGGER insrtWorkOrder ON Production.WorkOrder
AFTER INSERT AS
BEGIN
	SET NOCOUNT ON;
	INSERT INTO Production.TransactionHistory(
		ProductID,
		ReferenceOrderID,
		TransactionType,
		TransactionDate,
		Quantity,
		ActualCost)
	SELECT inserted.ProductID,
	inserted.WorkOrderID,
	'W', GETDATE(), inserted.OrderQty, 0
	FROM inserted;
END;

--Реализация триггера DELETE
--В следующем коде демонстрируется создание триггера DELETE delCustomer на таблице
--Sales.Customer базы данных AdventureWorks.
GO;
CREATE TRIGGER delCustomer ON Sales.Customer
AFTER DELETE AS
BEGIN
	SET NOCOUNT ON;
	EXEC  msdb.dbo.sp_send_dbmail
		@profile_name = 'AdventureWorksEmailProfile',
		@recipients = 'SalesManagers@Adventure-Works.com',
		@subject = 'Customer Deleted',
		@body = 'A customer has been deleted from the database.';
END;

--Реализация триггера UPDATE
--В следующем коде демонстрируется создание триггера UPDATE updtProductReview на
--таблице Production.ProductReview базы данных AdventureWorks.
GO;
CREATE TRIGGER updtProductReview ON Production.ProductReview
AFTER UPDATE NOT FOR REPLICATION AS
BEGIN
	SET NOCOUNT ON;
	UPDATE Production.ProductReview
		SET Production.ProductReview.ModifiedDate = GETDATE()
	FROM inserted
		WHERE inserted.ProductReviewID = Production.ProductReview.ProductReviewID;
END;

--Реализация триггера INSTEAD OF
--В следующем коде демонстрируется создание триггера INSTEAD OF delEmployee на таблице
--HumanResources.Employee база данных AdventureWorks.
GO;
CREATE TRIGGER delEmployee ON HumanResources.Employee
INSTEAD OF DELETE NOT FOR REPLICATION AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @DeleteCount int;
	SELECT @DeleteCount = COUNT(*) FROM deleted;
	IF @DeleteCount > 0
	BEGIN
		RAISERROR
		(N'Employees cannot be deleted. They can only be marked as not current.', --Message
		10, -- Severity.
		1); -- State.
		-- Roll back any active or uncommittable transactions
		IF @@TRANCOUNT > 0
		BEGIN
			ROLLBACK TRANSACTION;
		END
	END;
END;

--Отмена вложения:
sp_configure 'nested triggers', 0;

--Триггер не вызывает себя рекурсивно, пока не
--установлена опция базы данных RECURSIVE_TRIGGERS (влияет только на прямую рекурсию)
ALTER DATABASE AdventureWorks SET RECURSIVE_TRIGGERS ON
sp_dboption databasename, 'recursive triggers', True