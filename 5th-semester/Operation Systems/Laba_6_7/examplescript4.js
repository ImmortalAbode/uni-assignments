// fsoCreateText.js - �������� ����� � �������� ���������
if(WScript.Arguments.Count()==1)
{
	var fso=WScript.CreateObject("Scripting.FileSystemObject");
	var tf=fso.CreateTextFile(WScript.Arguments(0),true);
	tf.WriteLine("������� ��������:");
	var i;
	tf.Write(" |");
	for(i=1;i<10;i++)
	{
		tf.Write(" "+i+"|");
	}
	tf.WriteLine("");
	tf.WriteLine("-+--+--+--+--+--+--+--+--+--+");
	var j;
	for(i=1;i<10;i++)
	{
		tf.Write(i);
		for(j=1;j<10;j++)
		{
			tf.Write("|");
			if(i*j<10)
				tf.Write(" ");
			tf.Write(i*j);
		}
		tf.WriteLine("|");
	}
	tf.WriteLine("-+--+--+--+--+--+--+--+--+--+");
	tf.Close();
}
else
	WScript.Echo("�������������: cscript //nologo "+WScript.ScriptFullName + " pifagor.txt");