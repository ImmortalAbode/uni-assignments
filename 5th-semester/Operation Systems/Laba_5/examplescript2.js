// ���������� ������� MS-DOS � ������� ������ Run.

var command, dos_command, option
var Shell = WScript.CreateObject("WScript.Shell");

// ������� ������ ���������� ����������
command = "%COMSPEC% /K ";

// ������� ��������� ������� � �������� MS-DOS
//��� ������ ������� � ���������� ������� MS DOS ���������� ����� ����� ������� Help ������� ��� ������������ �������.
dos_command = "help ";

// ������������� ������������� ������
option = "| more"

// ��������� �������.
Shell.Run(command + dos_command + option);