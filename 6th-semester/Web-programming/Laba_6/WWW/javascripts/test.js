var toDoObjects = [
    {
        "description": "Купить продукты",
        "tags": ["шопинг", "рутина"]
    },
    {
        "description": "Сделать несколько новых задач",
        "tags": ["писательство", "работа"]
    },
    {
        "description": "Подготовиться к лекции в понедельник",
        "tags": ["работа", "преподавание"]
    },
    {
        "description": "Ответить на электронные письма",
        "tags": ["работа"]
    },
    {
        "description": "Вывести Грейси на прогулку в парк",
        "tags": ["рутина", "питомцы"]
    },
    {
        "description": "Закончить писать книгу",
        "tags": ["писательство", "работа"]
    },
];
var organizeByTags = function (toDoObjects) {
    console.log("organizeByTags вызвана");
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
var main = function () {
    "use strict";
    //Получение результата функции organizeByTags.
    var tagObjects = organizeByTags(toDoObjects);

    //.Проход по объектам тегов и добавление их содержимого в тело документа
    tagObjects.forEach(function (tagObject) {
        var $tagName = $("<h3>").text(tagObject.name), //Создание заголовка тега.
            $content = $("<ul>"); //Создание списка задач.

        //Добавление каждой задачи в список.
        tagObject.toDos.forEach(function (description) {
            $content.append($("<li>").text(description));
        });

        //Добавление заголовка и списка в тело документа.
        $("body").append($tagName).append($content);
    });
};
$(document).ready(main);