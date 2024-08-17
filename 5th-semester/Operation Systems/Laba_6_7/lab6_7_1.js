if ((WScript.Arguments.Count() == 5 && WScript.Arguments(4) == "false" ) || (WScript.Arguments.Count() == 6 && WScript.Arguments(4) == "true"))
{
	var sourceDir = WScript.Arguments(0);	//�������� ������� (���� + ���). 
	var sourceFile = WScript.Arguments(1);	//�������� ���� (���) (����� ���� ��������� ��������).
	var resDir = WScript.Arguments(2);	//�������������� ������� (���� + ���).
	var resFile = WScript.Arguments(3);     //�������������� ���� (���) (����� ���� ��������������� ��������).
	var toFile = WScript.Arguments(4);	//������������� ���������� ��������� � ���� (true) ��� ��� (false).
	var toFile_name;			//��� �����, � ������� ����� ��������� ��� ���������������� ����������.
	if (WScript.Arguments.Count() == 6)
		toFile_name = WScript.Arguments(5);
	
	var fso = WScript.CreateObject("Scripting.FileSystemObject"); //��� ������ ��������������� � ���������/���������/���������� ��������� � ������.
	var shell = WScript.CreateObject("WScript.Shell"); //��� ������ � ����������� ��������� (� ������ ������ ������ � ������������ ���������� �������).

	//4 �������������� ������:
	//4.1 ������� �������� �������;
	fso.CreateFolder(sourceDir);
	WScript.Echo("fso.CreateFolder(" + sourceDir + ")");

	var strNoteFile = sourceDir + "\\" + sourceFile;

	//4.2 � ������� �������� ������� �������� ����;
	var createNoteFile = "%WINDIR%\\notepad.exe " + "\"" + strNoteFile + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(createNoteFile),1,true);
	WScript.Echo(createNoteFile);

	//4.3 ������� �������������� �������;
	fso.CreateFolder(resDir);
	WScript.Echo("fso.CreateFolder(" + resDir + ")");
		
	//4.4 ����������� �������� ���� � �������������� �������;
	fso.CopyFile(strNoteFile, resDir + "\\", true);
	WScript.Echo("fso.CopyFile(" + strNoteFile + ", " + resDir + "\\, true)");
	
	//4.5 ������������� �������� ���� � �������������� ��������;
	fso.GetFile(resDir + "\\" + sourceFile).Name = resFile;
	WScript.Echo("fso.GetFile(" + resDir + "\\" + sourceFile + ").Name = " + resFile);

	//4.6 ��������� ������� ��� �������������� ����� � �������������� ��������;
	var editResFile = "%WINDIR%\\notepad.exe " + "\"" + resDir + "\\" + resFile + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(editResFile), 1, true);
	WScript.Echo(editResFile);
	
	//4.7 �������� ����� � �������� � �������������� ���������;
	var file_1 = fso.GetFile(sourceDir + "\\" + sourceFile); 
	var file_2 = fso.GetFile(resDir + "\\" + resFile); 

	file_1 = fso.OpenTextFile(file_1, 1, true, 0); 
	file_2 = fso.OpenTextFile(file_2, 1, true, 0);

	var text_file_1 = file_1.ReadAll();
	var text_file_2 = file_2.ReadAll();
	if (text_file_1 == text_file_2) 
		WScript.Echo("����� ����������."); 
	else
		WScript.Echo("����� ������.");

	//4.8 ��������������� ����������� ���������� �������� � �������������� ����.
	if (WScript.Arguments.Count() == 6)
	{
		var tf = fso.CreateTextFile(toFile_name, true);
		tf.WriteLine("���������� ������ ���������:");
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
			tf.WriteLine("����� ����������.");
		else
			tf.WriteLine("����� ������.");
	}
}
else
{
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <source_folder_path> " + "<source_file_name>.txt" + " <result_folder_path>" + " <result_file_name>.txt" + " <mode_to_file>(true/false)" + " <to_file_name>.txt (��� true)");
}
