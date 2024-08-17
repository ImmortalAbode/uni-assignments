if (WScript.Arguments.Count() == 4)
{
	var fromDir = WScript.Arguments(0);	//Исходный каталог (путь + имя). 
	var sourcefile = WScript.Arguments(1);	//Исходный файл (имя) (имеет путь исходного каталога).
	var toDir = WScript.Arguments(2);	//Результирующий каталог (путь + имя).
	var resfile = WScript.Arguments(3);	//Файл с результатами процедуры (имя) (имеет путь результирующего каталога).

	var shell = WScript.CreateObject("WScript.Shell");

	//3 Переименование каталогов:
	//3.1 Создать исходный каталог;
	var strFromDir = "%COMSPEC% /C mkdir " + "\"" + fromDir + "\"";
	WScript.Echo(strFromDir);
	shell.Run(strFromDir);

	//3.2 С помощью Блокнота создать исходный файл;
	var strSourceFile = "%WINDIR%\\notepad.exe " + "\"" + fromDir + "\\" + sourcefile + "\"";
	WScript.Echo(strSourceFile)
	shell.Run(shell.ExpandEnvironmentStrings(strSourceFile),1,true);

	//3.3 Скопировать исходный каталог в результирующий каталог;
	//3.3.1 Создание результирующего каталога.
	var strToDir = "%COMSPEC% /C mkdir " + "\"" + toDir + "\"";
	WScript.Echo(strToDir);
	shell.Run(strToDir);
	//3.3.2 Переименование исходного каталога в результирующий каталог.
	var strRenameDir = "%COMSPEC% /K move " + "\"" + fromDir + "\" \"" + toDir + "(1)\"";
	fromDir = toDir + "(1)";
	WScript.Echo(strRenameDir);
	shell.Run(strRenameDir);
	//3.3.3 Создание результирующего файла.
	var strResFile = "%WINDIR%\\notepad.exe " + "\"" + toDir + "\\" + resfile + "\"";
	WScript.Echo(strResFile);
	shell.Run(shell.ExpandEnvironmentStrings(strResFile),1,true);

	//3.4 Изменить атрибуты файла в результирующем каталоге;
	//Добавление атрибута "Только чтение" и удаление атрибута "Архивный".
	var strChangeFileAttributesInResDir = "%COMSPEC% /C attrib +R -A " + "\"" + toDir + "\\" + sourcefile + "\"";
	WScript.Echo(strChangeFileAttributesInResDir);
	shell.Run(strChangeFileAttributesInResDir);

	//3.5 Вывести оглавление исходного и результирующего каталогов;
	//3.5.1 Оглавление исходного каталога.
	var strFromDirContents = "%COMSPEC% /K dir /w " + "\"" + fromDir + "\"";
	WScript.Echo(strFromDirContents);
	shell.Run(strFromDirContents);
	//3.5.2 Оглавление результирующего каталога.
	var strToDirContents = "%COMSPEC% /K dir /w " + "\"" + toDir + "\"";
	WScript.Echo(strToDirContents);
	shell.Run(strToDirContents);

	//3.6 Вывести содержимое файла результирующего каталога; 
	var strToDirFileContents = "%COMSPEC% /K type " + "\"" + fromDir + "\\" + sourcefile + "\"";
	WScript.Echo(strToDirFileContents);
	shell.run(strToDirFileContents);

	//3.7 Перенаправление результатов выполнения процедур в результирующий файл.
	//3.1.
	shell.Run("%COMSPEC% /C echo " + strFromDir + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	//3.2.
	shell.Run("%COMSPEC% /C echo " + strSourceFile + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	//3.3.1.
	shell.Run("%COMSPEC% /C echo " + strToDir + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	//3.3.2.
	shell.Run("%COMSPEC% /C echo " + strRenameDir + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	//3.3.3.
	shell.Run("%COMSPEC% /C echo " + strResFile + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	//3.4
	shell.Run("%COMSPEC% /C echo " + strChangeFileAttributesInResDir + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	//3.5.1.
	shell.Run("%COMSPEC% /C echo " + strFromDirContents + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	shell.Run("%COMSPEC% /C dir /w " + "\"" + fromDir + "\"" + ">>\"" + toDir + "\\" + resfile + "\"");
	//3.5.2.
	shell.Run("%COMSPEC% /C echo " + strToDirContents + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	shell.Run("%COMSPEC% /C dir /w " + "\"" + toDir + "\"" + ">>\"" + toDir + "\\" + resfile + "\"");
	//3.6.
	shell.Run("%COMSPEC% /C echo " + strToDirFileContents + ">>" + "\"" + toDir + "\\" + resfile + "\"");
	shell.Run("%COMSPEC% /C type " + "\"" + fromDir + "\\" + sourcefile + "\"" + ">>\"" + toDir + "\\" + resfile + "\"");
}
else
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <from_folder_path> " + "<source_file_name>.txt" + " <to_folder_path> " + " <result_file_name>.doc");