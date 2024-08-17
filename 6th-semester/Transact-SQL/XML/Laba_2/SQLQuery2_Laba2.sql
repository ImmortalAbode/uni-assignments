USE CinemaService
GO

--ƒобавл€ем новую колонку XmlDataColumn дл€ данных из таблицы Movie
ALTER TABLE Movie
ADD XmlDataColumn XML

-- ќбновл€ем новую колонку XmlDataColumn с данными из таблицы Movie
UPDATE Movie
SET XmlDataColumn = (
    SELECT 
    Movie.MovieID     AS "@MovieID",
    Movie.MovieName   AS "Name",
    Movie.Release     AS "Release",
    Movie.Genre       AS "Genre",
    Movie.AgeLimit    AS "AgeLimit",
    Movie.Duration    AS "Duration",
    Movie.MovieFormat AS "MovieFormat",
	(SELECT
		Cinema.CinemaID AS "@CinemaID",
		Cinema.CinemaName AS "Name",
		Cinema.City AS "City"
	FROM CinemaMovie INNER JOIN Cinema
		ON CinemaMovie.CinemaID = Cinema.CinemaID
		WHERE CinemaMovie.MovieID = Movie.MovieID
	FOR XML PATH('Cinema'), TYPE
	) AS CinemaServices
FROM Movie AS m
WHERE Movie.MovieID = m.MovieID
FOR XML PATH ('Movie'), ROOT('MovieCinemaServicesInfo')
)
-- ѕреобразование в рел€ционный формат.
DECLARE @idoc INT
DECLARE @xmlData XML
SET @xmlData = 
	(SELECT XmlDataColumn
	FROM Movie
	FOR XML PATH(''), ROOT('XmlDataColumns'))
EXEC sp_xml_preparedocument @idoc OUTPUT, @xmlData
SELECT *
FROM OPENXML (@idoc, 'XmlDataColumns/XmlDataColumn/MovieCinemaServicesInfo/Movie/CinemaServices/Cinema', 2)
	WITH (
		CinemaID    int           '@CinemaID',
		CinemaName  varchar(50)   'Name',
		CinemaCity  varchar(30)   'City',
		MovieID     int           '../../@MovieID',
		Name        varchar(50)   '../../Name',
		Release     datetime      '../../Release',
		Genre       varchar(100)  '../../Genre',
		AgeLimit    varchar(3)    '../../AgeLimit',
		Duration    time          '../../Duration',
		Format      varchar(2)    '../../MovieFormat'
	)
ORDER BY CinemaID, MovieID
EXEC sp_xml_removedocument @idoc