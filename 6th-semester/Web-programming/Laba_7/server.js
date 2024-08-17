var express = require("express"),
    http = require("http"),
    app = express(),
    library = [
        {
            "returnDate": "15.06.2024",
            "fullName": "Иванов Иван Иванович",
            "title": "Преступление и наказание",
            "publishingOffice": "Эксмо",
            "year": "1866",
            "authors": ["Фёдор Михайлович Достоевский"]
        },
        {
            "returnDate": "20.07.2023",
            "fullName": "Петров Петр Петрович",
            "title": "Война и мир",
            "publishingOffice": "АСТ",
            "year": "1869",
            "authors": ["Лев Николаевич Толстой"]
        },
        {
            "returnDate": "05.08.2024",
            "fullName": "Сидоров Сидор Сидорович",
            "title": "Гарри Поттер и философский камень",
            "publishingOffice": "Росмэн",
            "year": "1997",
            "authors": ["Джоан Роулинг"]
        },
        {
            "returnDate": "10.07.2023",
            "fullName": "Козлова Анна Сергеевна",
            "title": "Мастер и Маргарита",
            "publishingOffice": "Художественная литература",
            "year": "1967",
            "authors": ["Михаил Афанасьевич Булгаков"]
        },
        {
            "returnDate": "01.09.2024",
            "fullName": "Смирнова Елена Ивановна",
            "title": "1984",
            "publishingOffice": "АСТ",
            "year": "1949",
            "authors": ["Джордж Оруэлл"]
        },
        {
            "returnDate": "06.06.2024",
            "fullName": "Горшков Андрей Олегович",
            "title": "Численные методы",
            "publishingOffice": "КГТУ",
            "year": "2006",
            "authors": ["Моисеев В.С.", "Комиссарова Е.М.", "Черняев Ю.А."]
        },
        {
            "returnDate": "06.06.2024",
            "fullName": "Горшков Андрей Олегович",
            "title": "Матрицы, определители и системы линейных алгебраических уравнений",
            "publishingOffice": "КГТУ",
            "year": "1993",
            "authors": ["Комиссарова Е.М.", "Цветков Л.Г."]
        }
    ];

app.use(express.static(__dirname + "/client"));
http.createServer(app).listen(3000);
app.get("/library.json", function (req, res) {
    res.json(library);
});
app.use(express.urlencoded());
app.post("/library", function (req, res) {
    console.log("Данные были отправлены на сервер!");
    var newBookRecord = req.body;
    console.log(newBookRecord);
    library.push(newBookRecord);
    res.json({ "message": "Вы размещаетесь на сервере!" });
});