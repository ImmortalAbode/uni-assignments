//wshExec.js - запуск процесса и ожидание его завершения
var of;
var shell=WScript.CreateObject("WScript.Shell");

WScript.Echo("Сейчас я запущу блокнот и подожду, пока вы его не закроете.");
shell.Run(shell.ExpandEnvironmentStrings("%windir%\\notepad.exe"),1,true);
