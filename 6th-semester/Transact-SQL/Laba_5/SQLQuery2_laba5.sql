--Используется БД CinemaService.
USE CinemaService
GO

/*Создание простого представления CinemaService.vMovie на основе одной таблицы Movie, со всеми столбцами, используя только условие выборки WHERE (возр. ограничение фильма 18+),
 *без опции CHECK WITH OPTION
 */
 CREATE VIEW vMovie
 AS
 SELECT *
 FROM dbo.Movie
 WHERE AgeLimit = '18+'

 --Выборка названий фильмов, жанра, возр. ограничения, продолжительности и формата из полученного представления vMovie.
SELECT MovieName, Genre, AgeLimit, Duration, MovieFormat FROM dbo.vMovie

 --Выборка всех фильмов из представления vMovie, продолжительность которых больше 1ч.
SELECT * FROM vMovie
WHERE DATEPART(HOUR, Duration) > 1 OR (DATEPART(HOUR, Duration) = 1 AND DATEPART(MINUTE, Duration) > 0);

/*Работа с представлением БЕЗ WITH CHECK OPTION*/
-- Вставка новой записи через представление vMovie.
INSERT INTO vMovie (MovieName, Release, Genre, AgeLimit, Duration, MovieFormat)
VALUES ('New Movie', 2023-05-15, 'Action', '18+', '02:00:00', '2D');
-- Вставка новой записи через представление vMovie.
INSERT INTO vMovie (MovieName, Release, Genre, AgeLimit, Duration, MovieFormat)
VALUES ('New new movie', CAST('2024-05-16T14:30:00.000' AS DATETIME), 'Action', '14+', '02:00:00', '2D');
--Обновление записи через представление vMovie.
UPDATE vMovie
SET MovieName = 'Updated Movie Name'
WHERE MovieName = 'New Movie'
--Удаление добавленных записей через представление vMovie.
DELETE FROM vMovie WHERE MovieName = 'Updated Movie Name'
DELETE FROM vMovie WHERE MovieName = 'New new Movie'
/*Все запросы выполнились*/


--Добавление опции WITH CHECK OPTION к представлению vMovie.
ALTER VIEW vMovie
AS
SELECT *
FROM dbo.Movie
WHERE AgeLimit = '18+'
WITH CHECK OPTION
/*Команда с вставкой фильма с возр. ограничением 14+ (НЕ 18+) не выполнилась из-за опции WITH CHECK OPTION для WHERE*/

--Создание представления vCinemaMovieInfo для просмотра информации о кинотеатрах и фильмах.
CREATE VIEW vCinemaMovieInfo
AS
SELECT c.CinemaName, c.City, c.Street, c.HouseNumber, m.MovieName, m.Release, m.Genre, m.Duration
FROM Cinema c
JOIN CinemaMovie cm ON c.CinemaID = cm.CinemaID
JOIN Movie m ON cm.MovieID = m.MovieID;

SELECT * FROM vCinemaMovieInfo

--Создание представления vMovieRatings для оценок фильмов с их названиями и контеатрами.
CREATE VIEW vMovieRatings
AS
SELECT m.MovieName, c.CinemaName, a.TranscriptID
FROM Movie m
JOIN Assessment a ON m.MovieID = a.MovieID
JOIN Cinema c ON a.CinemaID = c.CinemaID

SELECT * FROM vMovieRatings

--Создание представления vUserReviews для просмотра информации о пользователях и их отзывах.
CREATE VIEW vUserReviews
AS
SELECT u.UserLogin, r.Comment, r.CommentDateTime
FROM UserInformation u
JOIN Review r ON u.UserID = r.UserID;

SELECT * FROM vUserReviews

--Создание представления vCombinedMovieInfoRatings для просмотра информации о кинотеатрах, фильмах и их оценках фильмов.
CREATE VIEW vCombinedMovieInfoRatings
AS
SELECT cm.*, mr.TranscriptID
FROM vCinemaMovieInfo cm
JOIN vMovieRatings mr ON cm.MovieName = mr.MovieName AND cm.CinemaName = mr.CinemaName;

SELECT * FROM vCombinedMovieInfoRatings

--Возвращение списка всех доступных представлений в базе данных CinemaService.
SELECT * FROM sys.views

--Возвращение текста представления vCombinedMovieInfoRatings базы данных CinemaService.
EXEC sp_helptext 'vCombinedMovieInfoRatings'

--Получение списка всех объектов базы данных, которые имеют прямые зависимости от таблицы dbo.Movie базы данных CinemaService.
SELECT DISTINCT OBJECT_NAME(object_id) AS Name
FROM sys.sql_dependencies
	WHERE referenced_major_id =
	OBJECT_ID(N'CinemaService.dbo.Movie')

--Получение списка всех объектов базы данных, с которыми имеет зависимость представление vMovieRatings базы данных CinemaService.
SELECT DISTINCT referenced_entity_name AS UsedObject
FROM sys.sql_expression_dependencies
WHERE referencing_id = OBJECT_ID('CinemaService.dbo.vMovieRatings');

/*Эксперимент с просмотром фактического плана исполнения запросов до создания индекса к представлению IX_vStateProvinceCountryRegion БД AdwentureWorks2022 и после*/
USE AdventureWorks2022
GO

--Создание представления [Person].[vStateProvinceCountryRegion], содержащего информацию о географических областях (штатах/провинциях), привязанных к соответствующим регионам стран.
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

--Получение количества географических областей в каждом регионе.
SELECT 
    CountryRegionName,
    COUNT(*) AS NumberOfStateProvinces
FROM 
    [Person].[vStateProvinceCountryRegion]
GROUP BY 
    CountryRegionName

--Создание уникального кластеризованного индекса для представления.
CREATE UNIQUE CLUSTERED INDEX [IX_vStateProvinceCountryRegion] ON
[Person].[vStateProvinceCountryRegion]
(
	[StateProvinceID] ASC, [CountryRegionCode] ASC
)

-- Удаление кластеризованного индекса из представления.
DROP INDEX [IX_vStateProvinceCountryRegion] ON [Person].[vStateProvinceCountryRegion];