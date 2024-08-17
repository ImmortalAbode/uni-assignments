//Создание объекта для работы с Microsoft Excel.
//var xlApp=WScript.CreateObject("Excel.Application");
//или
var xlApp=new ActiveXObject("Excel.Application");

//Установка свойства Visible созданного объекта в True, чтобы приложение стало видимым.
xlApp.Visible=true;

//Создание новой рабочей книги в Excel с помощью метода Add.
//expression.Add(Template);
xlApp.Workbooks.Add();
