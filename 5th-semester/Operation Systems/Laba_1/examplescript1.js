// conddemo.js
var	weekday=new Date().getDay();// получение дн€ недели
var	str;
	switch(weekday)
	{
	case 0:
		str="седьмой";
		break;
	case 1:
		str="первый";
		break;
	case 2:
		str="второй";
		break;
	case 3:
		str="третий";
		break;
	case 4:
		str="четвЄртый";
		break;
	case 5:
		str="п€тый";
		break;
	case 6:
		str="шестой";
		break;
	default:
		str="неизвестный";
	}
	WScript.Echo("—егодн€ "+str+" день недели ("+
		( (weekday==0||weekday==6)?"выходной":"рабочий")+")");

