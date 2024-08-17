/*ВМЕСТО ФУНКЦИЙ ИСПОЛЬЗУЮТСЯ ФУНКЦИОНАЛЬНЫЕ ЛИТЕРАЛЫ*/

/*-----------------------------------------------------------------------------------------------------*/
/*ЗАДАНИЯ С ДАТАМИ*/

//Функция-обработчик для инициализации вычисления запрошенной даты по нажатию на интерактивный элемент.
var dateCalculator = function () {
    // Установка текста для указанных элементов документа.
    document.getElementById("week_day").textContent = getWeekDay();
    document.getElementById("day_month").textContent = getDayMonth();
    document.getElementById("year").textContent = getYear();
    document.getElementById("required_days").textContent = getSessionDays();
}
//Функция-исполнитель для вычисления текущего дня недели при загрузке HTML-страницы.
var getWeekDay = function () {
    // Создаем массив для хранения названий дней недели.
    var daysOfWeek = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];

    // Получаем текущий день недели по номеру дня в неделе.
    var date = new Date();
    var dayIndex = date.getDay();
    var day_of_week = daysOfWeek[dayIndex];

    return day_of_week;
};
//Функция-исполнитель для вычисления текущего дня и месяца при загрузке HTML-страницы.
var getDayMonth = function () {
    // Создаем массив для хранения названий дней недели.
    var monthsOfYear = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];

    var date = new Date();

    var day = date.getDate();
    var month = date.getMonth();

    if (day < 10) {
        day = '0' + day;
    }

    return day + " " + monthsOfYear[month];
}
//Функция-исполнитель для вычисления текущего года при загрузке HTML-страницы.
var getYear = function () {
    var date = new Date();
    var year = date.getFullYear();

    return year;
}

//Функция-исполнитель для вычисления дней, оставшихся до сессии.
var getSessionDays = function () {

    var current_date = new Date();
    var session_date = new Date(2024, 5, 10);
    return Math.ceil((session_date - current_date) / (1000 * 60 * 60 * 24));
}


//Функция-обработчик для вычисления дней, прошедших с памятной даты.
var getMemorableDate = function () {
    document.getElementById("memorable_paragraph").innerText = calculateNumberDays();
}
//Функция-исполнитель для вычисления дней, прошедших с памятной даты.
var calculateNumberDays = function () {
    var memorableDate = prompt("Enter a memorable date for you (format: DD.MM.YYYY)", "04.03.2003");
    if (memorableDate !== null) {
        if (isValidDate(memorableDate)) {
            var parts = memorableDate.split('.');
            var entered_day = parseInt(parts[0]);
            var entered_month = parseInt(parts[1]);
            var entered_year = parseInt(parts[2]);
            var entered_date = new Date(entered_year, entered_month - 1, entered_day);
            var current_date = new Date();
            required_days = Math.ceil((current_date - entered_date) / (1000 * 60 * 60 * 24));
            //Проверка логической корректности вводимой даты.
            if (entered_date > current_date) {
                alert("The entered date should be in the past.");
                return;
            }
            if (entered_month < 1 || entered_month > 12) {
                alert("Incorrect month! Please enter a month between 01 and 12.");
                return;
            }
            var last_day_of_month = new Date(entered_year, entered_month, 0).getDate();
            if (entered_day < 1 || entered_day > last_day_of_month) {
                alert("Incorrect day! Please enter a day between 01 and " + last_day_of_month + " for the entered month.");
                return;
            }
            if (required_days > 365) {
                return required_days;
            }
            else {
                alert("The number of days must be greater than 365. Current number of days:" + required_days);
                return;
            }
        } else {
            alert("Incorrect date format! Please enter the date in DD.MM.YYYY format.");
            return;
        }
    }
}
//Функция-исполнитель для проверки корректности ввода даты.
var isValidDate = function (dateString) {
    var pattern = /^\d{2}\.\d{2}\.\d{4}$/;
    return pattern.test(dateString);
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/*ЗАДАНИЕ ИЗ ЛАБОРАТОРНОЙ РАБОТЫ №3*/
//Функция-обработчик для проверки чисел.
var executeNumber = function () {
    document.getElementById("result_text").textContent = checkNumber();
}
//Функция-исполнитель для проверки чисел.
var checkNumber  = function () {
    // Получение введенного пользователем числа N.
    var numberN = document.getElementById('numberN').value;

    // Проверка на натуральность числа N.
    if (validateNumberFormat(numberN)) {
        var numberM = getNumberM(numberN);
        //Вывод результатов.
        var resultMessage = '';
        resultMessage += 'A number has been entered: N = ' + numberN + '. New number: M = ' + numberM + '.';
        return resultMessage;
    }
    else
        alert("Input Error! Check that the number N is entered correctly and is a natural number.")
}
//Функция-исполнитель для решения поставленной задачи.
var getNumberM = function (number) {
    //Размещение данных для решения поставленной задачи в массиве.
    var numberArray = number.toString().split('');
    var minDigit = numberArray[0];

    //Решение задачи.
    for (var i = 1; i < numberArray.length; i++)
        if (numberArray[i] < minDigit)
            minDigit = numberArray[i];

    var copyArrayM = numberArray;
    copyArrayM[copyArrayM.length - 1] = minDigit;
    var numberM = copyArrayM.join('');

    return numberM;
}
//Функция-исполнитель проверки корректности введенных данных.
var validateNumberFormat = function(number) {
    var regex = /^[1-9]\d*$/;
    return regex.test(number);
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/*ЗАДАНИЕ С ПОСЛЕДОВАТЕЛЬНОСТЬЮ*/
//Вычисление суммы числовой последовательности.
// Функция-обработчик ввода данных.
var enteredData = function () {
    document.getElementById("calculated_sum").innerText = dialogWindows();
}
//Функция-исполнитель подряд идущих поочередно диалоговых окон.
var dialogWindows = function() {
    var firstTerm = prompt("Введите номер первого члена");
    if (validateNumberFormat(firstTerm)) {
        document.getElementById("first_term").value = firstTerm;
        var countTerm = prompt("Введите количество слагаемых последующих членов");
        if (validateNumberFormat(countTerm)) {
            document.getElementById("count_term").value = countTerm;
        }
        else
            alert("Ошибка ввода! Проверьте, что количество слагаемых последующих членов введено корректно и является натуральным.")
    }
    else
        alert("Ошибка ввода! Проверьте, что номер первого члена введен корректно и является натуральным.")

}
// Функция-обработчик вычисления суммы..
var calculateSum = function () {
    document.getElementById("calculated_sum").innerText = getSum();
}
//Функция-исполнитель подсчета числовой последовательности.
var getSum = function() {
    var first = parseInt(document.getElementById("first_term").value);
    var count = parseInt(document.getElementById("count_term").value);
    if (validateNumberFormat(first) && validateNumberFormat(count)) {
        var sum = 0;
        for (var i = 0; i < count; i++) {
            sum += Math.pow(first + i - 2, 2);
        }
        //Формирование сообщения вывода.
        var resultMessage = '';
        resultMessage += "Сумма " + count + " членов последовательности, начиная с (со) " + first + ": " + sum + ".";
        return resultMessage;
    }
    else
        alert("Сначала нужно ввести номер первого члена числовой последовательности и их количество!")
}