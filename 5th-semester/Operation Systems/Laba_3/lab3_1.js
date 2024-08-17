//���������� ���������� ����������.
function factorial(number)
{
	if (number <=1)
		return 1;
	else
		return number*factorial(number-1);
}

if (WScript.Arguments.Count()==2)
{
	//����� ���������� � ���������� ������ ������ ��������� ����.
	var n = WScript.Arguments(0);
	WScript.Echo("����� n (������ n ������ ����) =", n);

	//����� ���������� � �������� ���������� x.
	var x = WScript.Arguments(1);
	WScript.Echo("���������� x =", x);

	//���������� ��� ������� ����� ������ n ������ ����.
	var result = 0;

	//���������� ��� �������� n!, (2*n)! � x^n.
	var pow_to_n;
	var pow_to_double_n;
	var pow_to_x = 1;

	//���������� ����� ������ n ������ ��������� ����.
	for (var i=1;i<=n;i++)
	{
		pow_to_n = factorial(i);
		pow_to_double_n = factorial(2*i);
		pow_to_x *= x;
		result += ((pow_to_n*pow_to_n) / pow_to_double_n) * pow_to_x;
	}
	//����� ���������� �����.
	WScript.Echo("���� ����� " + n + " ������ ������ ��������� ���� ����� " + result + ".");
}
else
	WScript.Echo("�������������: cscript //nologo "+ WScript.ScriptFullName + " 3 10");