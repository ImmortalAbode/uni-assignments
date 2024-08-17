var main = function (bookRecordObjects) {
    "use strict";
    var bookRecords = bookRecordObjects.map(function (brs) {
        var authors = [];
        brs.authors.forEach(function (author) {
            authors.push(author);
        });
        return [brs.returnDate, brs.fullName, brs.title, brs.publishingOffice, brs.year, authors];
    });
    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            var $element = $(element),
                $content;
            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();
            if ($element.parent().is(":nth-child(1)")) {
                $content = $("<div>");
                for (var i = bookRecords.length - 1; i > -1; i--) {
                    var $recordClassDiv = $("<div>").addClass("recordClass");

                    $recordClassDiv.append($("<h4>").text("Дата возврата: " + bookRecords[i][0]));
                    $recordClassDiv.append($("<h4>").text("ФИО держателя: " + bookRecords[i][1]));
                    $recordClassDiv.append($("<h4>").text("Название: " + bookRecords[i][2]));
                    $recordClassDiv.append($("<h4>").text("Издательство: " + bookRecords[i][3]));
                    $recordClassDiv.append($("<h4>").text("Год издания: " + bookRecords[i][4]));

                    $recordClassDiv.append($("<p>").text("Автор(-ы): "));
                    var $author_ul = $("<ul>");
                    for (var j = 0; j < bookRecords[i][5].length; j++) {
                        var $author_li = $("<li>").text(bookRecords[i][5][j]);
                        $author_ul.append($author_li);
                    }
                    $recordClassDiv.append($author_ul);
                    $content.append($recordClassDiv);
                }
            } else if ($element.parent().is(":nth-child(2)")) {
                $content = $("<div>");
                for (var i = 0; i < bookRecordObjects.length; i++) {
                    var $recordClassDiv = $("<div>").addClass("recordClass");

                    $recordClassDiv.append($("<h4>").text("Дата возврата: " + bookRecords[i][0]));
                    $recordClassDiv.append($("<h4>").text("ФИО держателя: " + bookRecords[i][1]));
                    $recordClassDiv.append($("<h4>").text("Название: " + bookRecords[i][2]));
                    $recordClassDiv.append($("<h4>").text("Издательство: " + bookRecords[i][3]));
                    $recordClassDiv.append($("<h4>").text("Год издания: " + bookRecords[i][4]));

                    $recordClassDiv.append($("<p>").text("Автор(-ы): "));
                    var $author_ul = $("<ul>");
                    for (var j = 0; j < bookRecords[i][5].length; j++) {
                        var $author_li = $("<li>").text(bookRecords[i][5][j]);
                        $author_ul.append($author_li);
                    }
                    $recordClassDiv.append($author_ul);
                    $content.append($recordClassDiv);
                }
            } else if ($element.parent().is(":nth-child(3)")) {
                $content = $("<div>");
                var returnDateAndPerson = {};
                for (var i = 0; i < bookRecordObjects.length; i++) {
                    var key = bookRecordObjects[i].returnDate + "|" + bookRecordObjects[i].fullName;
                    if (returnDateAndPerson.hasOwnProperty(key)) {
                        returnDateAndPerson[key].push(bookRecordObjects[i]);
                    } else {
                        returnDateAndPerson[key] = [bookRecordObjects[i]];
                    }
                }

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
                            $recordClassDiv.append($("<h4>").text("Автор(-ы): " + additional_info.authors.join(", ")));
                            $returnDatePersonClassDiv.append($recordClassDiv);
                        });
                        $content.append($returnDatePersonClassDiv);
                    }
                }
            } else if ($element.parent().is(":nth-child(4)")) {
                $content = $("<div>");
                var authors = {};
                for (var i = 0; i < bookRecordObjects.length; i++) {
                    for (var j = 0; j < bookRecordObjects[i].authors.length; j++) {
                        var author = bookRecordObjects[i].authors[j];
                        if (authors.hasOwnProperty(author)) {
                            authors[author].push(bookRecordObjects[i]);
                        } else {
                            authors[author] = [bookRecordObjects[i]];
                        }
                    }
                }

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
            } else if ($element.parent().is(":nth-child(5)")) {
                //Добавление необходимых элементов.
                var $returnDateLabel = $("<p>").text("Дата возврата: "),
                    $returnDateInput = $("<input>").addClass("returnDate"),
                    $fullNameLabel = $("<p>").text("ФИО держателя: "),
                    $fullNameInput = $("<input>").addClass("fullName"),
                    $titleLabel = $("<p>").text("Название: "),
                    $titleInput = $("<input>").addClass("title"),
                    $publishingOfficeLabel = $("<p>").text("Издательство: "),
                    $publishingOfficeInput = $("<input>").addClass("publishingOffice"),
                    $yearLabel = $("<p>").text("Год издания: "),
                    $yearInput = $("<input>").addClass("year"),
                    $authorsLabel = $("<p>").text("Автор(-ы): "),
                    $authorsInput = $("<input>").addClass("authors"),
                    $button = $("<button>").text("Добавить новую запись");

                $content = $("<div>").addClass("addNewData");
                $content.append($returnDateLabel);
                $content.append($returnDateInput);
                $content.append($fullNameLabel);
                $content.append($fullNameInput);
                $content.append($titleLabel);
                $content.append($titleInput);
                $content.append($publishingOfficeLabel);
                $content.append($publishingOfficeInput);
                $content.append($yearLabel);
                $content.append($yearInput);
                $content.append($authorsLabel);
                $content.append($authorsInput);
                $content.append($button);

                //Добавление новой записи библиотеки.
                var addNewDataFromInputBox = function () {
                    if ($returnDateInput.val() !== "" && $fullNameInput.val() !== "" && $titleInput.val() !== "" && $publishingOfficeInput.val() !== "" && $yearInput.val() !== "" && $authorsInput.val() !== "") {
                        //Обработка данных при нажатии кнопки.
                        var date = $returnDateInput.val();
                        var person = $fullNameInput.val();
                        var title = $titleInput.val();
                        var office = $publishingOfficeInput.val();
                        var year = $yearInput.val();
                        var authors = $authorsInput.val().split(",");
                        var taskData = [date, person, title, office, year, authors];
                        bookRecords.push(taskData);
                        bookRecordObjects.push({
                            "returnDate": date,
                            "fullName": person,
                            "title": title,
                            "publishingOffice": office,
                            "year": year,
                            "authors": authors
                        });
                        $returnDateInput.val("");
                        $fullNameInput.val("");
                        $titleInput.val("");
                        $publishingOfficeInput.val("");
                        $yearInput.val("");
                        $authorsInput.val("");
                    }
                }
                $button.on("click", function (event) {
                    addNewDataFromInputBox();
                });
                //Добавление записи библиотеки при нажатии Enter в одном из полей ввода.
                $returnDateInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $fullNameInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $titleInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $publishingOfficeInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $yearInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $authorsInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
            }
            $("main .content").append($content);
            return false;
        });
    });
    $(".tabs a:first-child span").trigger("click");
};
$(document).ready(function () {
    $.getJSON("library.json", function (bookRecordObjects) {
        main(bookRecordObjects);
    });
});