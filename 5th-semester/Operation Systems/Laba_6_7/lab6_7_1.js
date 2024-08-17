if ((WScript.Arguments.Count() == 5 && WScript.Arguments(4) == "false" ) || (WScript.Arguments.Count() == 6 && WScript.Arguments(4) == "true"))
{
	var sourceDir = WScript.Arguments(0);	//Исходный каталог (путь + имя). 
	var sourceFile = WScript.Arguments(1);	//Исходный файл (имя) (имеет путь исходного каталога).
	var resDir = WScript.Arguments(2);	//Результирующий каталог (путь + имя).
	var resFile = WScript.Arguments(3);     //Результирующий файл (имя) (имеет путь результирующего каталога).
	var toFile = WScript.Arguments(4);	//Перенаправить результаты процедуры в файл (true) или нет (false).
	var toFile_name;			//Имя файла, в котором будут храниться все перенаправленные результаты.
	if (WScript.Arguments.Count() == 6)
		toFile_name = WScript.Arguments(5);
	
	var fso = WScript.CreateObject("Scripting.FileSystemObject"); //Для работы непосредственно с созданием/удалением/изменением каталогов и файлов.
	var shell = WScript.CreateObject("WScript.Shell"); //Для работы с переменными окружения (в данном случае запуск и конфигурация приложения Блокнот).

	//4 Переименование файлов:
	//4.1 Создать исходный каталог;
	fso.CreateFolder(sourceDir);
	WScript.Echo("fso.CreateFolder(" + sourceDir + ")");

	var strNoteFile = sourceDir + "\\" + sourceFile;

	//4.2 С помощью Блокнота создать исходный файл;
	var createNoteFile = "%WINDIR%\\notepad.exe " + "\"" + strNoteFile + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(createNoteFile),1,true);
	WScript.Echo(createNoteFile);

	//4.3 Создать результирующий каталог;
	fso.CreateFolder(resDir);
	WScript.Echo("fso.CreateFolder(" + resDir + ")");
		
	//4.4 Скопировать исходный файл в результирующий каталог;
	fso.CopyFile(strNoteFile, resDir + "\\", true);
	WScript.Echo("fso.CopyFile(" + strNoteFile + ", " + resDir + "\\, true)");
	
	//4.5 Переименовать исходный файл в результирующем каталоге;
	fso.GetFile(resDir + "\\" + sourceFile).Name = resFile;
	WScript.Echo("fso.GetFile(" + resDir + "\\" + sourceFile + ").Name = " + resFile);

	//4.6 Запустить Блокнот для редактирования файла в результирующем каталоге;
	var editResFile = "%WINDIR%\\notepad.exe " + "\"" + resDir + "\\" + resFile + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(editResFile), 1, true);
	WScript.Echo(editResFile);
	
	//4.7 Сравнить файлы в исходном и результирующем каталогах;
	var file_1 = fso.GetFile(sourceDir + "\\" + sourceFile); 
	var file_2 = fso.GetFile(resDir + "\\" + resFile); 

	file_1 = fso.OpenTextFile(file_1, 1, true, 0); 
	file_2 = fso.OpenTextFile(file_2, 1, true, 0);

	var text_file_1 = file_1.ReadAll();
	var text_file_2 = file_2.ReadAll();
	if (text_file_1 == text_file_2) 
		WScript.Echo("Файлы одинаковые."); 
	else
		WScript.Echo("Файлы разные.");

	//4.8 Перенаправление результатов выполнения процедур в результирующий файл.
	if (WScript.Arguments.Count() == 6)
	{
		var tf = fso.CreateTextFile(toFile_name, true);
		tf.WriteLine("Результаты работы программы:");
		//4.1.
		tf.WriteLine("fso.CreateFolder(" + sourceDir + ")");
		//4.2.
		tf.WriteLine("shell.Run((createNoteFile), 1, true)");
		//4.3.
		tf.WriteLine("fso.CreateFolder(" + resDir + ")");
		//4.4.
		tf.WriteLine("fso.CopyFile(" + strNoteFile + ", " + resDir + "\\" + ", true)");
		//4.5.
		tf.WriteLine("fso.GetFile(" + resDir + "\\" + sourceFile + ").Name = " + resFile);
		//4.6.
		tf.WriteLine("shell.Run(shell.ExpandEnvironmentStrings(editResFile), 1, true)");
		//4.7.
		if (text_file_1 == text_file_2)
			tf.WriteLine("Файлы одинаковые.");
		else
			tf.WriteLine("Файлы разные.");
	}
}
else
{
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <source_folder_path> " + "<source_file_name>.txt" + " <result_folder_path>" + " <result_file_name>.txt" + " <mode_to_file>(true/false)" + " <to_file_name>.txt (для true)");
}
