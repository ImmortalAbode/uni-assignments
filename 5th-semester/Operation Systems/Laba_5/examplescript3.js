//wshShk.js - создание ярлыка Блокнота на Рабочем столе

var WSHShell=WScript.CreateObject("WScript.Shell");

//путь к Рабочему столу
var DesktopPath = WSHShell.SpecialFolders("Desktop");

//cоздаем ярлык на Рабочем столе
var MyShortcut=WSHShell.CreateShortcut(DesktopPath+"\\Ярлык на блокнот.lnk");

//Задаем свойства объекта-ярлыка и сохраняем их.
MyShortcut.TargetPath=WSHShell.ExpandEnvironmentStrings("%windir%\\notepad.exe");
MyShortcut.WorkingDirectory=WSHShell.ExpandEnvironmentStrings("%windir%");
MyShortcut.WindowStyle=4;
MyShortcut.IconLocation=WSHShell.ExpandEnvironmentStrings("%windir%\\notepad.exe,0");
MyShortcut.Save();

WScript.Echo("Теперь на Рабочем столе есть ярлык для Notepad.");