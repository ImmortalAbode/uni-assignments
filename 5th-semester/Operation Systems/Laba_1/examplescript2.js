// Применения операторов присваивания.
var x = 121;	//десятичная целочисленная переменная
var y = 22;	// десятичная целочисленная переменная
var z = 0;
z = x;
WScript.Echo(z);	//выводит 121
z+=y;
WScript.Echo(z);	//выводит 143
z-=y;
WScript.Echo(z);	//выводит 121
z *= 2;
WScript.Echo(z);	//выводит 242
z /= 4;
WScript.Echo(z);	// выводит 60,5
z %= 5;
WScript.Echo(z);	// выводит 0,5