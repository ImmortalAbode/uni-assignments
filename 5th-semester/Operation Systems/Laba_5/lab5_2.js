//������ �� ���������� ���� �������� ��������� � ��������� ������ �������.
if (WScript.Arguments.Count() == 3)
{
	var path = WScript.Arguments(0);
	var filename = WScript.Arguments(1);
	var mode = WScript.Arguments(2);
	
	//�������� ��������������� ��������� � ��������.
	var shell = WScript.CreateObject("WScript.Shell");
	shell.Run(("%WINDIR%\\notepad.exe " + path + filename),1,true);
	
	//���������� ��������� � ����������� �� ���������� ������ ������� ���������.
	if (mode == "cmd") //�������.
	{
		WScript.Echo("%COMSPEC% /K cscript " + "\"" + path + filename + "\"");
		shell.Run("%COMSPEC% /K cscript " + "\"" + path + filename + "\"");
	}
	else if (mode == "window")//����.
	{
		WScript.Echo("%COMSPEC% /K wscript " + "\"" + path + filename + "\"");
		//"& exit" ��������� ����������� ���� ������� ��� ������� �������� ��������� � ������� ������.
		shell.run("%COMSPEC% /K wscript " + "\"" + path + filename + "\"" + "& exit");	
	}
	else
		WScript.Echo("������ ������ ������� ��������� (cmd/window).");
	
}
else
{
	WScript.Echo("������� �������� ���������� ���������� ��������� ������.");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <path> " + "<filename>.js" + " <mode>.");
}