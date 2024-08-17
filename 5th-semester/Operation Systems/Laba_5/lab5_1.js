//Вывод информации о заданной команде MS-DOS по указанному пути в указанный файл.
if (WScript.Arguments.count() == 3)
{
	//Инициализация необходимых экземпляров объекта String для последующего формирования команд MS-DOS.
	var command = WScript.Arguments(0);
	var path = WScript.Arguments(1);
	var filename = WScript.Arguments(2);
	
	//Инициализация необходимого экземпляра объекта WshShell и формирование строки команды.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /C help " + command + ">\"" + path + filename + ".\"";

	//Исполнение команды MS-DOS с помощью метода Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//Вывод информации о командах MS-DOS по указанному пути в заданный файл.
else if (WScript.Arguments.count() == 2)
{
	//Инициализация необходимых экземпляров объекта String для последующего формирования команд MS-DOS.
	var command = WScript.Arguments(0);
	var path = WScript.Arguments(1);

	var filename = 'defaultname.doc';
	
	//Инициализация необходимого экземпляра объекта WshShell и формирование строки команды.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /C help " + command + ">\"" + path + filename + ".\"";

	//Исполнение команды MS-DOS с помощью метода Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//Вывод информации о командах MS-DOS на консоль в отдельном окне.
else if (WScript.Arguments.count() == 1)
{
	//Инициализация необходимых экземпляров объекта String для последующего формирования команд MS-DOS.
	var command = WScript.Arguments(0);
	
	//Инициализация необходимого экземпляра объекта WshShell и формирование строки команды.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help " + command;	
	
	//Исполнение команды MS-DOS с помощью метода Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
else if (WScript.Arguments.count() == 0)
{
	//Инициализация необходимого экземпляра объекта WshShell и формирование строки команды.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help ";
	
	//Исполнение команды MS-DOS с помощью метода Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//Иначе вывод о допустимых командах данной процедуры.
else
{
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <command_name> " + "<file_path>" + " <file_name>.doc");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <command_name> " + "<file_path>");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <command_name> ");
	WScript.ECho("Использование: cscript //nologo " + WScript.ScriptFullName);
} 