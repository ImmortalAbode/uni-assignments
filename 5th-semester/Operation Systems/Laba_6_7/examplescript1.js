// fsoDirs.js - ��������� ��������� ���������
var fso=WScript.CreateObject("Scripting.FileSystemObject");
var s="����������� ��������:";
s+="\nWindows "+fso.GetSpecialFolder(0);
s+="\nSystem "+fso.GetSpecialFolder(1);
s+="\nTemp "+fso.GetSpecialFolder(2);
WScript.Echo(s);