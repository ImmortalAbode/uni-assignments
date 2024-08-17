if (WScript.Arguments.Count()==2)
{
	//Инициализация экземпляра объекта String для задания исходного текста.
	var str_text = WScript.Arguments(0);
	WScript.Echo("Исходный текст: " + str_text);
	//Переменные.
	var word_length = WScript.Arguments(1); //Заданная длина искомых слов.
	var iter_ind = 0; //Переменная для интерации по исходному тексту.
	var word_count = 0; //Количество отобранных слов по условию задачи.

	//Итерация по исходному тексту.
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
				WScript.Echo(word_count + "-ое слово, длина которого равна \"" + word_length + "\": " + str_text.substr(word_start, word_len)); 
			}
		}
		iter_ind++;
	}
	WScript.Echo("Количество слов, длина которых равна \"" + word_length + "\": " + word_count);
}
else
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " \"В вашей жизни происходят невероятные изменения, когда вы решаете взять под контроль то, над чем у вас есть власть, вместо того, чтобы жаждать контроля над тем, чего у вас нет.\" 5");
