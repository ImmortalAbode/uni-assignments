//�������� ������� ��� ������ � Microsoft Excel. 
//var xlApp = new ActiveXObject("Excel.Application);
//���
var xlApp = WScript.CreateObject("Excel.Application");

//��������� �������� Visible ���������� ������� � True, ����� ���������� ����� �������. 
xlApp.Visible=true;

//�������� ������������ ������� ����� (��� Microsoft Excel). 
xlApp.Workbooks.Open("D:\\KAI\\������������ �������\\Laba_3\\example_for_script5.xlsx");