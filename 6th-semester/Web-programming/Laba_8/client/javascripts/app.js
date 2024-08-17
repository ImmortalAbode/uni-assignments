var main = function () {
    "use strict";
    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            var $element = $(element),
                $content;
            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();
            //Новые -> Старые.
            if ($element.parent().is(":nth-child(1)")) {
                fetch("api/bookRecords", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (bookRecords) {
                        $content = $("<div>");
                        bookRecords.reverse();
                        bookRecords.forEach(function (item) {
                            var $recordClassDiv = $("<div>").addClass("recordClass");

                            $recordClassDiv.append($("<h4>").text("Дата возврата: " + item.returnDate));
                            $recordClassDiv.append($("<h4>").text("ФИО держателя: " + item.fullName));
                            $recordClassDiv.append($("<h4>").text("Название: " + item.title));
                            $recordClassDiv.append($("<h4>").text("Издательство: " + item.publishingOffice));
                            $recordClassDiv.append($("<h4>").text("Год издания: " + item.year));

                            $recordClassDiv.append($("<p>").text("Автор(-ы): "));
                            var $author_ul = $("<ul>");

                            item.authors.split(/\s*,\s*/).forEach(function (author) {
                                var $author_li = $("<li>").text(author);
                                $author_ul.append($author_li);
                            })
                            $recordClassDiv.append($author_ul);
                            $content.append($recordClassDiv);
                        })
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            //Старые -> Новые.
            } else if ($element.parent().is(":nth-child(2)")) {
                fetch("api/bookRecords", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (bookRecords) {
                        $content = $("<div>");
                        bookRecords.forEach(function (item) {
                            var $recordClassDiv = $("<div>").addClass("recordClass");

                            $recordClassDiv.append($("<h4>").text("Дата возврата: " + item.returnDate));
                            $recordClassDiv.append($("<h4>").text("ФИО держателя: " + item.fullName));
                            $recordClassDiv.append($("<h4>").text("Название: " + item.title));
                            $recordClassDiv.append($("<h4>").text("Издательство: " + item.publishingOffice));
                            $recordClassDiv.append($("<h4>").text("Год издания: " + item.year));

                            $recordClassDiv.append($("<p>").text("Автор(-ы): "));
                            var $author_ul = $("<ul>");

                            item.authors.split(/\s*,\s*/).forEach(function (author) {
                                var $author_li = $("<li>").text(author);
                                $author_ul.append($author_li);
                            })
                            $recordClassDiv.append($author_ul);
                            $content.append($recordClassDiv);
                        })
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            //Группировка по дате возврата и ФИО ответственного.
            } else if ($element.parent().is(":nth-child(3)")) {
                fetch("api/bookRecords", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (bookRecords) {                        
                        var returnDateAndPerson = {};

                        bookRecords.forEach(function (item) {
                            var key = item.returnDate + "|" + item.fullName;
                            if (returnDateAndPerson.hasOwnProperty(key)) {
                                returnDateAndPerson[key].push(item);
                            } else {
                                returnDateAndPerson[key] = [item];
                            }
                        })

                        $content = $("<div>");
                        for (var key in returnDateAndPerson) {
                            if (returnDateAndPerson.hasOwnProperty(key)) {
                                var $returnDatePersonClassDiv = $("<div>").addClass("returnDatePersonClass");
                                var keys = key.split("|");
                                $returnDatePersonClassDiv.append($("<p>").text("Дата возврата: " + keys[0]));
                                $returnDatePersonClassDiv.append($("<p>").text("ФИО держателя: " + keys[1]));

                                returnDateAndPerson[key].forEach(function (additional_info) {
                                    var $recordClassDiv = $("<div>").addClass("recordClass");
                                    $recordClassDiv.append($("<h4>").text("Название: " + additional_info.title));
                                    $recordClassDiv.append($("<h4>").text("Издательство: " + additional_info.publishingOffice));
                                    $recordClassDiv.append($("<h4>").text("Год издания: " + additional_info.year));
                                    //Здесь нужно обработать разделение на производителей, если он представлен в формате строки, как и ранее.
                                    $recordClassDiv.append($("<h4>").text("Автор(-ы): " + additional_info.authors));
                                    $returnDatePersonClassDiv.append($recordClassDiv);
                                });
                                $content.append($returnDatePersonClassDiv);
                            }
                        }
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            //Группировка по авторам.
            } else if ($element.parent().is(":nth-child(4)")) {
                fetch("api/bookRecords", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (bookRecords) {
                        var authors = {};
                        bookRecords.forEach(function (item) {
                            item.authors.split(/\s*,\s*/).forEach(function (author) {
                                if (authors.hasOwnProperty(author)) {
                                    authors[author].push(item);
                                } else {
                                    authors[author] = [item];
                                }
                            })
                        })
                        $content = $("<div>");
                        for (var author in authors) {
                            if (authors.hasOwnProperty(author)) {
                                var $authorClassDiv = $("<div>").addClass("authorClass");
                                $authorClassDiv.append($("<p>").text("Автор: " + author));
                                var $innerContent = $("<div>");
                                authors[author].forEach(function (book) {
                                    var $recordClassDiv = $("<div>").addClass("recordClass");
                                    $recordClassDiv.append($("<h4>").text("Дата возврата: " + book.returnDate));
                                    $recordClassDiv.append($("<h4>").text("ФИО держателя: " + book.fullName));
                                    $recordClassDiv.append($("<h4>").text("Название: " + book.title));
                                    $recordClassDiv.append($("<h4>").text("Издательство: " + book.publishingOffice));
                                    $recordClassDiv.append($("<h4>").text("Год издания: " + book.year));
                                    $innerContent.append($recordClassDiv);
                                });
                                $authorClassDiv.append($innerContent);
                                $content.append($authorClassDiv);
                            }
                        }
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            //Работа с записями.
            } else if ($element.parent().is(":nth-child(5)")) {
                $("main .content").empty();
                const $form = $("<form>").attr("id", "dataForm");
                $form.append(
                    $("<label>").text("Дата возврата: "),
                    $("<input>").attr({ type: "date", id: "returnDate", name: "returnDate" }),
                    $("<br>"),
                    $("<label>").text("ФИО держателя: "),
                    $("<input>").attr({ type: "text", id: "fullName", name: "fullName" }),
                    $("<br>"),
                    $("<label>").text("Название: "),
                    $("<input>").attr({ type: "text", id: "title", name: "title" }),
                    $("<br>"),
                    $("<label>").text("Издательство: "),
                    $("<input>").attr({ type: "text", id: "publishingOffice", name: "publishingOffice" }),
                    $("<br>"),
                    $("<label>").text("Год издания: "),
                    $("<input>").attr({ type: "number", id: "year", name: "year" }),
                    $("<br>"),
                    $("<label>").text("Автор(-ы): "),
                    $("<input>").attr({ type: "text", id: "authors", name: "authors" }),
                    $("<br>"),
                    $("<button>").attr({ type: "button", id: "saveBtn" }).addClass("btn").text("Сохранить"),
                    $("<button>").attr({ type: "button", id: "resetBtn" }).addClass("btn").text("Сбросить")
                );
                //Таблица.
                const $table = $("<table>").attr("id", "dataTable");
                $table.append(
                    $("<thead>").append(
                        $("<tr>").append(
                            $("<th>").text("Дата возврата"),
                            $("<th>").text("ФИО держателя"),
                            $("<th>").text("Название"),
                            $("<th>").text("Издательство"),
                            $("<th>").text("Год издания"),
                            $("<th>").text("Автор(-ы)"),
                            $("<th>").text("Действия")
                        )
                    ),
                    $("<tbody>")
                );
                $("main .content").append($form, $("<h2>").text("Записи в базе данных"), $table);

                // Функция для загрузки данных в таблицу.
                function loadData() {
                    fetch("api/bookRecords", {
                        method: "GET",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                return response.json();
                            } else {
                                throw new Error('Ошибка получения данных');
                            }
                        })
                        .then(bookRecords => {
                            const $tbody = $("#dataTable tbody");
                            $tbody.empty();

                            bookRecords.forEach(bookRecord => {
                                const $row = $("<tr>").append(
                                    $("<td>").text(bookRecord.returnDate),
                                    $("<td>").text(bookRecord.fullName),
                                    $("<td>").text(bookRecord.title),
                                    $("<td>").text(bookRecord.publishingOffice),
                                    $("<td>").text(bookRecord.year),
                                    $("<td>").text(bookRecord.authors),
                                    $("<td>").append(
                                        $("<button>")
                                            .attr("data-id", bookRecord._id)
                                            .addClass("btn")
                                            .addClass("editBtn")
                                            .text("Изменить"),
                                        $("<button>")
                                            .attr("data-id", bookRecord._id)
                                            .addClass("btn")
                                            .addClass("deleteBtn")
                                            .text("Удалить")
                                    )
                                );
                                $tbody.append($row);
                            });
                        })
                        .catch(error => {
                            console.error('Произошла ошибка при получении данных:', error);
                        });
                }
                loadData();

                // Обработчик для кнопки изменения.
                $(document).on("click", ".editBtn", function () {
                    const id = $(this).attr("data-id");

                    fetch(`api/bookRecords/${id}`, {
                        method: "GET",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                return response.json();
                            } else {
                                throw new Error('Ошибка получения данных');
                            }
                        })
                        .then(bookRecord => {
                            // Заполнение формы данными текущей записи
                            $("#returnDate").val(bookRecord.returnDate);
                            $("#fullName").val(bookRecord.fullName);
                            $("#title").val(bookRecord.title);
                            $("#publishingOffice").val(bookRecord.publishingOffice);
                            $("#year").val(bookRecord.year);
                            $("#authors").val(bookRecord.authors);

                            // Сохранение идентификатора записи в скрытом поле формы или переменной
                            $("#dataForm").data("current-id", bookRecord._id);
                        })
                        .catch(error => {
                            console.error('Произошла ошибка при получении данных для изменения:', error);
                        });
                });

                // Обработчик для кнопки сохранения.
                $("#saveBtn").on("click", function () {
                    const returnDate = $("#returnDate").val().trim();
                    const fullName = $("#fullName").val().trim();
                    const title = $("#title").val().trim();
                    const publishingOffice = $("#publishingOffice").val().trim();
                    const year = $("#year").val().trim();
                    const authors = $("#authors").val().trim();

                    if (!returnDate || !fullName || !title || !publishingOffice || !year || !authors) {
                        alert("Пожалуйста, заполните все поля");
                        return;
                    }

                    const data = {
                        returnDate: returnDate,
                        fullName: fullName,
                        title: title,
                        publishingOffice: publishingOffice,
                        year: year,
                        authors: authors
                    };

                    const id = $("#dataForm").data("current-id");

                    const method = id ? "PUT" : "POST";
                    const url = id ? `api/bookRecords/${id}` : "api/bookRecords";

                    fetch(url, {
                        method: method,
                        headers: { "Content-Type": "application/json" },
                        body: JSON.stringify(data)
                    })
                        .then(response => {
                            if (response.ok) {
                                loadData();
                                alert(`Запись успешно ${id ? "изменена" : "добавлена"}`);
                                $("#dataForm")[0].reset();
                                $("#dataForm").removeData("current-id");
                            } else {
                                throw new Error(`Ошибка ${id ? "изменения" : "добавления"} записи`);
                            }
                        })
                        .catch(error => {
                            console.error(`Произошла ошибка при ${id ? "изменении" : "добавлении"} записи:`, error);
                        });
                });

                // Обработчик для кнопки сброса.
                $("#resetBtn").on("click", function () {
                    $("#dataForm")[0].reset();
                });

                // Обработчик для кнопки удаления.
                $(document).on("click", ".deleteBtn", function () {
                    const id = $(this).attr("data-id");

                    fetch(`api/bookRecords/${id}`, {
                        method: "DELETE",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                loadData();
                                alert("Запись успешно удалена");
                            } else {
                                throw new Error('Ошибка удаления записи');
                            }
                        })
                        .catch(error => {
                            console.error('Произошла ошибка при удалении записи:', error);
                        });
                });                
            }            
            return false;
        });
    });
    // Автоматически активируем первую вкладку
    $(".tabs a:first-child span").trigger("click");
};
$(document).ready(function () {
    main();
});