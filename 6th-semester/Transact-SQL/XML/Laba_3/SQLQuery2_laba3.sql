USE CinemaService
GO

/*������� � �������������� ������� query(), value() � exist()*/
--��������� ���������� � ���� �������, ������ � �����-���� ����������, ������������ ������� ������ 2�.
--������������� ������� query(), exist() � ���������� FLOWR.
DECLARE @duration AS TIME = '02:00:00';
SELECT XmlDataColumn.query('
    <Movie>
    {
        for $movie in /MovieCinemaServicesInfo/Movie
        return (
            $movie/Name,
            $movie/Release,
            $movie/Genre,
            $movie/AgeLimit,
            $movie/Duration,
            $movie/MovieFormat
        )
    }
    </Movie>'
) AS MoviesInfo
FROM Movie
WHERE XmlDataColumn.exist('/MovieCinemaServicesInfo/Movie[Duration <= xs:time(sql:variable("@duration"))]') = 1
--������������� ������� query() � value().
SELECT XmlDataColumn.query(
	'<Movie>
		{/MovieCinemaServicesInfo/Movie/Name}
		{/MovieCinemaServicesInfo/Movie/Release}
		{/MovieCinemaServicesInfo/Movie/Genre}
		{/MovieCinemaServicesInfo/Movie/AgeLimit}
		{/MovieCinemaServicesInfo/Movie/Duration}
		{/MovieCinemaServicesInfo/Movie/MovieFormat}
	</Movie>')
FROM Movie
WHERE XmlDataColumn.value('(/MovieCinemaServicesInfo/Movie/Duration)[1]', 'time') <= '02:00:00';

SELECT * FROM Movie

/*������� � �������������� ������ modify()nodes()*/
--�������� insert. ���������� ��������� � ������ "�����������".
DECLARE @directorName AS NVARCHAR(50) = '��������� �����'
UPDATE movie
SET XmlDataColumn.modify('
    insert 
        <FilmCrew>
            <Director>{sql:variable("@directorName")}</Director>
        </FilmCrew>
    as first into (/MovieCinemaServicesInfo/Movie[Name = "�����������"])[1]')
--�������� insert. ���������� ����������� � ������ "�����������".
UPDATE Movie
SET XmlDataColumn.modify('
	insert element Produsers {"����� �����������"} as last
	into (/MovieCinemaServicesInfo/Movie[Name = "�����������"]/FilmCrew)[1]')
--�������� replace value of. ��������� ����������� ������ "�����������".
UPDATE Movie
SET XmlDataColumn.modify('
    replace value of 
        (/MovieCinemaServicesInfo/Movie[Name = "�����������"]/FilmCrew/Produsers/text())[1] 
    with "��������� �����, ���� �����, ������ �����"')
--�������� delete. �������� ��������� � ����������� ������ "�����������".
UPDATE Movie
SET XmlDataColumn.modify('delete /MovieCinemaServicesInfo/Movie[Name = "�����������"]/FilmCrew')

/*������� � �������������� ������ nodes()*/
--��������� ������ ����������� � ������ � ��� �������.
SELECT 
	nCol.value('@CinemaID[1]', 'int') CinemaID,
	nCol.value('Name[1]', 'varchar(50)') CinemaName,
	nCol.value('City[1]', 'varchar(30)') CinemaCity,
	nCol.value('../../@MovieID[1]', 'int') MovieID,
	nCol.value('../../Name[1]', 'varchar(50)') Name,
	nCol.value('../../Release[1]', 'datetime') Release,
	nCol.value('../../Genre[1]', 'varchar(100)') Genre,
	nCol.value('../../AgeLimit[1]', 'varchar(3)') AgeLimit,
	nCol.value('../../Duration[1]', 'time') Duration,
	nCol.value('../../MovieFormat[1]', 'varchar(2)') MovieFormat
FROM Movie
CROSS APPLY XmlDataColumn.nodes('/MovieCinemaServicesInfo/Movie/CinemaServices/Cinema') AS nTable(nCol)
ORDER BY CinemaID, MovieID