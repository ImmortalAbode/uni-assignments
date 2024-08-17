--������������ �� CinemaService.
USE CinemaService
GO

/*�������� �������� ������������� CinemaService.vMovie �� ������ ����� ������� Movie, �� ����� ���������, ��������� ������ ������� ������� WHERE (����. ����������� ������ 18+),
 *��� ����� CHECK WITH OPTION
 */
 CREATE VIEW vMovie
 AS
 SELECT *
 FROM dbo.Movie
 WHERE AgeLimit = '18+'

 --������� �������� �������, �����, ����. �����������, ����������������� � ������� �� ����������� ������������� vMovie.
SELECT MovieName, Genre, AgeLimit, Duration, MovieFormat FROM dbo.vMovie

 --������� ���� ������� �� ������������� vMovie, ����������������� ������� ������ 1�.
SELECT * FROM vMovie
WHERE DATEPART(HOUR, Duration) > 1 OR (DATEPART(HOUR, Duration) = 1 AND DATEPART(MINUTE, Duration) > 0);

/*������ � �������������� ��� WITH CHECK OPTION*/
-- ������� ����� ������ ����� ������������� vMovie.
INSERT INTO vMovie (MovieName, Release, Genre, AgeLimit, Duration, MovieFormat)
VALUES ('New Movie', 2023-05-15, 'Action', '18+', '02:00:00', '2D');
-- ������� ����� ������ ����� ������������� vMovie.
INSERT INTO vMovie (MovieName, Release, Genre, AgeLimit, Duration, MovieFormat)
VALUES ('New new movie', CAST('2024-05-16T14:30:00.000' AS DATETIME), 'Action', '14+', '02:00:00', '2D');
--���������� ������ ����� ������������� vMovie.
UPDATE vMovie
SET MovieName = 'Updated Movie Name'
WHERE MovieName = 'New Movie'
--�������� ����������� ������� ����� ������������� vMovie.
DELETE FROM vMovie WHERE MovieName = 'Updated Movie Name'
DELETE FROM vMovie WHERE MovieName = 'New new Movie'
/*��� ������� �����������*/


--���������� ����� WITH CHECK OPTION � ������������� vMovie.
ALTER VIEW vMovie
AS
SELECT *
FROM dbo.Movie
WHERE AgeLimit = '18+'
WITH CHECK OPTION
/*������� � �������� ������ � ����. ������������ 14+ (�� 18+) �� ����������� ��-�� ����� WITH CHECK OPTION ��� WHERE*/

--�������� ������������� vCinemaMovieInfo ��� ��������� ���������� � ����������� � �������.
CREATE VIEW vCinemaMovieInfo
AS
SELECT c.CinemaName, c.City, c.Street, c.HouseNumber, m.MovieName, m.Release, m.Genre, m.Duration
FROM Cinema c
JOIN CinemaMovie cm ON c.CinemaID = cm.CinemaID
JOIN Movie m ON cm.MovieID = m.MovieID;

SELECT * FROM vCinemaMovieInfo

--�������� ������������� vMovieRatings ��� ������ ������� � �� ���������� � �����������.
CREATE VIEW vMovieRatings
AS
SELECT m.MovieName, c.CinemaName, a.TranscriptID
FROM Movie m
JOIN Assessment a ON m.MovieID = a.MovieID
JOIN Cinema c ON a.CinemaID = c.CinemaID

SELECT * FROM vMovieRatings

--�������� ������������� vUserReviews ��� ��������� ���������� � ������������� � �� �������.
CREATE VIEW vUserReviews
AS
SELECT u.UserLogin, r.Comment, r.CommentDateTime
FROM UserInformation u
JOIN Review r ON u.UserID = r.UserID;

SELECT * FROM vUserReviews

--�������� ������������� vCombinedMovieInfoRatings ��� ��������� ���������� � �����������, ������� � �� ������� �������.
CREATE VIEW vCombinedMovieInfoRatings
AS
SELECT cm.*, mr.TranscriptID
FROM vCinemaMovieInfo cm
JOIN vMovieRatings mr ON cm.MovieName = mr.MovieName AND cm.CinemaName = mr.CinemaName;

SELECT * FROM vCombinedMovieInfoRatings

--����������� ������ ���� ��������� ������������� � ���� ������ CinemaService.
SELECT * FROM sys.views

--����������� ������ ������������� vCombinedMovieInfoRatings ���� ������ CinemaService.
EXEC sp_helptext 'vCombinedMovieInfoRatings'

--��������� ������ ���� �������� ���� ������, ������� ����� ������ ����������� �� ������� dbo.Movie ���� ������ CinemaService.
SELECT DISTINCT OBJECT_NAME(object_id) AS Name
FROM sys.sql_dependencies
	WHERE referenced_major_id =
	OBJECT_ID(N'CinemaService.dbo.Movie')

--��������� ������ ���� �������� ���� ������, � �������� ����� ����������� ������������� vMovieRatings ���� ������ CinemaService.
SELECT DISTINCT referenced_entity_name AS UsedObject
FROM sys.sql_expression_dependencies
WHERE referencing_id = OBJECT_ID('CinemaService.dbo.vMovieRatings');

/*����������� � ���������� ������������ ����� ���������� �������� �� �������� ������� � ������������� IX_vStateProvinceCountryRegion �� AdwentureWorks2022 � �����*/
USE AdventureWorks2022
GO

--�������� ������������� [Person].[vStateProvinceCountryRegion], ����������� ���������� � �������������� �������� (������/����������), ����������� � ��������������� �������� �����.
CREATE VIEW [Person].[vStateProvinceCountryRegion] 
WITH SCHEMABINDING 
AS 
SELECT 
    sp.[StateProvinceID] 
    ,sp.[StateProvinceCode] 
    ,sp.[IsOnlyStateProvinceFlag] 
    ,sp.[Name] AS [StateProvinceName] 
    ,sp.[TerritoryID] 
    ,cr.[CountryRegionCode] 
    ,cr.[Name] AS [CountryRegionName]
FROM [Person].[StateProvince] sp 
    INNER JOIN [Person].[CountryRegion] cr 
    ON sp.[CountryRegionCode] = cr.[CountryRegionCode]

--��������� ���������� �������������� �������� � ������ �������.
SELECT 
    CountryRegionName,
    COUNT(*) AS NumberOfStateProvinces
FROM 
    [Person].[vStateProvinceCountryRegion]
GROUP BY 
    CountryRegionName

--�������� ����������� ����������������� ������� ��� �������������.
CREATE UNIQUE CLUSTERED INDEX [IX_vStateProvinceCountryRegion] ON
[Person].[vStateProvinceCountryRegion]
(
	[StateProvinceID] ASC, [CountryRegionCode] ASC
)

-- �������� ����������������� ������� �� �������������.
DROP INDEX [IX_vStateProvinceCountryRegion] ON [Person].[vStateProvinceCountryRegion];