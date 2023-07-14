#include <iostream> // для консоли
#include <string> // для строк

#include "WorkWithFunc.h"
#include "RPN.h"

void PrePrint()
{
	std::cout << std::string(125, '-') << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << std::string(95, ' ') << "Горшков Андрей Олегович" << std::endl;
	std::cout << std::string(107, ' ') << "Группа 4212" << std::endl;
	std::cout << "Номер в списке группы g = 4212\nНомер в списке группы n = 3" << std::endl << std::endl;
	std::cout << "Унарная операция из табл. 1 выбирается под номером (g + n - 1)(mod 6) + 1, где s = [n / 7], [.] - целая часть числа.\n"
		<< "Таким образом, номер унарной операции из табл. 1: '3'" << std::endl << std::endl;
	std::cout << "Бинарная операция из табл. 2 выбирается под номером (g + n - 1)(mod 7) + 1.\n"
		<< "Таким образом, номер бинарной операции из табл. 2: '1'" << std::endl << std::endl;
	std::cout << "Стандартная форма представления функции под номером (g + n - 1)(mod 3) + 1.\n"
		<< "Таким образом, номер стандартной формы представления функции: '3'" << std::endl << std::endl;
	std::cout << std::string(125, '-') << std::endl << std::endl;
}
void MenuPrint()
{
	std::cout << "Что вы хотите сделать?\n"
		<< "1 - Задать число k (k-значная логика).\n"
		<< "2 - Задать число n (одна/две существенные переменные задаваемой функции k-значной логики).\n"

		<< "3 - Ввод функции k-значной логики в аналитической форме, как суперпозиции k-значных функций следующих типов:\n"
		<< "\t+ любой постоянной функции;\n"
		<< "\t+ определенной индивидуальным заданием унарной операции(см.Табл. 1 и п. Выбор варианта в исходном файле с заданием)\n"
		<< "\t+ определенной индивидуальным заданием бинарной операции (см. Табл. 2 и п. Выбор варианта в исходном файле с заданием)\n"

		<< "4 - Получение значений заданной функции (в виде таблицы).\n"

		<< "5 - Получение одной из стандартных форм представления введенной функции (см. п. Выбор варианта в исходном файле):\n"
		<< "\t1. первой формы (аналога СДНФ);\n"
		<< "\t2. второй формы;\n"
		<< "\t3. аналога СКНФ.\n"
		<< "\t(форма будет выведена с учетом возможных сокращений - в соответствии со значениями функции);\n"

		<< "6 - Получение информации о принадлежности заданной функции классу T(E) (множество E задается пользователем).\n"
		<< "7 - Выход.\n";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
			return choice[0];
		else
			std::cout << "Вы должны ввести целое число от 1 до 7. Повторите ввод. " << std::endl;
	}
}

int convertStrToInt(std::string const& convertStr)
{
	int number{};
	for (int i{}; i < convertStr.length();i++)
	{
		number += static_cast<int>((convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i));
	}
	return number;
}
bool checkStrIsNumeric(std::string const& userStr)
{
	for (int i{}; i < userStr.length();i++)
		if (userStr[i] < '0' || userStr[i] > '9')
			return false;
	return true;
}
std::string getNumber(const char& sign)
{
	switch (sign)
	{
	case '0':
		return "0";
		break;
	case '1':
		return "1";
		break;
	case '2':
		return "2";
		break;
	case '3':
		return "3";
		break;
	case '4':
		return "4";
		break;
	case '5':
		return "5";
		break;
	case '6':
		return "6";
		break;
	case '7':
		return "7";
		break;
	case '8':
		return "8";
		break;
	case '9':
		return "9";
		break;
	}
}
std::string CharToStr(const char& sign)
{
	switch (sign)
	{
	case '(':
		return "(";
		break;
	case ')':
		return ")";
		break;
	case '*':
		return "*";
		break;
	case '&':
		return "&";
		break;
	case '~':
		return "~";
		break;
	case 'x':
		return "x";
		break;
	case 'y':
		return "y";
		break;
	}
}
std::string get0_1()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите 0 или 1: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) == 0 || convertStrToInt(userStr) == 1)
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите 0 или 1: ";
	}
}

void getNumberK(Func*& func)
{
	if (func->k != 0)
	{
		std::cout << "Вы хотите задать значение k заново? (1 - да, 0 - нет): ";
		std::string userStr{ get0_1() };
		if (userStr == "0") return;
	}
	std::cout << "Введите значение числа k для k-значной логики: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите натуральное число: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0)
		{
			func->k = convertStrToInt(userStr);
			break;
		}
		else
			std::cout << "Ошибка ввода. Введите натуральное число: ";
	}
	std::cout << "Число k было успешно получено." << std::endl;
}

void getNumberN(Func*& func)
{
	if (func->n != 0)
	{
		std::cout << "Вы хотите задать значение n заново? (1 - да, 0 - нет): ";
		std::string userStr{ get0_1() };
		if (userStr == "0") return;
	}
	std::cout << "Введите значение числа n (одна/две существенные переменные задаваемой функции k-значной логики): ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr == "1" || userStr == "2")
		{
			func->n = convertStrToInt(userStr);
			break;
		}
		else
			std::cout << "Ошибка ввода. Введите число 1 или 2: ";
	}
	std::cout << "Число n было успешно получено." << std::endl;
}

bool findErrorSubstr(std::string const& func)
{
	for (int i{}; i < func.length() - 1; i++)
	{
		int k{ i + 1 };
		if ((func[i] == '~' && func[k] == '&') ||
			(func[i] == 'x' && func[k] == '~') ||
			(func[i] == 'y' && func[k] == '~') ||
			(func[i] == '(' && func[k] == '&') ||
			(func[i] == '&' && func[k] == ')') ||
			(func[i] == '&' && func[k] == '&') ||
			(func[i] == '(' && func[k] == ')') ||
			(func[i] == ')' && func[k] == '(') ||
			(func[i] == 'x' && func[k] == 'y') ||
			(func[i] == 'y' && func[k] == 'x') ||
			(func[i] >= '0' && func[i] <= '9' && (func[k] == '(' || func[k] == 'x' || func[k] == 'y')) ||
			((func[i] == 'x' || func[i] == 'y') && (func[k] >= '0' && func[k] <= '9' || func[k] == '('))
			)
		{
			return true;
		}
	}
	return false;
}
bool functionIsOK(const Func* func, std::string const& user_func)
{
	bool isY{ false }; //Для двух переменных ведет учет есть у или нет.
	std::string str_number{}; bool number{ false }; //Проверка чисел.
	int count_open_bracket{}, count_close_bracket{};//Сооветствие кол-ва открытых и закрытых скобок.

	//Обработка строки функции.
	for (int i{}; i < user_func.length(); i++)
	{
		//Проверка чисел. Вынесена наверх для обработки в первую очередь. Если было число и встретилось не число, то набранное число проверяем:
		if (number && (user_func[i] < '0' || user_func[i] > '9'))
		{
			if (convertStrToInt(str_number) >= func->k)
			{
				std::cout << "Ваша функция содержит число, превышающее максимальное значение k-значной логики, то есть " << func->k - 1 << ". Функция была сброшена." << std::endl;
				return false;
			}
			number = false;
			str_number = "";
		}
		//Обработка допустимых знаков с оговоркой на недопустимые.
		if (user_func[i] == 'x' ||
			user_func[i] == '&' ||
			user_func[i] == '~' ||
			user_func[i] == '(' ||
			user_func[i] == ')')
		{
			if (user_func[i] == '(') count_open_bracket++;
			if (user_func[i] == ')') count_close_bracket++;
			continue;
		}
		else if (user_func[i] >= '0' && user_func[i] <= '9')
		{
			number = true;
			str_number += getNumber(user_func[i]);
		}
		else
		{
			if (func->n == 2 && user_func[i] == 'y')
			{
				isY = true;
				continue;
			}
			std::cout << "Ваша функция содержит недопустимый символ. Текущий символ: " << user_func[i] << ". Функция была сброшена." << std::endl;
			return false;
		}
	}

	//Дополнительные проверки по проанализированным данным.
	if (func->n == 2 && !isY)
	{
		std::cout << "Было указано, что функция содержит 2 существенные переменные, но вы ввели только одну. Функция была сброшена." << std::endl;
		return false;
	}
	if (count_open_bracket != count_close_bracket)
	{
		std::cout << "Ваша функция содержит лишнюю открывающую/закрывающую скобку. Функция была сброшена." << std::endl;
		return false;
	}
	if (user_func[0] == '&' || user_func[user_func.length() - 1] == '&' || user_func[user_func.length() - 1] == '~')
	{
		std::cout << "Начало или конец функции содержит оператор без соответствующих операндов. Функция была сброшена." << std::endl;
		return false;
	}
	if (findErrorSubstr(user_func))
	{
		std::cout << "Функция имеет ошибки написания. Функция была сброшена." << std::endl;
		return false;
	}
	return true;
}
void getFunction(Func*& func)
{
	std::cout << "Подсказки:\nОтрицание Лукасевича: ~x;\nМинимум (обобщение дизъюнкции): x&y;\n"
		<< "Постоянная: число в пределах k-значной логики.\n"
		<< "Скобки: открывающая - '(', закрывающая - ')'." << std::endl;
	std::cout << "Функция не должна содержать пробелов. Все выражение вводится целиком без пробелов." << std::endl << std::endl;
	if (func->n == 1) std::cout << "Введите вашу функцию: f(x) = ";
	else std::cout << "Введите вашу функцию: f(x, y) = ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			if (func->n == 1) std::cout << "Ошибка ввода, функция не может быть пустой. Повторите ввод, f(x) = ";
			else std::cout << "Ошибка ввода, функция не может быть пустой. Повторите ввод, f(x, y) = ";
		else if (functionIsOK(func, userStr))
		{
			func->func = userStr;
			break;
		}
		else
			if (func->n == 1) std::cout << "Ошибка ввода. Повторите ввод, f(x) = ";
			else std::cout << "Ошибка ввода. Повторите ввод, f(x, y) = ";
	}
	std::cout << "Функция была успешно получена." << std::endl;
}

void AddOutStringNewElem(const char& sign, OutString*& cur_char)
{
	OutString* new_char = new OutString{};

	std::string str_value{ CharToStr(sign) };
	new_char->current_out_value = str_value;

	cur_char->next = new_char;
	new_char->prev = cur_char;
	cur_char = cur_char->next;
}
void AddStackNewElem(const char& sign, Stack*& sp)
{
	Stack* new_sign = new Stack{};
	new_sign->current_value = sign;

	if (sp->next != nullptr) new_sign->next = sp->next;
	sp->next = new_sign;
}
void addOutStringNewElemFromStack(Stack*& sp, OutString*& cur_char)
{
	OutString* new_char = new OutString{};

	std::string str_value{ CharToStr(sp->next->current_value) };
	new_char->current_out_value = str_value;

	cur_char->next = new_char;
	new_char->prev = cur_char;
	cur_char = cur_char->next;

	Stack* del_ptr{ sp->next };
	sp->next = sp->next->next;
	delete del_ptr;
}
void getRPNstring(Func*& func, Stack*& sp, OutString*& RPN_string)
{
	OutString* cur_char{ RPN_string }; //Реализуется структура для ОПН(ОПЗ)
	std::string str_const_number{}; bool meet_const{ false };
	for (int i{}; i < func->func.length(); i++)
	{
		//Аналогично functionIsOK, обработка вынесена наверх для чисел.
		if (meet_const && (func->func[i] < '0' || func->func[i] > '9'))
		{
			OutString* new_const = new OutString{};
			new_const->current_out_value = str_const_number;

			cur_char->next = new_const;
			new_const->prev = cur_char;
			cur_char = cur_char->next;

			meet_const = false;
			str_const_number = "";
		}
		switch (func->func[i])
		{
		case '(':
		{
			AddStackNewElem(func->func[i], sp);
			break;
		}
		case ')':
		{
			//Проверка сделана для компилятора, которому нужна гарантия, что указатель не будет nullptr, хотя ')' идет только после '(', иначе будет ошибка.
			if (sp->next != nullptr)
			{
				while (sp->next->current_value != '(')
				{
					addOutStringNewElemFromStack(sp, cur_char);
				}

				//Стек выгрузили до (, теперь ее надо удалить с него тоже, как обработанную.
				Stack* del_open_bracket{ sp->next };
				sp->next = sp->next->next;
				delete del_open_bracket;

				//Если перед ( стояло ~, то выгружаем и этот оператор.
				if (sp->next != nullptr && sp->next->current_value == '~')
				{
					while (sp->next != nullptr && sp->next->current_value == '~')
						addOutStringNewElemFromStack(sp, cur_char);
				}
			}
			break;
		}
		case '&':
		{
			AddStackNewElem(func->func[i], sp);
			break;
		}
		case '~':
		{
			//Просто добавляем оператор в стек, так как дальше будет либо скобка, либо константа, либо переменная.
			Stack* new_sign = new Stack{};
			new_sign->current_value = func->func[i];

			if (sp->next != nullptr) new_sign->next = sp->next;
			sp->next = new_sign;
			break;
		}
		case 'x':
		{
			//После описанных выше проверок будем считать, что строка функции написана идеально.
			//Встретили переменную, проверяем стек операторов, если есть ~ или &, то выгружаем их.
			AddOutStringNewElem(func->func[i], cur_char);
			if (sp->next != nullptr && sp->next->current_value == '~')
			{
				while (sp->next != nullptr && sp->next->current_value == '~')
					addOutStringNewElemFromStack(sp, cur_char);
			}
			else if (sp->next != nullptr && sp->next->current_value == '&')
			{
				addOutStringNewElemFromStack(sp, cur_char);
			}
			break;
		}
		case 'y':
		{
			//После описанных выше проверок будем считать, что строка функции написана идеально. Если y встретилась - функция обязательно двух переменных, никак иначе.
			//Встретили переменную, проверяем стек операторов, если есть ~ или &, то выгружаем их.
			AddOutStringNewElem(func->func[i], cur_char);
			if (sp->next != nullptr && sp->next->current_value == '~')
			{
				while (sp->next != nullptr && sp->next->current_value == '~')
					addOutStringNewElemFromStack(sp, cur_char);
			}
			else if (sp->next != nullptr && sp->next->current_value == '&')
			{
				addOutStringNewElemFromStack(sp, cur_char);
			}
			break;
		}
		default:
		{
			//Встретили цифру - активируем обработку символов как число.
			meet_const = true;
			str_const_number += getNumber(func->func[i]);
			break;
		}
		}
	}
	//Выгружаем стек от вершины вниз, как и добавлялись операторы. Чем позднее оператор, тем более позднее выполнение он имеет.
	//Строка заполнялась слева направо, значит то, что вносилось в строку имеет позднее время выполнения. Аналогично выгружаем.
	while (sp->next != nullptr)
		addOutStringNewElemFromStack(sp, cur_char);
}

void AddElemResult(Result*& cur_res, const int& value)
{
	Result* new_value = new Result{};
	new_value->value = value;

	if (cur_res->next != nullptr) new_value->next = cur_res->next;
	cur_res->next = new_value;
}
int getResult(OutString*& outstring, const int& x, const int& y, const int& k)
{
	Result* cur_res = new Result{}; //Реализуем структуру для подсчета значений функции относительно ОПН(ОПЗ). Это заголовочный элнемент, пустой. HEAD->new->...->...
	OutString* cur_char{ outstring->next }; //Считываем первый символ.
	bool meet_const{ false }; std::string const_number{};
	while (cur_char != nullptr)
	{
		//Подобно описанным выше подсчетам числа функциям, поступаем и здесь.
		if (meet_const && (cur_char->current_out_value[0] < '0' || cur_char->current_out_value[0] > '9'))
		{
			AddElemResult(cur_res, convertStrToInt(const_number));
			meet_const = false;
			const_number = "";
		}
		//Обработка символов. В зависимости от символа выполняется то или иное действие. Считывает структуру ОПН(ОПЗ) слева направо.
		switch (cur_char->current_out_value[0])
		{
		case 'x':
		{
			AddElemResult(cur_res, x);
			break;
		}
		case 'y':
		{
			AddElemResult(cur_res, y);
			break;
		}
		case '&':
		{
			Result* first_value{ cur_res->next };
			Result* second_value{ cur_res->next->next };
			int result{ first_value->value <= second_value->value ? first_value->value : second_value->value };

			cur_res->next = second_value->next;
			delete first_value;
			delete second_value;

			AddElemResult(cur_res, result);
			break;
		}
		case '~':
		{
			int result_value{ k - 1 - cur_res->next->value };
			cur_res->next->value = result_value;
			break;
		}
		default:
			//Встретили цифру - активируем обработку символов как число.
			meet_const = true;
			const_number += cur_char->current_out_value[0];
			break;
		}
		cur_char = cur_char->next;
	}
	int result{ cur_res->next->value };
	delete cur_res->next;
	delete cur_res;
	return result;
}

void getValuesOfFunc(Func*& func, Stack*& stack_signs, OutString*& RPN_string, int*& result_of_function)
{
	getRPNstring(func, stack_signs, RPN_string);

	//Вывод информации о функции.
	std::cout << "Ваша функция: " << func->func << std::endl;

	std::cout << "ОПН(ОПЗ) от функции: ";
	OutString* cur_char{ RPN_string->next }; //Считываем первый символ.
	while (cur_char != nullptr)
	{
		std::cout << cur_char->current_out_value;
		cur_char = cur_char->next;
	}
	std::cout << std::endl;
	//Конец вывода.

	std::cout << std::endl;
	std::cout << "\t Таблица: " << std::endl;
	if (func->n == 1) std::cout << "\t-----------------\n\t|   x   |  f(x) |\n\t-----------------" << std::endl;
	else std::cout << "\t-------------------------\n\t|   x   |   y   |f(x,y) |\n\t-------------------------" << std::endl;
	if (func->n == 1)
	{
		result_of_function = new int[func->k]{};
		for (int x{}; x < func->k; x++)
		{
			result_of_function[x] = getResult(RPN_string, x, 0, func->k);
			if (x < 10) 
				std::cout << "\t|   " << x << "   |";
			else 
				std::cout << "\t|  " << x << "   |";
			if (result_of_function[x] < 10)
				std::cout << "   " << result_of_function[x] << "   |\n\t-----------------" << std::endl;
			else
				std::cout << "  " << result_of_function[x] << "   |\n\t-----------------" << std::endl;
		}
	}
	else
	{
		result_of_function = new int[func->k * func->k]{};
		for (int x{}; x < func->k; x++)
			for (int y{}; y < func->k; y++)
			{
				result_of_function[x * func->k + y] = getResult(RPN_string, x, y, func->k);
				if (x < 10)
					std::cout << "\t|   " << x << "   |";
				else
					std::cout << "\t|  " << x << "   |";
				if (y < 10)
					std::cout << "   " << y << "   |";
				else
					std::cout << "  " << y << "   |";
				if (result_of_function[x * func->k + y] < 10)
					std::cout << "   " << result_of_function[x * func->k + y] << "   |\n\t-------------------------" << std::endl;
				else
					std::cout << "  " << result_of_function[x * func->k + y] << "   |\n\t-------------------------" << std::endl;
			}
	}
}

void getSKNFform(Func*& func, int*& result_of_function)
{
	int count_ind{};
	std::cout << "Подсказка: J_i - характеристическая функция (первого рода) числа i(i принадлежит Ek)." << std::endl << std::endl;
	if (func->n == 1)
	{
		std::cout << "\tАналог СКНФ: " << std::endl;
		std::cout << "f(x) = ";
		bool first_out{ false };
		for (int x{}; x < func->k; x++)
		{
			if (result_of_function[x] == func->k - 1)
				continue;
			if (result_of_function[x] == 0)
				//Вывод, когда значение = 0
				if (!first_out)
				{
					std::cout << "~J_" << x << "(x)";
					first_out = true;
					count_ind++;
				}
				else
				{
					std::cout << " & ~J_" << x << "(x)";
					count_ind++;
				}
			else
				//Вывод для ост. значений
				if (!first_out)
				{
					std::cout << "(" << result_of_function[x] << " v ~J_" << x << "(x))";
					first_out = true;
					count_ind++;
				}
				else
				{
					std::cout << " & (" << result_of_function[x] << " v ~J_" << x << "(x))";
					count_ind++;
				}
			if (count_ind % 5 == 0 && x != func->k - 1)
				std::cout << " &\n      ";
		}
	}
	else
	{
		std::cout << "Аналог СКНФ: " << std::endl;
		std::cout << "f(x,y) = ";
		bool first_out{ false };
		for (int x{}; x < func->k; x++)
			for (int y{}; y < func->k; y++)
			{
				if (result_of_function[x * func->k + y] == func->k - 1)
					continue;
				if (result_of_function[x * func->k + y] == 0)
					//Вывод, когда результат = 0
					if (!first_out)
					{
						std::cout << "(~J_" << x << "(x) v ~J_" << y << "(y))";
						first_out = true;
						count_ind++;
					}
					else
					{
						std::cout << " & (~J_" << x << "(x) v ~J_" << y << "(y))";
						count_ind++;
					}
				else
					if (!first_out)
					{
						std::cout << "(" << result_of_function[x * func->k + y] << " v ~J_" << x << "(x) v ~J_" << y << "(y))";
						first_out = true;
						count_ind++;
					}
					else
					{
						std::cout << " & (" << result_of_function[x * func->k + y] << " v ~J_" << x << "(x) v ~J_" << y << "(y))";
						count_ind++;
					}
				if (count_ind % 5 == 0 && (x != func->k - 1 || y != func->k - 1))
					std::cout << " &\n        ";
			}
	}
	std::cout << "." << std::endl << std::endl;
}

bool checkStrForCorrect(std::string const& userStr, Func*& func, int*& mass_of_save_values, int& count_of_save_values)
{
	//Обработка всех ошибочных символов, то есть не _ или 0..9
	for (int i{}; i < userStr.length(); i++)
	{
		if ((userStr[i] != ' ' && (userStr[i] < '0' && userStr[i] > '9')))
			return false;
	}

	//Два пробела подряд
	for (int i{}; i < userStr.length() - 1; i++)
	{
		int k{ i + 1 };
		if ((userStr[i] == ' ' && userStr[k] == ' '))
			return false;
	}
	//Крайние случаи
	if (userStr[0] == ' ' || userStr[userStr.length() - 1] == ' ')
		return false;

	int index{};
	count_of_save_values = 0;
	mass_of_save_values = new int[func->k]{};
	while (index != userStr.length())
	{
		if (userStr[index] >= '0' && userStr[index] <= '9')
		{
			std::string cur_num{};
			//Набор числа
			while (true)
			{
				cur_num += getNumber(userStr[index]);
				index++;
				if (userStr[index] == ' ' || index == userStr.length())
					break;
			}
			//Число начинается с 0
			if (cur_num.length() >= 2 && cur_num[0] == '0')
				return false;
			if (convertStrToInt(cur_num) >= func->k)
			{
				std::cout << "Введенная вами строка содержит значение, которое превышает максимально возможное, то есть " << func->k - 1 << ". Строка была сброшена." << std::endl;
				return false;
			}
			else
			{
				//Проверяем, нет ли повторений введенных значений
				for (int i{}; i < count_of_save_values; i++)
				{
					if (mass_of_save_values[i] == convertStrToInt(cur_num))
					{
						std::cout << "Введенные вами значения имеют повторения. Строка была сброшена." << std::endl;
						delete[] mass_of_save_values;
						mass_of_save_values = nullptr;
						count_of_save_values = 0;
						return false;
					}
				}
				if (count_of_save_values < func->k) //Проверка сделана для компилятора, которому нужна гарантия, что индекс не выйдет за пределы массива.
					mass_of_save_values[count_of_save_values] = convertStrToInt(cur_num); //Добавление числа
				count_of_save_values++;
			}
		}
		else
			index++;
	}
	return true;
}
std::string getValueString(Func*& func, int*& mass_of_save_values, int& count_of_save_values)
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Строка не может быть пустой: ";
		else if (checkStrForCorrect(userStr, func, mass_of_save_values, count_of_save_values))
		{
			std::cout << "Строка значений была успешно получена." << std::endl;
			return userStr;
		}
		else
			std::cout << "Заданная строка содержит ошибки. Повторите ввод: ";
	}
}
void printMassOfSaveValues(const int* mass_of_save_values, const int& count_of_save_values)
{
	for (int i{}; i < count_of_save_values; i++)
		if (i != count_of_save_values - 1)
			std::cout << mass_of_save_values[i] << ";";
		else
			std::cout << mass_of_save_values[i] << "}." << std::endl;
}
void getSaveData(Func*& func, int*& result_of_function)
{
	int* mass_of_save_values{ nullptr }; //Массив значений для проверки.
	int count_of_save_values{}; //Сколько значений в массиве.
	std::cout << "Введите значения множества E через пробел: ";
	std::string ValueSet{ getValueString(func, mass_of_save_values, count_of_save_values) };
	if (func->n == 1)
	{
		for (int x{}; x < func->k; x++)
		{
			bool x_is_in_set{ false }; //Если текущее значение переменной принадлежит значению множества, будем смотреть значение функции.
			for (int index{}; index < count_of_save_values; index++)
				if (x == mass_of_save_values[index])
				{
					x_is_in_set = true;
					break;
				}
			if (x_is_in_set)
			{
				bool res_is_in_set{ false };//Если текущее значение функции принадлежит значению множества, значит сохраняет.
				for (int index{}; index < count_of_save_values; index++)
					if (result_of_function[x] == mass_of_save_values[index])
					{
						res_is_in_set = true;
						break;
					}
				if (!res_is_in_set)
				{
					std::cout << "f(x) не принадлежит T(E), то есть не сохраняет E: {";
					printMassOfSaveValues(mass_of_save_values, count_of_save_values);
					delete[] mass_of_save_values;
					return;
				}
			}
		}
		std::cout << "f(x) принадлежит T(E), то есть сохраняет E: {";
	}
	else
	{
		for (int x{}; x < func->k; x++)
			for (int y{}; y < func->k; y++)
			{
				bool x_is_in_set{ false };//Если текущее значение переменной х принадлежит значению множества, будем смотреть значение функции.
				bool y_is_in_set{ false };//Если текущее значение переменной у принадлежит значению множества, будем смотреть значение функции.
				for (int index{}; index < count_of_save_values; index++)
				{
					if (x == mass_of_save_values[index])
						x_is_in_set = true;
					if (y == mass_of_save_values[index])
						y_is_in_set = true;
					if (x_is_in_set && y_is_in_set)
						break;
				}
				if (x_is_in_set && y_is_in_set) 
				{
					bool res_is_in_set{ false }; //Если текущее значение функции принадлежит значению множества, значит сохраняет.
					for (int index{}; index < count_of_save_values; index++)
						if (result_of_function[x * func->k + y] == mass_of_save_values[index])
						{
							res_is_in_set = true;
							break;
						}
					if (!res_is_in_set)
					{
						std::cout << "f(x,y) не принадлежит T(E), то есть не сохраняет E: {";
						printMassOfSaveValues(mass_of_save_values, count_of_save_values);
						delete[] mass_of_save_values;
						return;
					}
				}
			}
		std::cout << "f(x,y) принадлежит T(E), то есть сохраняет E: {";
	}
	printMassOfSaveValues(mass_of_save_values, count_of_save_values);
	delete[] mass_of_save_values;
}

void ClearSomeStructs(int*& result_of_function, OutString*& RPN_string)
{
	if (result_of_function != nullptr)
	{
		delete[] result_of_function;
		result_of_function = nullptr;
	}
	if (RPN_string != nullptr)
		while (RPN_string->next != nullptr)
		{
			OutString* del_cur_ptr{ RPN_string->next };
			RPN_string->next = del_cur_ptr->next;
			if (del_cur_ptr->next != nullptr) del_cur_ptr->next->prev = RPN_string;
			del_cur_ptr->next = nullptr;
			del_cur_ptr->prev = nullptr;
			delete del_cur_ptr;
		}
}
void clearAllStructs(Func*& func, Stack*& stack_signs, OutString*& RPN_string)
{
	delete func;
	delete stack_signs;

	while (RPN_string->next != nullptr)
	{
		OutString* del_cur_ptr{ RPN_string->next };
		RPN_string->next = del_cur_ptr->next;
		if (del_cur_ptr->next != nullptr) del_cur_ptr->next->prev = RPN_string;
		del_cur_ptr->next = nullptr;
		del_cur_ptr->prev = nullptr;
		delete del_cur_ptr;
	}
	delete RPN_string;
}