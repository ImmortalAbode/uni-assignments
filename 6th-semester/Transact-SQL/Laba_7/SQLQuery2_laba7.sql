--Используется БД CinemaService
USE CinemaService
GO

--Пример простой хранимой процедуры.
-- Хранимая процедура для получения списка всех кинотеатров.
CREATE PROCEDURE GetAllCinemas
AS
BEGIN
    SELECT * Cinema;
END
GO
-- Проверка.
EXEC GetAllCinemas;

--Пример хранимой процедуры с входным параметром.
-- Хранимая процедура для получения информации о кинотеатре по идентификатору.
CREATE PROCEDURE GetCinemaByID
    @CinemaID int
AS
BEGIN
    SELECT * FROM Cinema WHERE CinemaID = @CinemaID;
END
GO
-- Проверка.
EXEC GetCinemaByID @CinemaID = 1004;
EXEC GetCinemaByID 1004;

--Пример хранимой процедуры с выходным параметром.
--Хранимая процедура, которая проверяет наличие фильма в базе данных и возвращает соответствующее значение.
CREATE PROCEDURE CheckMovieExists
    @MovieName varchar(50)
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Movie WHERE MovieName = @MovieName)
        RETURN 1
    ELSE
        RETURN 0
END
GO
-- Проверка.
DECLARE @ReturnValue int
DECLARE @MovieName varchar(50) = 'Оппенгеймер';
EXEC @ReturnValue = CheckMovieExists @MovieName
SELECT @ReturnValue AS MovieExists

--Использование оператора RETURN в хранимой процедуре.
-- Хранимая процедура для проверки существования кинотеатра.
CREATE PROCEDURE CheckCinemaExists
    @CinemaID int
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Cinema WHERE CinemaID = @CinemaID)
    BEGIN
        RETURN 1;
    END
    ELSE
    BEGIN
        RETURN 0;
    END
END
GO
-- Проверка.
DECLARE @Result int;
EXEC @Result = CheckCinemaExists @CinemaID = 1;
SELECT @Result AS CinemaExists;

DECLARE @Result int;
EXEC @Result = CheckCinemaExists @CinemaID = 1004;
SELECT @Result AS CinemaExists;

--Пример создания скалярной функции.
--Скалярная функция для получения адреса кинотеатра по идентификатору.
CREATE FUNCTION GetFullCinemaAddress(@CinemaID int)
RETURNS varchar(200)
AS
BEGIN
    DECLARE @FullAddress varchar(200);

    SELECT @FullAddress = 
        City + ', ' + 
        Street + ', ' + 
        HouseNumber + 
        CASE WHEN HouseLetter IS NOT NULL AND HouseLetter <> '' THEN HouseLetter ELSE '' END + 
        CASE WHEN HouseDescr IS NOT NULL AND HouseDescr <> '-' THEN ', ' + HouseDescr ELSE '' END
    FROM Cinema
    WHERE CinemaID = @CinemaID;

    RETURN @FullAddress;
END;
GO
-- Проверка.
DECLARE @Address varchar(200);
SET @Address = dbo.GetFullCinemaAddress(1004);
SELECT @Address AS FullAddress;

--Пример подставляемой табличной функции.
--Подставляемая табличная функция для получения списка кинотеатров в указанном городе.
CREATE FUNCTION GetCinemasByCity
    (@City varchar(30))
RETURNS TABLE
AS
RETURN
(
    SELECT * 
    FROM Cinema
    WHERE City = @City
)
GO
-- Проверка.
SELECT * FROM dbo.GetCinemasByCity('Казань');

--Пример многооператорной табличной функции.
-- Мультиоператорная табличная функция для получения списка кинотеатров с количеством оценок к фильмам.
CREATE FUNCTION GetCinemasWithAssessmentCount()
RETURNS @CinemaAssessmentCount TABLE
(
    CinemaID int,
    CinemaName varchar(50),
    AssessmentCount int
)
AS
BEGIN
    INSERT INTO @CinemaAssessmentCount (CinemaID, CinemaName, AssessmentCount)
    SELECT c.CinemaID, c.CinemaName, COUNT(a.AssessmentID) AS AssessmentCount
    FROM Cinema c
    LEFT JOIN Assessment a ON c.CinemaID = a.CinemaID
    GROUP BY c.CinemaID, c.CinemaName;
    RETURN;
END;
GO
-- Проверка.
SELECT * FROM dbo.GetCinemasWithAssessmentCount();