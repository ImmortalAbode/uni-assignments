var main = function (toDoObjects) {
    "use strict";
    var toDos = toDoObjects.map(function (toDo) {
        return toDo.description;
    });
    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            var $element = $(element),
                $content;
            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();
            if ($element.parent().is(":nth-child(1)")) {
                var i;
                $content = $("<ul>");
                for (i = toDos.length; i > -1; i--) {
                    $content.append($("<li>").text(toDos[i]));
                }
            } else if ($element.parent().is(":nth-child(2)")) {
                $content = $("<ul>");
                toDos.forEach(function (todo) {
                    $content.append($("<li>").text(todo));
                });
            } else if ($element.parent().is(":nth-child(3)")) {
                /*ЭТО КОД ДЛЯ ВКЛАДКИ ТЕГИ*/
                console.log("Щелчок на вкладке Теги");
                var organizeByTags = function (toDoObjects) {
                    //Проход по исходной структуре файла todos.json и записывание всех уникальных тегов в массив tags.
                    var tags = [];
                    toDoObjects.forEach(function (toDo) {
                        toDo.tags.forEach(function (tag) {
                            if (tags.indexOf(tag) === -1) {
                                tags.push(tag);
                            }
                        });
                    });
                    //Создание нового массива, применяя функцию function (tag) {...} к каждому элементу созданного массива tags (к кажому тегу формируем массив дел).
                    var tagObjects = tags.map(function (tag) {
                        // Проходя по исходной структуре toDoObjects файла todos.json, мы создаем новый массив toDosWithTag, который хранит описание дел по тегам.
                        var toDosWithTag = [];
                        //Если тег текущего дела структуры совпадает с рассматриваемым элементом массива tags, то добавляем его в массив toDosWithTag.
                        toDoObjects.forEach(function (toDo) {
                            if (toDo.tags.indexOf(tag) !== -1) {
                                toDosWithTag.push(toDo.description);
                            }
                        });
                        //Возвращаем новую структуру для текущего тега, которая для каждого тега сформировала список дел.
                        return { "name": tag, "toDos": toDosWithTag };
                    });
                    //Вызываем функцию, возвращающую новую структуру.
                    return tagObjects;
                };
                var organizedByTag = organizeByTags(toDoObjects);
                organizedByTag.forEach(function (tag) {
                    var $tagName = $("<h3>").text(tag.name),
                        $content = $("<ul>");
                    tag.toDos.forEach(function (description) {
                        var $li = $("<li>").text(description);
                        $content.append($li);
                    });
                    $("main .content").append($tagName);
                    $("main .content").append($content);
                });
            } else if ($element.parent().is(":nth-child(4)")) {
                var $input = $("<input>").addClass("description"),
                    $inputLabel = $("<p>").text("Описание"),
                    $tagInput = $("<input>").addClass("tags"),
                    $tagLabel = $("<p>").text("Теги"),
                    $button = $("<button>").text("+");
                $content = $("<div>");
                $content.append($inputLabel);
                $content.append($input);
                $content.append($tagLabel);
                $content.append($tagInput);
                $content.append($button);
                var addTaskFromInputBox = function () {
                    if ($input.val() !== "") {
                        toDos.push($input.val());
                        $input.val("");
                    }
                };
                $button.on("click", function () {
                    var description = $input.val(),
                        //Разделение тегов по запятым.
                        tags = $tagInput.val().split(",");
                    toDoObjects.push({ "description": description, "tags": tags });
                    // Обновление списка задач
                    toDos = toDoObjects.map(function (toDo) {
                        return toDo.description;
                    });
                    $input.val("");
                    $tagInput.val("");
                });
            }
            $("main .content").append($content);
            return false;
        });
    });
    $(".tabs a:first-child span").trigger("click");
};
$(document).ready(function () {
    $.getJSON("todos.json", function (toDoObjects) {
        main(toDoObjects);
    });
});