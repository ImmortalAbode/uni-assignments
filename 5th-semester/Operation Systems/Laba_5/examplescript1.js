//wshExec.js - ������ �������� � �������� ��� ����������
var of;
var shell=WScript.CreateObject("WScript.Shell");

WScript.Echo("������ � ������ ������� � �������, ���� �� ��� �� ��������.");
shell.Run(shell.ExpandEnvironmentStrings("%windir%\\notepad.exe"),1,true);
