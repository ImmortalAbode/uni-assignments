//������������� ���������� ������� String ��� ������� ��������� ������.
var str_text = '� ����� ����� ���������� ����������� ���������, ����� �� ������� ����� ��� �������� ��, ��� ��� � ��� ���� ������, ������ ����, ����� ������� �������� ��� ���, ���� � ��� ���.';
WScript.Echo("�������� �����: " + str_text);
//����������.
var word_length = 5; //�������� ����� ������� ����.
var iter_ind = 0; //���������� ��� ��������� �� ��������� ������.
var word_count = 0; //���������� ���������� ���� �� ������� ������.

//�������� �� ��������� ������.
while (iter_ind < str_text.length)
{
	if (str_text.charAt(iter_ind) != ' ' &&
	    str_text.charAt(iter_ind) != '.' &&
	    str_text.charAt(iter_ind) != ',' &&
	    str_text.charAt(iter_ind) != ':' &&
	    str_text.charAt(iter_ind) != ';' &&
	    str_text.charAt(iter_ind) != '-' &&
	    str_text.charAt(iter_ind) != '(' &&
	    str_text.charAt(iter_ind) != ')' &&
	    str_text.charAt(iter_ind) != '!' &&
	    str_text.charAt(iter_ind) != '?' &&
	    str_text.charAt(iter_ind) != '"' &&
	    str_text.charAt(iter_ind) != '\'')
	{
		var word_start = iter_ind; //������ ������� ������� ���������������� ����� ��������� ������.
		var word_len = 0; //����� ���������������� ����� ��������� ������.

		while (str_text.charAt(iter_ind) != ' ' &&
	   	       str_text.charAt(iter_ind) != '.' &&
	    	       str_text.charAt(iter_ind) != ',' &&
	    	       str_text.charAt(iter_ind) != ':' &&
	    	       str_text.charAt(iter_ind) != ';' &&
	    	       str_text.charAt(iter_ind) != '-' &&
	    	       str_text.charAt(iter_ind) != '(' &&
	    	       str_text.charAt(iter_ind) != ')' &&
	    	       str_text.charAt(iter_ind) != '!' &&
	    	       str_text.charAt(iter_ind) != '?' &&
	   	       str_text.charAt(iter_ind) != '"' &&
	    	       str_text.charAt(iter_ind) != '\'')
		{
			word_len++;
			iter_ind++;
		}
		if (str_text.substr(word_start, word_len).length == word_length)
		{
			word_count++;
			WScript.Echo(word_count + "-�� �����, ����� �������� ����� \"" + word_length + "\": " + str_text.substr(word_start, word_len)); 
		}
	}
	iter_ind++;
}
WScript.Echo("���������� ����, ����� ������� ����� \"" + word_length + "\": " + word_count);
