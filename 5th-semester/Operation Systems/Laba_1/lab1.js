//����� ���������� � ���������� ������ ������ ��������� ����.
var n = 3;
WScript.Echo("����� n (������ n ������ ����) =", n);

//����� ���������� � �������� ���������� x.
var x = 10;
WScript.Echo("���������� x =", x);

//���������� ��� ������� ����� ������ n ������ ����.
var result = 0;

//���������� ��� �������� n!, (2*n)! � x^n.
var pow_to_n = 1;
var pow_to_double_n;
var pow_to_x = 1;

//���������� ����� ������ n ������ ��������� ����.
for (var i=1;i<=n;i++)
{
	pow_to_n *= i;
	pow_to_double_n = pow_to_n;
	for (var j=i+1;j<=2*i;j++)
	{
		pow_to_double_n*=j;
	}
	pow_to_x *= x;
	result += ((pow_to_n*pow_to_n) / pow_to_double_n) * pow_to_x;
}
//����� ���������� �����.
WScript.Echo("���� ����� " + n + " ������ ������ ��������� ���� ����� " + result + ".");
