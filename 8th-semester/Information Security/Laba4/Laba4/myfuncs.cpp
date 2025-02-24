#include <iostream>
#include <string>
#include <iomanip>
#include <functional>
#include <vector>

#include "myfuncs.h"
#include "constants.h"

/*-----------------+
| ФУНКЦИИ ПРОВЕРОК |
+------------------*/
//Проверка строки на русский ("RUS") или латинский ("LATIN") алфавит, смешанный = "MIXED", без букв = "NONE".
const std::string CheckMixedAlphabet(const std::string& text)
{
	bool hasLatin{};
	bool hasRussian{};

	for (const char& c : text) 
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) 
		{
			hasLatin = true;
		}
		else if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')) 
		{
			hasRussian = true;
		}
		if (hasLatin && hasRussian) 
		{
			return "MIXED";
		}
	}

	if (hasLatin) 
	{
		return "LATIN";
	}
	else if (hasRussian) 
	{
		return "RUS";
	}

	return "NONE";
}
//Нижний -> верхний регистр русских и латинских символов.
char LowerToUpper(const char& c, const std::string& type_alphabet)
{
	if (type_alphabet == "RUS") 
	{
		if (c >= 'а' && c <= 'я')
			return c - ('а' - 'А');
	}
	else if (type_alphabet == "LATIN") 
	{
		if (c >= 'a' && c <= 'z') {
			return c - ('a' - 'A');
		}
		return c;
	}
	return c;
}
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
	std::cout << "Шифрование методом G-контурной многоалфавитной замены." << std::endl <<
		"1 - Запустить программу." << std::endl <<
		"2 - Выход из программы." << std::endl;
	return 2;
}
//Выбор из меню
char GetCase(std::function<const int&()> showMenu)
{
	int maxChoice{ showMenu() };
	while (true)
	{
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice.size() == 1 && (choice[0] >= '0' && choice[0] <= ('0' + maxChoice)))
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода: некорректный выбор. Повторите ввод." << std::endl;
		}
	}
}
/*----------------------------------+
| ФУНКЦИИ ВЫВОДА ТАБЛИЦ ПОДСТАНОВОК |
+-----------------------------------*/
//Функция для отрисовки горизонтальной линии таблицы.
void HorizontalLineForTable(const int& col_width) 
{
	std::cout << std::string(col_width + 2, '-') << std::endl;
}
void HorizontalDoubleLineForTable(const int& col_width)
{
	std::cout << std::string(col_width + 2, '=') << std::endl;
}
//Функция для центрирования текста.
std::string CenterText(const std::string& text, const int& width)
{
	int padding = width - static_cast<int>(text.size()); // Свободное пространство.
	int left_padding = padding / 2;  // Левая часть.
	int right_padding = padding - left_padding; // Правая часть.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//Функция отрисовки разделительной черты.
void DrawLine()
{
	std::cout << "|" << std::string(200, '-') << "|" << std::endl;
}
//Отображение таблицы шифра G-контурной многоалфавитной замены.
void DisplayContourPolyTable(const std::string& type_alphabet, const std::string& text, const std::vector<std::string>& keys)
{
	//Определение алфавита.
	std::string alphabet{};
	if (type_alphabet == "RUS") alphabet = russian_upper;
	else if (type_alphabet == "LATIN") alphabet = latin_upper;
	else return;

	//Приведение исходного текста к тексту без лишних знаков и в верхнем регистре.
	std::string up_text{};
	for (size_t i = 0; i < text.size(); ++i)
	{
		if (type_alphabet == "RUS")
		{
			if (!(text[i] >= 'а' && text[i] <= 'я' || text[i] >= 'А' && text[i] <= 'Я'))
				continue;
		}
		else
		{
			if (!(text[i] >= 'a' && text[i] <= 'z' || text[i] >= 'A' && text[i] <= 'Z'))
				continue;
		}
		up_text += LowerToUpper(text[i], type_alphabet);
	}
	
	const int col_width{ 3 };	//Ширина столбца.
	const int word_width{ 12 };	//Отведение места для слов названия строк.
	const int columns{ 20 };	//Число столбцов.
	const int row_length{ static_cast<const int>(col_width * columns + word_width + (columns - 1) + 1) }; //Длина строки.
	const int steps{ static_cast<int>(up_text.size()) / columns + ((static_cast<int>(up_text.size()) % columns) == 0 ? 0 : 1) }; //Число секций таблицы.

	for (size_t i = 0; i < keys.size(); ++i)
	{
		//Приведение ключа к верхнему регистру.
		std::string key{}; //Текущий ключ.
		for (const char& c : keys[i])
			key += LowerToUpper(c, type_alphabet);
		//Определение текущего зашифрованного текста.
		std::string encrypt_text{ ProcessWithKey(up_text, key, type_alphabet, true) };	//Текущий зашифрованный текст.

		//Заголовок.
		std::cout << std::endl;
		std::cout << "Этап №" << i + 1 << std::endl;
		HorizontalDoubleLineForTable(row_length);
		std::cout << "|" << CenterText("Таблица подстановок G - контурной многоалфавитной замены", row_length) << "|" << std::endl;
		HorizontalDoubleLineForTable(row_length);

		//Вывод таблицы подстановок.
		//Секции таблицы по 3 строки.
		for (size_t iter = 0; iter < steps; ++iter)
		{
			//Строки внутри секции.
			for (size_t row = 0; row < 3; ++row)
			{
				switch (row)
				{
				case 0:
					std::cout << "|" << std::setw(static_cast<size_t>(word_width)) << CenterText("Сообщение", word_width) << "|";
					//Колонки внутри строк секции.
					for (size_t col = 0; col < columns; ++col)
					{
						if (iter * columns + col < up_text.size())
							std::cout << std::right << std::setw(col_width) << up_text[iter * columns + col] << "|";
						else
							std::cout << std::right << std::setw(col_width) << " " << "|";
					}
					break;
				case 1:
					std::cout << "|" << std::setw(static_cast<size_t>(word_width)) << CenterText("Ключ", word_width) << "|";
					//Колонки.
					for (size_t col = 0; col < columns; ++col)
					{
						//Вывод.
						if ((iter * columns + col < up_text.size()))
							std::cout << std::right << std::setw(col_width) << key[(iter * columns + col) % key.size()] << "|";
						else
							std::cout << std::right << std::setw(col_width) << " " << "|";
					}
					break;
				case 2:
					std::cout << "|" << std::setw(static_cast<size_t>(word_width)) << CenterText("Шифротекст", word_width) << "|";
					for (size_t col = 0; col < columns; ++col)
					{
						if (iter * columns + col < encrypt_text.size())
							std::cout << std::right << std::setw(col_width) << encrypt_text[iter * columns + col] << "|";
						else
							std::cout << std::right << std::setw(col_width) << " " << "|";
					}
					break;
				default:;
				}
				std::cout << std::endl;
				if (row != 2) HorizontalLineForTable(row_length);
			}
			HorizontalDoubleLineForTable(row_length);
		}
		up_text = encrypt_text;
	}
	std::cout << std::endl;
}
/*----------------------------------------+
| ФУНКЦИИ РЕАЛИЗАЦИИ АЛГОРИТМА ШИФРОВАНИЯ |
+-----------------------------------------*/
//Проверка ключа на корректность.
bool CheckKeyCorrect(const std::string& type_alphabet, const std::string& key)
{
	if (type_alphabet == "RUS")
	{
		for (size_t i = 0; i < key.size(); ++i)
		{
			if (key[i] >= 'А' && key[i] <= 'Я' || key[i] >= 'а' && key[i] <= 'я' || key[i] >= '0' && key[i] <= '9')
				continue;
			else
				return false;
		}
	}
	else
	{
		for (size_t i = 0; i < key.size(); ++i)
		{
			if (key[i] >= 'A' && key[i] <= 'Z' || key[i] >= 'a' && key[i] <= 'z' || key[i] >= '0' && key[i] <= '9')
				continue;
			else
				return false;
		}
	}
	return true;
}
//Получение смещения по символу ключа.
int GetShift(const char& c_key, const std::string& type_alphabet)
{
	if (c_key >= '0' && c_key <= '9')
		return c_key - '0';

	const std::string& upper = (type_alphabet == "RUS") ? russian_upper : latin_upper;
	const std::string& lower = (type_alphabet == "RUS") ? russian_lower : latin_lower;

	size_t pos = upper.find(c_key);
	if (pos != std::string::npos) return static_cast<int>(pos);
	pos = lower.find(c_key);
	return (pos != std::string::npos) ? static_cast<int>(pos) : 0;
}
//Шифрование соответствующего символа по ключу.
char EncryptChar(const char& c, const int& shift, const std::string& alphabet, const int& M)
{
	size_t pos = alphabet.find(c);
	return (pos != std::string::npos) ? alphabet[(pos + shift + M) % M] : c;
}
//Шифрование текста по одному ключу.
std::string ProcessWithKey(const std::string& text, const std::string& key, const std::string& type_alphabet, const bool& encrypt)
{
	std::string result{};
	const int M = (type_alphabet == "RUS") ? RUSSIAN_M : LATIN_M;
	const std::string& upper = (type_alphabet == "RUS") ? russian_upper : latin_upper;
	const std::string& lower = (type_alphabet == "RUS") ? russian_lower : latin_lower;
	size_t num_char{};

	for (char c : text)
	{
		int shift = GetShift(key[num_char % key.size()], type_alphabet);
		if (!encrypt) shift = (-shift % M + M) % M; //Нормализация при дешифровании.

		if (upper.find(c) != std::string::npos || lower.find(c) != std::string::npos)
		{
			result += EncryptChar(c, shift, (upper.find(c) != std::string::npos) ? upper : lower, M);
			num_char++;
		}
		else
		{
			result += c;
		}
	}
	return result;
}
//Шифрование текста по всем ключам.
std::string ProcessText(const std::string& text, const std::vector<std::string>& keys, const std::string& type_alphabet, bool encrypt)
{
	std::string cur_text{ text };
	for (size_t i = 0; i < keys.size(); ++i)
	{
		const std::string& key{ encrypt ? keys[i] : keys[keys.size() - 1 - i] };
		cur_text = ProcessWithKey(cur_text, key, type_alphabet, encrypt);
	}
	return cur_text;
}
//Шифрование методом G-контурной многоалфавитной замены.
std::string ContourPolyEncryption(const std::string& text, const std::vector<std::string>& keys, const std::string& type_alphabet)
{
	return ProcessText(text, keys, type_alphabet, true);
}
//Дешифрование методом G-контурной многоалфавитной замены.
std::string ContourPolyDecryption(const std::string& text, const std::vector<std::string>& keys, const std::string& type_alphabet)
{
	return ProcessText(text, keys, type_alphabet, false);
}
//Метод G-контурной многоалфавитной замены - обработка.
void EcexuteContourPolySub()
{
	//Обработка.
	std::cout << std::endl;
	std::cout << "Шифрование методом G-контурной многоалфавитной замены. " << std::endl;
	std::cout << "Примечание:\n\t*Шифрование русских символов -> русский алфавит, латинских символов -> латинский алфавит." << std::endl;
	std::cout << "\t*Остальные символы не шифруются." << std::endl;
	std::cout << "\t*Ключи могут содержать как символы алфавита (того же, который использован в шифруемом тексте), так и цифры.\n" << std::endl;
	DrawLine();
	std::cout << std::endl;
	while (true)
	{
		std::cout << "Введите текст для шифрования: (quit - выход): ";
		std::string open_text{};
		std::getline(std::cin, open_text);
		if (open_text == "quit") break;
		//Проверка строки на моноалфавит.
		const std::string type_alphabet{ CheckMixedAlphabet(open_text) };
		if (type_alphabet == "MIXED")
		{
			std::cout << "Ошибка! Строка для шифрования должна содержать символы из одного алфавита. Попробуйте снова." << std::endl << std::endl;
			continue;
		}
		//Проверка необходимости шифровать.
		if (type_alphabet == "NONE")
		{
			std::cout << "<Отсутствует текст для Шифрования/Дешифрования!!!>" << std::endl;
			std::cout << "Зашифрованная строка: " << open_text << std::endl;
			std::cout << "Дешифрованная строка: " << open_text << std::endl;
			DrawLine();
			std::cout << std::endl;
			continue;
		}

		//Ввод ключей шифрования K1, K2, ..., Kn.
		bool exit{ false };
		int key_num{ 1 };
		std::string key_contour_poly{};
		std::vector<std::string> keys{};
		while (key_contour_poly != "#end")
		{
			std::cout << "Введите значение ключа K_" << key_num << ": (#quit - выход, #end - конец ввода ключей)" << std::endl;
			std::cout << "Ключ K_" << key_num << ": ";
			std::getline(std::cin, key_contour_poly);
			if (key_contour_poly == "#quit")
			{
				exit = true;
				break;
			}
			if (key_contour_poly == "#end")
				break;
			else
			{
				//Проверка значения ключа K.
				if (!CheckKeyCorrect(type_alphabet, key_contour_poly))
				{
					std::cout << "Ошибка! Ключ шифрования должен содержать символы того же алфавита, что и шифруемый текст, либо цифры." << std::endl << std::endl;
					continue;
				}
			}
			keys.push_back(key_contour_poly);
			key_num++;
		}
		if (key_contour_poly == "#quit")
		{
			keys.clear();
			break;
		}

		DisplayContourPolyTable(type_alphabet, open_text, keys);
		std::string encrypt_str{ ContourPolyEncryption(open_text, keys, type_alphabet) };
		std::string	decrypt_str{ ContourPolyDecryption(encrypt_str, keys, type_alphabet) };
		std::cout << "Зашифрованная строка: " << encrypt_str << std::endl;
		std::cout << "Дешифрованная строка: " << decrypt_str << std::endl;
		DrawLine();
		std::cout << std::endl;
	}
}