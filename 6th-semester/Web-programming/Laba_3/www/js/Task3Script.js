function addDigit() {
    // Получение введенных пользователем числа n и цифры k.
    var numberN = document.getElementById('numberN').value;
    var digitK = document.getElementById('digitK').value;

    // Проверка на натуральность числа n и на значение от 0 до 9 цифры k.
    if (validateNumberFormat(numberN) && validateDigitFormat(digitK)) {
        // Создание нового числа.
        var newNumber = digitK + numberN + digitK;

        // Вывод результата в диалоговом окне.
        var resultMessage = 'Было введено число:\nn = ' + numberN + '\nи цифра k = ' + digitK + '\n\n';

        resultMessage += 'Новое число: ' + newNumber;
        alert(resultMessage);
    }
    else {
        alert("Ошибка ввода! Проверьте, что число n введено корретно и является натуральным и цифра k введена корректно (цифра считается цифрой от 0 до 9).")
    }
}
function validateNumberFormat(number) {
    var regex = /^[1-9]\d*$/;
    return regex.test(number);
}

function validateDigitFormat(digit) {
    var regex = /^[0-9]$/;
    return regex.test(digit);
}