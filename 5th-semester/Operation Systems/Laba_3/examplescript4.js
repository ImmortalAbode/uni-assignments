//�������� ������� ��� ������ � Microsoft Word.
var wdApp = WScript.CreateObject("Word.Application");
//���
//var wdApp = new ActiveXObject("Word.Application);

//��������� �������� Visible ���������� ������� � True, ����� ���������� ����� �������.
wdApp.Visible=true;

//�������� ������������� �������� ��������� (��� Microsoft Word).
wdApp.Documents.Open("D:\\KAI\\������������ �������\\Laba_3\\example_for_script4.docx");