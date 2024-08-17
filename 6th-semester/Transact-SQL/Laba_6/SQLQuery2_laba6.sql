--������������ �� CinemaService.
USE CinemaService
GO
--������� ��� ���������� �������� �������, ��������� � ��������� �����������.
CREATE TRIGGER trg_Cinema_Delete
ON Cinema
FOR DELETE
AS
BEGIN
    -- ������� ��������� ������ �� ������� Review.
    DELETE R
    FROM Review R
    INNER JOIN Assessment A ON R.AssessmentID = A.AssessmentID
    WHERE A.CinemaID IN (SELECT CinemaID FROM DELETED);
    -- ������� ��������� ������ �� ������� Assessment.
    DELETE A
    FROM Assessment A
    WHERE A.CinemaID IN (SELECT CinemaID FROM DELETED);
    -- ������� ��������� ������ �� ������� CinemaMovie.
    DELETE CM
    FROM CinemaMovie CM
    WHERE CM.CinemaID IN (SELECT CinemaID FROM DELETED);
    -- ������� ��������� ������ �� ������� Movie, ������� ������ �� ������� �� � ����� �����������.
    DELETE M
    FROM Movie M
    WHERE NOT EXISTS (SELECT 1 FROM CinemaMovie CM WHERE CM.MovieID = M.MovieID);
END
GO
--�������� ���������� � ID = 15.
DELETE FROM Cinema WHERE CinemaID = 15