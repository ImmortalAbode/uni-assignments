//Создание объекта для работы с Microsoft Excel. 
//var xlApp = new ActiveXObject("Excel.Application);
//или
var xlApp = WScript.CreateObject("Excel.Application");

//Установка свойства Visible созданного объекта в True, чтобы приложение стало видимым. 
xlApp.Visible=true;

//Открытие существующей рабочей книги (для Microsoft Excel). 
xlApp.Workbooks.Open("D:\\KAI\\Операционные системы\\Laba_3\\example_for_script5.xlsx");