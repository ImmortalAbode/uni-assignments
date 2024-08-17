if (WScript.Arguments.Count() == 2 || WScript.Arguments.Count() == 3)
{
	//Создание объекта WshShell.
	var shell = WScript.CreateObject("WScript.Shell");

	//Создание исходного текста на русском языке в текстовом файле путем вызова блокнота.
	var strSourceFile = "%WINDIR%\\notepad.exe " + "\"" + WScript.Arguments(0) + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(strSourceFile),1,true);

	//Создание файла с результатами выполнения процедуры.	
	var fso = WScript.CreateObject("Scripting.FileSystemObject");
	if (WScript.Arguments.Count() == 3)
		var resFile = fso.CreateTextFile(WScript.Arguments(2), true, false);
	
	//Обработка исходного текстового файла.
	//Открытие потока для построчного чтения файла (path[,iomode[,create[,unicode]]]) (существующий файл с исходными данными открываетя только для чтения в кодировке ASCII).
	var textStreamReadFile = fso.OpenTextFile(WScript.Arguments(0), 1, true, 0);

	//Переменные.
	var word_length = WScript.Arguments(1); //Искомая длина слова.
	var word_count = 0;	 		//Количество отобранных слов по условию задачи.
	var common_res_str = ""; 		//Переменная, которая выведет все найденные слова.
	
	if (WScript.Arguments.Count() == 2)
		WScript.Echo("Исходный текст:");
	else
		resFile.WriteLine("Исходный текст:");

	if (!textStreamReadFile.AtEndOfStream)
	{
		while (!textStreamReadFile.AtEndOfStream)
		{
			var iter_ind = 0; //Переменная для интерации по считанной строке.

			//Считываем первую строчку из текстового файла с исходным текстом.
			var str_text = textStreamReadFile.ReadLine();
			if (WScript.Arguments.Count() == 2)
				WScript.Echo(str_text);
			else
				resFile.WriteLine(str_text);

			//Итерация по считанной строке исходного текста.
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
					var word_start = iter_ind; //Индекс первого символа рассматриваемого слова исходного текста.
					var word_len = 0; //Длина рассматриваемого слова исходного текста.

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
						common_res_str += word_count + "-ое слово, длина которого равна \"" + word_length + "\": " + str_text.substr(word_start, word_len) + "\n"; 
			
					}
				}
				iter_ind++;
			}
		}
		if (WScript.Arguments.Count() == 2)
		{
			WScript.Echo("\n" + common_res_str);
			WScript.Echo("Количество слов, длина которых равна \"" + word_length + "\": " + word_count);
		}
		else	
		{
			resFile.WriteLine("\n" + common_res_str);
			resFile.WriteLine("Количество слов, длина которых равна \"" + word_length + "\": " + word_count);
		}
	}
	else
	{
		if (WScript.Arguments.Count() == 2)
			WScript.Echo("undefined\n[Текстовый файл с исходным текстом пуст! Содержимого не обнаружено.]");
		else
			resFile.WriteLine("undefined\n[Текстовый файл с исходным текстом пуст! Содержимого не обнаружено.]");
	}
	//Закрытие открытого потока.
	textStreamReadFile.Close();
}
else
{
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt " + "<enter_a_length_of_word> ");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt " + "<enter_a_length_of_word> " + "<path_res_file>.txt");
}