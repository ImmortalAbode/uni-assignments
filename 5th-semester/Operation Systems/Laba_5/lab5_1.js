//����� ���������� � �������� ������� MS-DOS �� ���������� ���� � ��������� ����.
if (WScript.Arguments.count() == 3)
{
	//������������� ����������� ����������� ������� String ��� ������������ ������������ ������ MS-DOS.
	var command = WScript.Arguments(0);
	var path = WScript.Arguments(1);
	var filename = WScript.Arguments(2);
	
	//������������� ������������ ���������� ������� WshShell � ������������ ������ �������.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /C help " + command + ">\"" + path + filename + ".\"";

	//���������� ������� MS-DOS � ������� ������ Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//����� ���������� � �������� MS-DOS �� ���������� ���� � �������� ����.
else if (WScript.Arguments.count() == 2)
{
	//������������� ����������� ����������� ������� String ��� ������������ ������������ ������ MS-DOS.
	var command = WScript.Arguments(0);
	var path = WScript.Arguments(1);

	var filename = 'defaultname.doc';
	
	//������������� ������������ ���������� ������� WshShell � ������������ ������ �������.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /C help " + command + ">\"" + path + filename + ".\"";

	//���������� ������� MS-DOS � ������� ������ Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//����� ���������� � �������� MS-DOS �� ������� � ��������� ����.
else if (WScript.Arguments.count() == 1)
{
	//������������� ����������� ����������� ������� String ��� ������������ ������������ ������ MS-DOS.
	var command = WScript.Arguments(0);
	
	//������������� ������������ ���������� ������� WshShell � ������������ ������ �������.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help " + command;	
	
	//���������� ������� MS-DOS � ������� ������ Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
else if (WScript.Arguments.count() == 0)
{
	//������������� ������������ ���������� ������� WshShell � ������������ ������ �������.
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help ";
	
	//���������� ������� MS-DOS � ������� ������ Run.
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//����� ����� � ���������� �������� ������ ���������.
else
{
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <command_name> " + "<file_path>" + " <file_name>.doc");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <command_name> " + "<file_path>");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <command_name> ");
	WScript.ECho("�������������: cscript //nologo " + WScript.ScriptFullName);
} 