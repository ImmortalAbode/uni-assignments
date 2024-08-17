--Используется БД CinemaService.
USE CinemaService
GO
--Триггер для каскадного удаления записей, связанных с удаляемым кинотеатром.
CREATE TRIGGER trg_Cinema_Delete
ON Cinema
FOR DELETE
AS
BEGIN
    -- Удаляем связанные записи из таблицы Review.
    DELETE R
    FROM Review R
    INNER JOIN Assessment A ON R.AssessmentID = A.AssessmentID
    WHERE A.CinemaID IN (SELECT CinemaID FROM DELETED);
    -- Удаляем связанные записи из таблицы Assessment.
    DELETE A
    FROM Assessment A
    WHERE A.CinemaID IN (SELECT CinemaID FROM DELETED);
    -- Удаляем связанные записи из таблицы CinemaMovie.
    DELETE CM
    FROM CinemaMovie CM
    WHERE CM.CinemaID IN (SELECT CinemaID FROM DELETED);
    -- Удаляем связанные записи из таблицы Movie, которые больше не связаны ни с одним кинотеатром.
    DELETE M
    FROM Movie M
    WHERE NOT EXISTS (SELECT 1 FROM CinemaMovie CM WHERE CM.MovieID = M.MovieID);
END
GO
--Удаление кинотеатра с ID = 15.
DELETE FROM Cinema WHERE CinemaID = 15