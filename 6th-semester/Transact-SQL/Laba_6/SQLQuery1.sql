--������������ ������� �� AdventureWorks2022.
USE AdventureWorks2022
GO

--���������� �������� INSERT
--� ��������� ���� ��������������� �������� �������� INSERT insrtWorkOrder �� �������
--Production.WorkOrder ���� ������ AdventureWorks. ��������, ��� ������� inserted
--������������ ��� ������ �� ����������, ������� ������� ���������� ��������.
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

--���������� �������� DELETE
--� ��������� ���� ��������������� �������� �������� DELETE delCustomer �� �������
--Sales.Customer ���� ������ AdventureWorks.
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

--���������� �������� UPDATE
--� ��������� ���� ��������������� �������� �������� UPDATE updtProductReview ��
--������� Production.ProductReview ���� ������ AdventureWorks.
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

--���������� �������� INSTEAD OF
--� ��������� ���� ��������������� �������� �������� INSTEAD OF delEmployee �� �������
--HumanResources.Employee ���� ������ AdventureWorks.
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

--������ ��������:
sp_configure 'nested triggers', 0;

--������� �� �������� ���� ����������, ���� ��
--����������� ����� ���� ������ RECURSIVE_TRIGGERS (������ ������ �� ������ ��������)
ALTER DATABASE AdventureWorks SET RECURSIVE_TRIGGERS ON
sp_dboption databasename, 'recursive triggers', True