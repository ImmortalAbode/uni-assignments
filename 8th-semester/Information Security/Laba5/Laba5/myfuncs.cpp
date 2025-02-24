#include <iostream>
#include <string>
#include <iomanip>
#include <functional>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#include "myfuncs.h"
#include "mystruct.h"

/*----------------------------------+
| ФУНКЦИИ ВЫВОДА ОСНОВНЫХ СООБЩЕНИЙ |
+-----------------------------------*/
//Вывод заголовка.
void ShowTitle()
{
	std::cout << std::endl << "|" << std::string(200, '-') << "|" << std::endl;
	std::cout << "|" << std::string(200, ' ') << "|" << std::endl;
	std::cout << "|" << CenterText("Выполнил студент группы 4412 Горшков Андрей Олегович", 200) << "|" << std::endl;
	std::cout << "|" << std::string(200, ' ') << "|" << std::endl;
	std::cout << "|" << std::string(200, '-') << "|" << std::endl << std::endl;
}
//Главное меню.
const int& MainMenu()
{
	std::cout << "Криптоанализ, основанный на исследовании частотности символов в тексте:" << std::endl <<
		"1 -> Провести частотный анализ символов в тексте файла." << std::endl <<
		"2 -> Провести дешифрование заданного файла." << std::endl <<
		"q -> Выход из программы." << std::endl;
	return 2;
}
//Выбор из меню
char GetCase(std::function<const int& ()> showMenu)
{
	int maxChoice{ showMenu() };
	while (true)
	{
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice.size() == 1 && (choice[0] >= '0' && choice[0] <= ('0' + maxChoice) || choice[0] == 'q'))
		{
			std::cout << std::endl;
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода: некорректный выбор. Повторите ввод." << std::endl;
		}
	}
}
/*------------------------------+
| ФУНКЦИИ ВЫВОДА ФОРМАТИРОВАНИЯ |
+-------------------------------*/
//Функция для центрирования текста.
std::string CenterText(const std::string& text, const int& width)
{
	int padding = width - static_cast<int>(text.size()); // Свободное пространство.
	int left_padding = padding / 2;  // Левая часть.
	int right_padding = padding - left_padding; // Правая часть.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//Функция отрисовки разделительной черты.
void DrawLine(const char& del)
{
	std::cout << "|" << std::string(200, del) << "|" << std::endl;
}
/*-----------------------------------+
| ФУНКЦИИ ЧАСТОТНОГО АНАЛИЗА СИМВОЛОВ|
+------------------------------------*/
//Функция-компаратор для сортировки по убыванию количества вхождений.
bool compare(const std::pair<unsigned char, CharStat>& a, const std::pair<unsigned char, CharStat>& b)
{
	if (a.second.count == b.second.count) 
		return a.first < b.first;
	return a.second.count > b.second.count;
}
//Функция для записи результатов в файл.
bool PrintFreqResults(const std::string& file, const std::map<unsigned char, CharStat>& chars_frequency)
{
	//Открытие выходного файла с результатами.
	std::ofstream process_file(file);
	if (!process_file)
	{
		std::cerr << std::endl << "Ошибка: не удалось открыть файл " << file << "! Попробуйте снова." << std::endl;
		return false;
	}

	std::cout << std::endl << "В файл " << file << " выводятся результаты. Пожалуйста, подождите..." << std::endl;

	//Сортировка результатов по убыванию частоты.
	std::vector<std::pair<unsigned char, CharStat>> sorted_chars_frequency(chars_frequency.begin(), chars_frequency.end());
	std::sort(sorted_chars_frequency.begin(), sorted_chars_frequency.end(), compare);

	//Запись заголовков таблицы.
	process_file << "NN\tDEC\tHEX\tCHAR\tCOUNT\t%\n";

	int index{ 1 };
	for (const auto& pair : sorted_chars_frequency)
	{
		unsigned char uch = pair.first;
		//Если символ не печатный, то проверяется вывод на специальные символы.
		std::string charRep = std::isprint(uch) ?
			std::string(1, uch)
			: (uch == 13 ? "\\r"
				: (uch == 10 ? "\\n"
					: std::string(1, uch)));

		//Форматирование 16-ричного вывода (верхний регистр).
		std::stringstream hexStream{};
		hexStream << std::uppercase << std::hex << static_cast<int>(uch);

		process_file << index++ << "\t"
			<< static_cast<int>(uch) << "\t"
			<< hexStream.str() << "\t"
			<< charRep << "\t"
			<< pair.second.count << "\t"
			<< std::fixed << std::setprecision(3) << pair.second.frequency << "%" << "\n";
	}

	process_file.close(); //Закрытие открытого файла.
	std::cout << std::endl << "Результаты записаны в файл " << file << std::endl << std::endl;

	return true;
}
//Подсчет процентного соотношения частотности каждого символа в тексте.
void ComputePercentages(std::map<unsigned char, CharStat>& chars_frequency, const int& total_chars)
{
	for (auto& pair : chars_frequency)
		pair.second.frequency = (pair.second.count * 100.0) / total_chars;
	return;
}
//Проведение частотного анализа символов в файле.
bool ExecuteFileAnalysis(const std::string& file, std::map<unsigned char, CharStat>& chars_frequency, int& total_chars)
{
	//Открытие файла в бинарном режиме.
	std::ifstream process_file(file, std::ios::binary);

	if (!process_file)
	{
		std::cerr << std::endl << "Ошибка: не удалось открыть файл " << file << "! Попробуйте снова." << std::endl;
		return false;
	}

	std::cout << std::endl << "Файл " << file << " анализируется. Пожалуйста, подождите..." << std::endl;

	//Подсчет частоты символов.
	char ch{};
	while (process_file.get(ch))
	{
		unsigned char uch = static_cast<unsigned char>(ch);
		chars_frequency[uch].symbol = uch;
		chars_frequency[uch].count++;
		total_chars++;
	}

	if (total_chars == 0)
	{
		std::cout << "Файл пуст! Анализировать нечего. Укажите другой файл." << std::endl;
		return false;
	}

	process_file.close(); //Закрытие открытого файла.
	std::cout << std::endl << "Файл  " << file << " был успешно проанализирован!" << std::endl << std::endl;
	DrawLine('-');

	return true;
}
//Обработка взаимодействия пользователя при анализе частотности символов.
void ExecuteSymbolFrequency()
{
	//Обработка.
	std::cout << std::endl;
	while (true)
	{
		//Принимаем файл от пользователя.
		std::cout << "Введите название файла для проведения частотного анализа символов." << std::endl;
		std::cout << "Укажите файл в формате <name.txt> (Enter -> по умолчанию: opentext.txt; quit - выход)." << std::endl;
		std::cout << "Ваш файл: ";
		std::string input_file{};
		std::getline(std::cin, input_file);
		if (input_file == "quit")
		{
			std::cout << std::endl;
			break;
		}
		if (input_file.empty()) input_file = "opentext.txt";
		
		//Формирование вектора структур для анализа символов.
		std::map<unsigned char, CharStat> chars_frequency{};
		int total_chars{};

		//1. Исследование частотности символов текста в файле.
		if (!ExecuteFileAnalysis(input_file, chars_frequency, total_chars)) break;
		//2. Подсчет частотности каждого символа в процентах.
		ComputePercentages(chars_frequency, total_chars);
		//3. Вывод результатов.
		std::string output_file{};
		std::cout << std::endl;
		std::cout << "Введите название файла для вывода результатов проведенного анализа." << std::endl;
		std::cout << "Укажите файл в формате <name.txt> (Enter -> по умолчанию: FA_Opentext.txt; quit - выход)." << std::endl;
		std::cout << "Ваш файл: ";
		std::getline(std::cin, output_file);
		if (output_file == "quit") 
		{
			std::cout << std::endl;
			break;
		}
		if (output_file.empty()) output_file = "FA_Opentext.txt";
		if (!PrintFreqResults(output_file, chars_frequency)) break;

		DrawLine('-');
		std::cout << std::endl;

		//Конец.
		std::cout << "Проведенный частотный анализ файла " << input_file << " был выведен в файл " << output_file << "!" << std::endl << std::endl;

		DrawLine('-');
		std::cout << std::endl;
	}
	return;
}
/*--------------------------------------------+
| ФУНКЦИИ ДЕШИФРОВАНИЯ ФАЙЛА НА ОСНОВЕ АНАЛИЗА|
+---------------------------------------------*/
//Функция для сохранения таблицы подстановок в указанный файл.
bool SaveSubstitutionTable(const std::vector<std::pair<unsigned char, unsigned char>>& substitution, const std::string& file)
{
	//Открытие файла для сохранения.
	std::ofstream table_file(file);
	if (!table_file)
	{
		std::cerr << std::endl << "Ошибка: не удалось открыть файл для таблицы замен!" << std::endl;
		return false;
	}

	table_file << "ТАБЛИЦА ЗАМЕН АЛГОРИТМА ШИФРОВАНИЯ" << std::endl;
	//Запись заголовков таблицы.
	table_file << "NN\tENCR_S\t\tDECR_S\n";

	int index{ 1 };
	for (const auto& pair : substitution) 
	{
		unsigned char encr_s = pair.first;
		unsigned char decr_s = pair.second;

		std::string encr_s_Rep = std::isprint(encr_s) ? 
			std::string(1, encr_s)
			: (encr_s == 13 ? "\\r"
				: (encr_s == 10 ? "\\n"
					: std::string(1, encr_s)));

		std::string decr_s_Rep = std::isprint(decr_s) ? 
			std::string(1, decr_s)
			: (decr_s == 13 ? "\\r"
				: (decr_s == 10 ? "\\n"
					: std::string(1, decr_s)));

		table_file << index++ << "\t"
			<< encr_s_Rep << "\t"
			<< "->" << "\t"
			<< decr_s_Rep << "\n";
	}

	table_file.close();
	std::cout << std::endl << "Таблица замен сохранена в " << file << "!" << std::endl << std::endl;

	return true;
}
//Функция проведения дешифроки текста в файле.
bool ExecuteFileDecrypt(const std::string& freq1_file, const std::string& freq2_file, const std::string& encrypt_file, const std::string& decrypt_file, const std::string& table_file)
{
	//Карты для хранения частот незашифрованных и зашифрованных символов.
	std::map<unsigned char, CharStat> chars_freq1{}, chars_freq2{};
	int total_chars1{}, total_chars2{};

	//Анализируем оба файла с частотами.
	//Файл с открытым текстом.
	if (!ExecuteFileAnalysis(freq1_file, chars_freq1, total_chars1)) return false;
	//Файл с зашифрованным текстом.
	if (!ExecuteFileAnalysis(freq2_file, chars_freq2, total_chars2)) return false;
	ComputePercentages(chars_freq1, total_chars1);
	ComputePercentages(chars_freq2, total_chars2);

	//Сортируем частоты.
	std::vector<std::pair<unsigned char, CharStat>> sorted_chars_freq1(chars_freq1.begin(), chars_freq1.end());
	std::vector<std::pair<unsigned char, CharStat>> sorted_chars_freq2(chars_freq2.begin(), chars_freq2.end());
	std::sort(sorted_chars_freq1.begin(), sorted_chars_freq1.end(), compare);
	std::sort(sorted_chars_freq2.begin(), sorted_chars_freq2.end(), compare);

	//Создаем таблицу подстановки.
	std::vector<std::pair<unsigned char, unsigned char>> substitution{};			// Ключ - зашифрованный символ, значение - расшифрованный символ.
	for (size_t i = 0; i < std::min(sorted_chars_freq1.size(), sorted_chars_freq2.size()); ++i)
		substitution.emplace_back(sorted_chars_freq2[i].first, sorted_chars_freq1[i].first);	//Зашифрованный символ -> символ открытого текста.

	//Вывод таблицы в файл.
	if (!SaveSubstitutionTable(substitution, table_file)) return false;

	//Открываем зашифрованный файл и файл для расшифрованного текста.
	std::ifstream input_file(encrypt_file, std::ios::binary);//Зашифрованный файл.
	std::ofstream output_file(decrypt_file, std::ios::binary);//Файл расшифровки.
	if (!input_file || !output_file)
	{
		std::cerr << std::endl << "Ошибка: не удалось открыть входной или выходной файл!" << std::endl;
		return false;
	}

	//Заменяем символы по таблице подстановки.
	//Заменяем символы по таблице подстановки.
	char ch{};
	while (input_file.get(ch)) 
	{
		unsigned char uch = static_cast<unsigned char>(ch);
		bool replaced{};
		//Ищем зашифрованный символ.
		for (const auto& pair : substitution) 
		{
			// Если символ найден в таблице,
			if (pair.first == uch) 
			{  
				output_file.put(pair.second); //То заменяем.
				replaced = true;
				break;
			}
		}
		// Если символ не был заменен, оставляем его как есть.
		if (!replaced) 
		{ 
			output_file.put(ch);
		}
	}

	//Закрытие файлов.
	input_file.close();
	output_file.close();
	std::cout << std::endl << "Расшифровка завершена! Результат записан в " << decrypt_file << "!" << std::endl;

	return true;
}
//Обработка взаимодействия пользователя при дешифровании файла на основе анализа частотности символов.
void ExecuteDecryptFile()
{
	//Обработка.
	std::cout << std::endl;
	while (true) 
	{
		//Ввод файла с открытым текстом для анализа.
		std::string freq1_file{};
		std::cout << "Введите название файла с открытым текстом, на основе которого будет получен анализ частотности символов." << std::endl;
		std::cout << "Укажите файл в формате <name.txt> (Enter -> по умолчанию: opentext.txt; quit - выход)." << std::endl;
		std::cout << "Ваш файл: ";
		std::getline(std::cin, freq1_file);
		if (freq1_file == "quit")
		{
			std::cout << std::endl;
			break;
		}
		if (freq1_file.empty()) freq1_file = "opentext.txt";

		std::cout << std::endl;
		DrawLine('-');
		std::cout << std::endl;

		//Ввод файла с зашифрованным текстом для анализа.
		std::string freq2_file{};
		std::cout << "Введите название файла с зашифрованным текстом, на основе которого будет получен анализ частотности символов." << std::endl;
		std::cout << "Укажите файл в формате <name.txt> (Enter -> по умолчанию: open.txt; quit - выход)." << std::endl;
		std::cout << "Ваш файл: ";
		std::getline(std::cin, freq2_file);
		if (freq2_file == "quit")
		{
			std::cout << std::endl;
			break;
		}
		if (freq2_file.empty()) freq2_file = "open.txt";

		std::cout << std::endl;
		DrawLine('-');
		std::cout << std::endl;

		//Ввод файла с зашифрованным текстом для расшифровки.
		std::string encrypt_file{};
		std::cout << "Введите название файла с зашифрованным текстом для расшифровки." << std::endl;
		std::cout << "Укажите файл в формате <name.txt> (Enter -> по умолчанию: " << freq2_file << "; quit - выход)." << std::endl;
		std::cout << "Ваш файл: ";
		std::getline(std::cin, encrypt_file);
		if (encrypt_file == "quit")
		{
			std::cout << std::endl;
			break;
		}
		if (encrypt_file.empty()) encrypt_file = freq2_file;

		std::cout << std::endl;
		DrawLine('-');
		std::cout << std::endl;

		//Вывод результатов (расшифровка).
		std::string decrypt_file{};
		std::cout << "Введите название файла, в который будет помещен результат расшифровки." << std::endl;
		std::cout << "Укажите файл в формате <name.txt> (Enter -> по умолчанию: decrypt_open.txt; quit - выход)." << std::endl;
		std::cout << "Ваш файл: ";
		std::getline(std::cin, decrypt_file);
		if (decrypt_file == "quit")
		{
			std::cout << std::endl;
			break;
		}
		if (decrypt_file.empty()) decrypt_file = "decrypt_open.txt";

		std::cout << std::endl;
		DrawLine('-');
		std::cout << std::endl;

		//Вывод таблицы подстановок в указанный файл.
		std::string table_file{};
		std::cout << "Введите название файла, в который будет выведена таблица подстановок символов." << std::endl;
		std::cout << "Укажите файл в формате <name.txt> (Enter -> по умолчанию: table_encr_decr_opentext_open.txt; quit - выход)." << std::endl;
		std::cout << "Ваш файл: ";
		std::getline(std::cin, table_file);
		if (table_file == "quit")
		{
			std::cout << std::endl;
			break;
		}
		if (table_file.empty()) table_file = "table_encr_decr_opentext_open.txt";

		std::cout << std::endl;
		DrawLine('-');

		//Запуск.
		if (!ExecuteFileDecrypt(freq1_file, freq2_file, encrypt_file, decrypt_file, table_file)) break;
		else std::cout << std::endl;

		//Конец.
		std::cout << "Был успешно произведен криптоанализ файла " << encrypt_file << ", результаты записаны в файл " << decrypt_file << "! "
			<< std::endl << "Расшифровка производилась на основе частотного анализа символов следующих файлов: " << freq1_file << " -> "
			<< freq2_file << "." << std::endl
			<< "Таблица подстановок выведена в файл " << table_file << "." << std::endl
			<< "Примечание:\n\t*Для просмотра частотного анализа соответствующих файлов можно запустить опцию 1 данной программы." << std::endl << std::endl;


		DrawLine('-');
		std::cout << std::endl;
	}
	return;
}