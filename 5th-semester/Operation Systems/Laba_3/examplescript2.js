//Создание объекта для работы с Microsoft Word.

//var wdApp = WScript.CreateObject("Word.Application");
//или
var wdApp = new ActiveXObject("Word.Application");

//Установка свойства Visible созданного объекта в True, чтобы положение стало видимым.
wdApp.Visible=true;

//Добавление нового, пустого документа к коллекции открытых документов с помощью метода Add.
//expression.Add(Template, NewTemplate, DocumentType, Visible);
wdApp.Documents.Add();
