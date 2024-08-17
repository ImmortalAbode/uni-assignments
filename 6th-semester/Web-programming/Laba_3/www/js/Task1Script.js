function calculateTime() {
    // Получение введеного времени пользователем.
    var userInput = document.getElementById("timeInput").value;

    //Проверка верного ввода времени.
    if (validateTimeFormat(userInput)) {
        // Разбитие введеного времени на часы и минуты.
        var inputTimeArray = userInput.split(":");
        var inputHours = parseInt(inputTimeArray[0]);
        var inputMinutes = parseInt(inputTimeArray[1]);

        // Переменные для расчета нового времени.
        var newMinutes = inputMinutes + 1; //Увеличение числа минут на 1.
        var newHours = inputHours;

        //Проверка 3-х условий.
        if (newMinutes % 60 == 0) {
            newMinutes = 0;
            newHours++;
            if (newHours >= 24) {
                newHours = 0;
            }
        }

        //Форматирование времени:
        var newTime = formatTime(newHours) + ":" + formatTime(newMinutes);

        // Вывод результата в диалоговом окне
        alert("Введенное время: " + userInput + "\nВремя через минуту: " + newTime);
    }
    else {
        // Вывод сообщения об ошибке в формате времени
        alert("Ошибка ввода времени. Пожалуйста, введите время в формате HH:MM.");
    }
}
function validateTimeFormat(time) {
    var regex = /^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$/;
    return regex.test(time);
}
function formatTime(time) {
    return (time < 10 ? "0" : "") + time;
}