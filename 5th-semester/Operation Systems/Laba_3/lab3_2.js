if (WScript.Arguments.Count()==3)
{
	//����� ���������� � ���������� ������ n ������ ��������� ����.
	var n = WScript.Arguments(0);
	WScript.Echo("����� n (������ n ������ ����) =", n);
	
	//����� ���������� � �������� ���������� x.
	var x = WScript.Arguments(1);
	WScript.Echo("���������� x =", x);
	
	//����� ���������� � �������� ���������� p.
	var p = WScript.Arguments(2);
	WScript.Echo("���������� p =", p);
	
	//���������� ��� �������� ����� ������ n ������ ��������� ����.
	var summ = 0;
	
	//���������� ����� ������ n ������ ��������� ����.
	for (i=1;i<=n;i++)
	{
		summ += (1/Math.pow(i,p))*Math.pow(1-(x*Math.log(i))/i,i);
	}
	//����� ���������� �����.
	WScript.Echo("���� ����� " + n + " ������ ������ ���� ����� " + summ + ".");
}
else
	WScript.Echo("�������������: cscript //nologo "+ WScript.ScriptFullName + " 2 1 3");
