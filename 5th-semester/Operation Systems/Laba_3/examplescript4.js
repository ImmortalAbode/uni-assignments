//Создание объекта для работы с Microsoft Word.
var wdApp = WScript.CreateObject("Word.Application");
//или
//var wdApp = new ActiveXObject("Word.Application);

//Установка свойства Visible созданного объекта в True, чтобы приложение стало видимым.
wdApp.Visible=true;

//Открытие существующего рабочего документа (для Microsoft Word).
wdApp.Documents.Open("D:\\KAI\\Операционные системы\\Laba_3\\example_for_script4.docx");