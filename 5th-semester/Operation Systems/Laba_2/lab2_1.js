//Вычисление факториала рекурсивно.
function factorial(number)
{
	if (number <=1)
		return 1;
	else
		return number*factorial(number-1);
}

//Вывод информации о количестве первых членов заданного ряда.
var n = 3;
WScript.Echo("Число n (первые n членов ряда) =", n);

//Вывод информации о значении переменной x.
var x = 10;
WScript.Echo("Переменная x =", x);

//Переменная для посчета суммы первых n членов ряда.
var result = 0;

//Переменные для подсчета n!, (2*n)! и x^n.
var pow_to_n;
var pow_to_double_n;
var pow_to_x = 1;

//Вычисление суммы первых n членов заданного ряда.
for (var i=1;i<=n;i++)
{
	pow_to_n = factorial(i);
	pow_to_double_n = factorial(2*i);
	pow_to_x *= x;
	result += ((pow_to_n*pow_to_n) / pow_to_double_n) * pow_to_x;
}
//Вывод полученной суммы.
WScript.Echo("Ваша сумма " + n + " первых членов заданного ряда равна " + result + ".");
