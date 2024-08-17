if (WScript.Arguments.Count() == 2 || WScript.Arguments.Count() == 3)
{
	//�������� ������� WshShell.
	var shell = WScript.CreateObject("WScript.Shell");

	//�������� ��������� ������ �� ������� ����� � ��������� ����� ����� ������ ��������.
	var strSourceFile = "%WINDIR%\\notepad.exe " + "\"" + WScript.Arguments(0) + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(strSourceFile),1,true);

	//�������� ����� � ������������ ���������� ���������.	
	var fso = WScript.CreateObject("Scripting.FileSystemObject");
	if (WScript.Arguments.Count() == 3)
		var resFile = fso.CreateTextFile(WScript.Arguments(2), true, false);
	
	//��������� ��������� ���������� �����.
	//�������� ������ ��� ����������� ������ ����� (path[,iomode[,create[,unicode]]]) (������������ ���� � ��������� ������� ���������� ������ ��� ������ � ��������� ASCII).
	var textStreamReadFile = fso.OpenTextFile(WScript.Arguments(0), 1, true, 0);

	//����������.
	var word_length = WScript.Arguments(1); //������� ����� �����.
	var word_count = 0;	 		//���������� ���������� ���� �� ������� ������.
	var common_res_str = ""; 		//����������, ������� ������� ��� ��������� �����.
	
	if (WScript.Arguments.Count() == 2)
		WScript.Echo("�������� �����:");
	else
		resFile.WriteLine("�������� �����:");

	if (!textStreamReadFile.AtEndOfStream)
	{
		while (!textStreamReadFile.AtEndOfStream)
		{
			var iter_ind = 0; //���������� ��� ��������� �� ��������� ������.

			//��������� ������ ������� �� ���������� ����� � �������� �������.
			var str_text = textStreamReadFile.ReadLine();
			if (WScript.Arguments.Count() == 2)
				WScript.Echo(str_text);
			else
				resFile.WriteLine(str_text);

			//�������� �� ��������� ������ ��������� ������.
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
						common_res_str += word_count + "-�� �����, ����� �������� ����� \"" + word_length + "\": " + str_text.substr(word_start, word_len) + "\n"; 
			
					}
				}
				iter_ind++;
			}
		}
		if (WScript.Arguments.Count() == 2)
		{
			WScript.Echo("\n" + common_res_str);
			WScript.Echo("���������� ����, ����� ������� ����� \"" + word_length + "\": " + word_count);
		}
		else	
		{
			resFile.WriteLine("\n" + common_res_str);
			resFile.WriteLine("���������� ����, ����� ������� ����� \"" + word_length + "\": " + word_count);
		}
	}
	else
	{
		if (WScript.Arguments.Count() == 2)
			WScript.Echo("undefined\n[��������� ���� � �������� ������� ����! ����������� �� ����������.]");
		else
			resFile.WriteLine("undefined\n[��������� ���� � �������� ������� ����! ����������� �� ����������.]");
	}
	//�������� ��������� ������.
	textStreamReadFile.Close();
}
else
{
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt " + "<enter_a_length_of_word> ");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt " + "<enter_a_length_of_word> " + "<path_res_file>.txt");
}