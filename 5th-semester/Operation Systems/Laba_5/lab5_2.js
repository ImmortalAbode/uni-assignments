//Запуск по указанному пути заданной процедуры в выбранном режиме запуска.
if (WScript.Arguments.Count() == 3)
{
	var path = WScript.Arguments(0);
	var filename = WScript.Arguments(1);
	var mode = WScript.Arguments(2);
	
	//Открытие соответствующей процедуры в Блокноте.
	var shell = WScript.CreateObject("WScript.Shell");
	shell.Run(("%WINDIR%\\notepad.exe " + path + filename),1,true);
	
	//Выполнение процедуры в зависимости от выбранного режима запуска процедуры.
	if (mode == "cmd") //Консоль.
	{
		WScript.Echo("%COMSPEC% /K cscript " + "\"" + path + filename + "\"");
		shell.Run("%COMSPEC% /K cscript " + "\"" + path + filename + "\"");
	}
	else if (mode == "window")//Окно.
	{
		WScript.Echo("%COMSPEC% /K wscript " + "\"" + path + filename + "\"");
		//"& exit" закрывает всплывающее окно консоли при запуске заданной процедуры в оконном режиме.
		shell.run("%COMSPEC% /K wscript " + "\"" + path + filename + "\"" + "& exit");	
	}
	else
		WScript.Echo("Ошибка выбора запуска процедуры (cmd/window).");
	
}
else
{
	WScript.Echo("Указано неверное количество аргументов командной строки.");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <path> " + "<filename>.js" + " <mode>.");
}