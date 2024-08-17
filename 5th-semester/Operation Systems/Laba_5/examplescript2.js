// Исполнение команды MS-DOS с помощью метода Run.

var command, dos_command, option
var Shell = WScript.CreateObject("WScript.Shell");

// Команда вызова командного процессора
command = "%COMSPEC% /K ";

// Команда получения справки о командах MS-DOS
//для вывода справки о конкретной команде MS DOS необходимо после самой команды Help указать имя интересуемой команды.
dos_command = "help ";

// Использование постраничного вывода
option = "| more"

// Исполнить команду.
Shell.Run(command + dos_command + option);