if (WScript.Arguments.Count() == 4)
{
	var fromDir = WScript.Arguments(0);	//�������� ������� (���� + ���). 
	var sourcefile = WScript.Arguments(1);	//�������� ���� (���) (����� ���� ��������� ��������).
	var toDir = WScript.Arguments(2);	//�������������� ������� (���� + ���).
	var resfile = WScript.Arguments(3);	//���� � ������������ ��������� (���) (����� ���� ��������������� ��������).

	var shell = WScript.CreateObject("WScript.Shell");

	//3 �������������� ���������:
	//3.1 ������� �������� �������;
	var strFromDir = "%COMSPEC% /C mkdir " + "\"" + fromDir + "\"";
	WScript.Echo(strFromDir);
	shell.Run(strFromDir);

	//3.2 � ������� �������� ������� �������� ����;
	var strSourceFile = "%WINDIR%\\notepad.exe " + "\"" + fromDir + "\\" + sourcefile + "\"";
	WScript.Echo(strSourceFile)
	shell.Run(shell.ExpandEnvironmentStrings(strSourceFile),1,true);

	//3.3 ����������� �������� ������� � �������������� �������;
	//3.3.1 �������� ��������������� ��������.
	var strToDir = "%COMSPEC% /C mkdir " + "\"" + toDir + "\"";
	WScript.Echo(strToDir);
	shell.Run(strToDir);
	//3.3.2 �������������� ��������� �������� � �������������� �������.
	var strRenameDir = "%COMSPEC% /K move " + "\"" + fromDir + "\" \"" + toDir + "(1)\"";
	fromDir = toDir + "(1)";
	WScript.Echo(strRenameDir);
	shell.Run(strRenameDir);
	//3.3.3 �������� ��������������� �����.
	var strResFile = "%WINDIR%\\notepad.exe " + "\"" + toDir + "\\" + resfile + "\"";
	WScript.Echo(strResFile);
	shell.Run(shell.ExpandEnvironmentStrings(strResFile),1,true);

	//3.4 �������� �������� ����� � �������������� ��������;
	//���������� �������� "������ ������" � �������� �������� "��������".
	var strChangeFileAttributesInResDir = "%COMSPEC% /C attrib +R -A " + "\"" + toDir + "\\" + sourcefile + "\"";
	WScript.Echo(strChangeFileAttributesInResDir);
	shell.Run(strChangeFileAttributesInResDir);

	//3.5 ������� ���������� ��������� � ��������������� ���������;
	//3.5.1 ���������� ��������� ��������.
	var strFromDirContents = "%COMSPEC% /K dir /w " + "\"" + fromDir + "\"";
	WScript.Echo(strFromDirContents);
	shell.Run(strFromDirContents);
	//3.5.2 ���������� ��������������� ��������.
	var strToDirContents = "%COMSPEC% /K dir /w " + "\"" + toDir + "\"";
	WScript.Echo(strToDirContents);
	shell.Run(strToDirContents);

	//3.6 ������� ���������� ����� ��������������� ��������; 
	var strToDirFileContents = "%COMSPEC% /K type " + "\"" + fromDir + "\\" + sourcefile + "\"";
	WScript.Echo(strToDirFileContents);
	shell.run(strToDirFileContents);

	//3.7 ��������������� ����������� ���������� �������� � �������������� ����.
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
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <from_folder_path> " + "<source_file_name>.txt" + " <to_folder_path> " + " <result_file_name>.doc");