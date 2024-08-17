USE CinemaService
GO

/*ЗАПРОСЫ В РЕЖИМЕ RAW*/
--Пример 1. Вывод всех кинотеатров и фильмов, идущих в каждом кинотеатре.
SELECT CinemaName AS Cinema, MovieName AS Movie, Release AS ReleaseMovie
	FROM Cinema INNER JOIN CinemaMovie ON Cinema.CinemaID = CinemaMovie.CinemaID
		INNER JOIN Movie ON CinemaMovie.MovieID = Movie.MovieID
	ORDER BY Cinema.CinemaID
FOR XML RAW('CinemaService'), ELEMENTS, ROOT('CinemaServices')
--Пример 2. Вывод информации о всех кинотеатрах и фильмах, идущих в них.
SELECT CinemaName, OpeningTime, ClosingTime, ContactInformation,
    (SELECT MovieName, Release, Genre, AgeLimit, Duration, MovieFormat
        FROM 
            CinemaMovie AS cm INNER JOIN Movie AS m
			ON cm.MovieID = m.MovieID
        WHERE 
            cm.CinemaID = c.CinemaID
        FOR XML RAW('Movie'), TYPE
    ) AS Movies
FROM Cinema AS c
ORDER BY CinemaName
FOR XML RAW('Cinema'), ROOT('CinemasWithMovies')

/*ЗАПРОСЫ В РЕЖИМЕ AUTO*/
--Пример 1. Вывод информации о всех пользователях, зарегистрированных в системе.
SELECT UserLogin, UserPswd, UserRole
	FROM UserInformation
FOR XML AUTO, ELEMENTS, ROOT('Users')
--Пример 2. Вывод всех пользователей, зарегистрированных в системе, и информации об их комментариях.
SELECT UserID, UserLogin, UserRole,
    (SELECT ReviewID, Comment, CommentDateTime
        FROM Review AS r WHERE r.UserID = ui.UserID
        FOR XML AUTO, TYPE
    ) AS Reviews
FROM UserInformation AS ui
ORDER BY UserID
FOR XML AUTO, ROOT('UsersWithReviews')

/*ЗАПРОСЫ В РЕЖИМЕ PATH*/
--Пример 1. Вывод информации о всех пользователях, зарегистрированных в системе.
SELECT ui.UserID AS "@UserID",
	ui.UserLogin AS "@Login",
	ui.UserPswd AS "@Password"
FROM UserInformation AS ui
ORDER BY ui.UserID
FOR XML PATH('User'), ROOT('Users')
--Пример 2. Вывод всех кинотеатров и информации о фильмах, идущих в каждом из них.
SELECT Cinema.CinemaID AS "@CinemaID",
	Cinema.CinemaName AS "Cinema/Name",
	Cinema.City AS "Cinema/City",
	(SELECT Movie.MovieID AS "@MovieID",
			Movie.MovieName AS "Movie/Name",
			Movie.Release AS "Movie/Release",
            Movie.Genre AS "Movie/Genre",
            Movie.AgeLimit AS "Movie/AgeLimit",
            Movie.Duration AS "Movie/Duration",
            Movie.MovieFormat AS "Movie/MovieFormat"
	FROM CinemaMovie INNER JOIN Movie
		ON CinemaMovie.MovieID = Movie.MovieID
		WHERE CinemaMovie.CinemaID = Cinema.CinemaID
	FOR XML PATH('Movie'), TYPE
	) AS Movies
FROM Cinema
ORDER BY Cinema.CinemaID
FOR XML PATH('CinemaService'), ROOT('CinemaServices')

/*ЗАПРОСЫ В РЕЖИМЕ EXPLICIT*/
--Пример 1. Вывод всех пользователей, зарегистрированных в системе, и информации о них.
SELECT 1 AS Tag,
    NULL AS Parent,
    UserID AS [User!1!ID],
	UserLogin AS [User!1!Login],
    UserPswd AS [User!1!Pswd]
FROM UserInformation
ORDER BY UserID
FOR XML EXPLICIT
--Пример 2. Вывод всех фильмом, которые комментировали пользователи, с отображением комментариев.
SELECT 1 AS Tag,
    NULL AS Parent,
	Movie.MovieID AS [Movie!1!ID],
    Movie.MovieName AS [Movie!1!Name!Element],
    NULL AS [User!2!ID],
    NULL AS [User!2!Comment],
	NULL AS [User!2!DateTime]
FROM Movie
UNION ALL
SELECT 2 AS Tag,
    1 AS Parent,
    Movie.MovieID,
    NULL,
    Review.UserID,
    Review.Comment,
	Review.CommentDateTime
FROM Review JOIN Assessment
    ON Review.AssessmentID = Assessment.AssessmentID
        JOIN Movie ON Assessment.MovieID = Movie.MovieID
ORDER BY [Movie!1!ID], [User!2!DateTime]
FOR XML EXPLICIT