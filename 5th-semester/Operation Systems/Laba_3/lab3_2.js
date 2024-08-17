if (WScript.Arguments.Count()==3)
{
	//Вывод информации о количестве первых n членов заданного ряда.
	var n = WScript.Arguments(0);
	WScript.Echo("Число n (первые n членов ряда) =", n);
	
	//Вывод информации о значении переменной x.
	var x = WScript.Arguments(1);
	WScript.Echo("Переменная x =", x);
	
	//Вывод информации о значении переменной p.
	var p = WScript.Arguments(2);
	WScript.Echo("Переменная p =", p);
	
	//Переменная для подсчета суммы первых n членов заданного ряда.
	var summ = 0;
	
	//Вычисление суммы первых n членов заданного ряда.
	for (i=1;i<=n;i++)
	{
		summ += (1/Math.pow(i,p))*Math.pow(1-(x*Math.log(i))/i,i);
	}
	//Вывод полученной суммы.
	WScript.Echo("Ваша сумма " + n + " первых членов ряда равна " + summ + ".");
}
else
	WScript.Echo("Использование: cscript //nologo "+ WScript.ScriptFullName + " 2 1 3");
