#include <iostream> // ��� �������
#include <string> // ��� �����

#include "WorkWithFunc.h"
#include "RPN.h"

void PrePrint()
{
	std::cout << std::string(125, '-') << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << std::string(95, ' ') << "������� ������ ��������" << std::endl;
	std::cout << std::string(107, ' ') << "������ 4212" << std::endl;
	std::cout << "����� � ������ ������ g = 4212\n����� � ������ ������ n = 3" << std::endl << std::endl;
	std::cout << "������� �������� �� ����. 1 ���������� ��� ������� (g + n - 1)(mod 6) + 1, ��� s = [n / 7], [.] - ����� ����� �����.\n"
		<< "����� �������, ����� ������� �������� �� ����. 1: '3'" << std::endl << std::endl;
	std::cout << "�������� �������� �� ����. 2 ���������� ��� ������� (g + n - 1)(mod 7) + 1.\n"
		<< "����� �������, ����� �������� �������� �� ����. 2: '1'" << std::endl << std::endl;
	std::cout << "����������� ����� ������������� ������� ��� ������� (g + n - 1)(mod 3) + 1.\n"
		<< "����� �������, ����� ����������� ����� ������������� �������: '3'" << std::endl << std::endl;
	std::cout << std::string(125, '-') << std::endl << std::endl;
}
void MenuPrint()
{
	std::cout << "��� �� ������ �������?\n"
		<< "1 - ������ ����� k (k-������� ������).\n"
		<< "2 - ������ ����� n (����/��� ������������ ���������� ���������� ������� k-������� ������).\n"

		<< "3 - ���� ������� k-������� ������ � ������������� �����, ��� ������������ k-������� ������� ��������� �����:\n"
		<< "\t+ ����� ���������� �������;\n"
		<< "\t+ ������������ �������������� �������� ������� ��������(��.����. 1 � �. ����� �������� � �������� ����� � ��������)\n"
		<< "\t+ ������������ �������������� �������� �������� �������� (��. ����. 2 � �. ����� �������� � �������� ����� � ��������)\n"

		<< "4 - ��������� �������� �������� ������� (� ���� �������).\n"

		<< "5 - ��������� ����� �� ����������� ���� ������������� ��������� ������� (��. �. ����� �������� � �������� �����):\n"
		<< "\t1. ������ ����� (������� ����);\n"
		<< "\t2. ������ �����;\n"
		<< "\t3. ������� ����.\n"
		<< "\t(����� ����� �������� � ������ ��������� ���������� - � ������������ �� ���������� �������);\n"

		<< "6 - ��������� ���������� � �������������� �������� ������� ������ T(E) (��������� E �������� �������������).\n"
		<< "7 - �����.\n";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
			return choice[0];
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 7. ��������� ����. " << std::endl;
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
			std::cout << "������ �����. ������� 0 ��� 1: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) == 0 || convertStrToInt(userStr) == 1)
			return userStr;
		else
			std::cout << "������ �����. ������� 0 ��� 1: ";
	}
}

void getNumberK(Func*& func)
{
	if (func->k != 0)
	{
		std::cout << "�� ������ ������ �������� k ������? (1 - ��, 0 - ���): ";
		std::string userStr{ get0_1() };
		if (userStr == "0") return;
	}
	std::cout << "������� �������� ����� k ��� k-������� ������: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� ����������� �����: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0)
		{
			func->k = convertStrToInt(userStr);
			break;
		}
		else
			std::cout << "������ �����. ������� ����������� �����: ";
	}
	std::cout << "����� k ���� ������� ��������." << std::endl;
}

void getNumberN(Func*& func)
{
	if (func->n != 0)
	{
		std::cout << "�� ������ ������ �������� n ������? (1 - ��, 0 - ���): ";
		std::string userStr{ get0_1() };
		if (userStr == "0") return;
	}
	std::cout << "������� �������� ����� n (����/��� ������������ ���������� ���������� ������� k-������� ������): ";
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
			std::cout << "������ �����. ������� ����� 1 ��� 2: ";
	}
	std::cout << "����� n ���� ������� ��������." << std::endl;
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
	bool isY{ false }; //��� ���� ���������� ����� ���� ���� � ��� ���.
	std::string str_number{}; bool number{ false }; //�������� �����.
	int count_open_bracket{}, count_close_bracket{};//����������� ���-�� �������� � �������� ������.

	//��������� ������ �������.
	for (int i{}; i < user_func.length(); i++)
	{
		//�������� �����. �������� ������ ��� ��������� � ������ �������. ���� ���� ����� � ����������� �� �����, �� ��������� ����� ���������:
		if (number && (user_func[i] < '0' || user_func[i] > '9'))
		{
			if (convertStrToInt(str_number) >= func->k)
			{
				std::cout << "���� ������� �������� �����, ����������� ������������ �������� k-������� ������, �� ���� " << func->k - 1 << ". ������� ���� ��������." << std::endl;
				return false;
			}
			number = false;
			str_number = "";
		}
		//��������� ���������� ������ � ��������� �� ������������.
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
			std::cout << "���� ������� �������� ������������ ������. ������� ������: " << user_func[i] << ". ������� ���� ��������." << std::endl;
			return false;
		}
	}

	//�������������� �������� �� ������������������ ������.
	if (func->n == 2 && !isY)
	{
		std::cout << "���� �������, ��� ������� �������� 2 ������������ ����������, �� �� ����� ������ ����. ������� ���� ��������." << std::endl;
		return false;
	}
	if (count_open_bracket != count_close_bracket)
	{
		std::cout << "���� ������� �������� ������ �����������/����������� ������. ������� ���� ��������." << std::endl;
		return false;
	}
	if (user_func[0] == '&' || user_func[user_func.length() - 1] == '&' || user_func[user_func.length() - 1] == '~')
	{
		std::cout << "������ ��� ����� ������� �������� �������� ��� ��������������� ���������. ������� ���� ��������." << std::endl;
		return false;
	}
	if (findErrorSubstr(user_func))
	{
		std::cout << "������� ����� ������ ���������. ������� ���� ��������." << std::endl;
		return false;
	}
	return true;
}
void getFunction(Func*& func)
{
	std::cout << "���������:\n��������� ����������: ~x;\n������� (��������� ����������): x&y;\n"
		<< "����������: ����� � �������� k-������� ������.\n"
		<< "������: ����������� - '(', ����������� - ')'." << std::endl;
	std::cout << "������� �� ������ ��������� ��������. ��� ��������� �������� ������� ��� ��������." << std::endl << std::endl;
	if (func->n == 1) std::cout << "������� ���� �������: f(x) = ";
	else std::cout << "������� ���� �������: f(x, y) = ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			if (func->n == 1) std::cout << "������ �����, ������� �� ����� ���� ������. ��������� ����, f(x) = ";
			else std::cout << "������ �����, ������� �� ����� ���� ������. ��������� ����, f(x, y) = ";
		else if (functionIsOK(func, userStr))
		{
			func->func = userStr;
			break;
		}
		else
			if (func->n == 1) std::cout << "������ �����. ��������� ����, f(x) = ";
			else std::cout << "������ �����. ��������� ����, f(x, y) = ";
	}
	std::cout << "������� ���� ������� ��������." << std::endl;
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
	OutString* cur_char{ RPN_string }; //����������� ��������� ��� ���(���)
	std::string str_const_number{}; bool meet_const{ false };
	for (int i{}; i < func->func.length(); i++)
	{
		//���������� functionIsOK, ��������� �������� ������ ��� �����.
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
			//�������� ������� ��� �����������, �������� ����� ��������, ��� ��������� �� ����� nullptr, ���� ')' ���� ������ ����� '(', ����� ����� ������.
			if (sp->next != nullptr)
			{
				while (sp->next->current_value != '(')
				{
					addOutStringNewElemFromStack(sp, cur_char);
				}

				//���� ��������� �� (, ������ �� ���� ������� � ���� ����, ��� ������������.
				Stack* del_open_bracket{ sp->next };
				sp->next = sp->next->next;
				delete del_open_bracket;

				//���� ����� ( ������ ~, �� ��������� � ���� ��������.
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
			//������ ��������� �������� � ����, ��� ��� ������ ����� ���� ������, ���� ���������, ���� ����������.
			Stack* new_sign = new Stack{};
			new_sign->current_value = func->func[i];

			if (sp->next != nullptr) new_sign->next = sp->next;
			sp->next = new_sign;
			break;
		}
		case 'x':
		{
			//����� ��������� ���� �������� ����� �������, ��� ������ ������� �������� ��������.
			//��������� ����������, ��������� ���� ����������, ���� ���� ~ ��� &, �� ��������� ��.
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
			//����� ��������� ���� �������� ����� �������, ��� ������ ������� �������� ��������. ���� y ����������� - ������� ����������� ���� ����������, ����� �����.
			//��������� ����������, ��������� ���� ����������, ���� ���� ~ ��� &, �� ��������� ��.
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
			//��������� ����� - ���������� ��������� �������� ��� �����.
			meet_const = true;
			str_const_number += getNumber(func->func[i]);
			break;
		}
		}
	}
	//��������� ���� �� ������� ����, ��� � ����������� ���������. ��� ������� ��������, ��� ����� ������� ���������� �� �����.
	//������ ����������� ����� �������, ������ ��, ��� ��������� � ������ ����� ������� ����� ����������. ���������� ���������.
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
	Result* cur_res = new Result{}; //��������� ��������� ��� �������� �������� ������� ������������ ���(���). ��� ������������ ��������, ������. HEAD->new->...->...
	OutString* cur_char{ outstring->next }; //��������� ������ ������.
	bool meet_const{ false }; std::string const_number{};
	while (cur_char != nullptr)
	{
		//������� ��������� ���� ��������� ����� ��������, ��������� � �����.
		if (meet_const && (cur_char->current_out_value[0] < '0' || cur_char->current_out_value[0] > '9'))
		{
			AddElemResult(cur_res, convertStrToInt(const_number));
			meet_const = false;
			const_number = "";
		}
		//��������� ��������. � ����������� �� ������� ����������� �� ��� ���� ��������. ��������� ��������� ���(���) ����� �������.
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
			//��������� ����� - ���������� ��������� �������� ��� �����.
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

	//����� ���������� � �������.
	std::cout << "���� �������: " << func->func << std::endl;

	std::cout << "���(���) �� �������: ";
	OutString* cur_char{ RPN_string->next }; //��������� ������ ������.
	while (cur_char != nullptr)
	{
		std::cout << cur_char->current_out_value;
		cur_char = cur_char->next;
	}
	std::cout << std::endl;
	//����� ������.

	std::cout << std::endl;
	std::cout << "\t �������: " << std::endl;
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
	std::cout << "���������: J_i - ������������������ ������� (������� ����) ����� i(i ����������� Ek)." << std::endl << std::endl;
	if (func->n == 1)
	{
		std::cout << "\t������ ����: " << std::endl;
		std::cout << "f(x) = ";
		bool first_out{ false };
		for (int x{}; x < func->k; x++)
		{
			if (result_of_function[x] == func->k - 1)
				continue;
			if (result_of_function[x] == 0)
				//�����, ����� �������� = 0
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
				//����� ��� ���. ��������
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
		std::cout << "������ ����: " << std::endl;
		std::cout << "f(x,y) = ";
		bool first_out{ false };
		for (int x{}; x < func->k; x++)
			for (int y{}; y < func->k; y++)
			{
				if (result_of_function[x * func->k + y] == func->k - 1)
					continue;
				if (result_of_function[x * func->k + y] == 0)
					//�����, ����� ��������� = 0
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
	//��������� ���� ��������� ��������, �� ���� �� _ ��� 0..9
	for (int i{}; i < userStr.length(); i++)
	{
		if ((userStr[i] != ' ' && (userStr[i] < '0' && userStr[i] > '9')))
			return false;
	}

	//��� ������� ������
	for (int i{}; i < userStr.length() - 1; i++)
	{
		int k{ i + 1 };
		if ((userStr[i] == ' ' && userStr[k] == ' '))
			return false;
	}
	//������� ������
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
			//����� �����
			while (true)
			{
				cur_num += getNumber(userStr[index]);
				index++;
				if (userStr[index] == ' ' || index == userStr.length())
					break;
			}
			//����� ���������� � 0
			if (cur_num.length() >= 2 && cur_num[0] == '0')
				return false;
			if (convertStrToInt(cur_num) >= func->k)
			{
				std::cout << "��������� ���� ������ �������� ��������, ������� ��������� ����������� ���������, �� ���� " << func->k - 1 << ". ������ ���� ��������." << std::endl;
				return false;
			}
			else
			{
				//���������, ��� �� ���������� ��������� ��������
				for (int i{}; i < count_of_save_values; i++)
				{
					if (mass_of_save_values[i] == convertStrToInt(cur_num))
					{
						std::cout << "��������� ���� �������� ����� ����������. ������ ���� ��������." << std::endl;
						delete[] mass_of_save_values;
						mass_of_save_values = nullptr;
						count_of_save_values = 0;
						return false;
					}
				}
				if (count_of_save_values < func->k) //�������� ������� ��� �����������, �������� ����� ��������, ��� ������ �� ������ �� ������� �������.
					mass_of_save_values[count_of_save_values] = convertStrToInt(cur_num); //���������� �����
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
			std::cout << "������ �����. ������ �� ����� ���� ������: ";
		else if (checkStrForCorrect(userStr, func, mass_of_save_values, count_of_save_values))
		{
			std::cout << "������ �������� ���� ������� ��������." << std::endl;
			return userStr;
		}
		else
			std::cout << "�������� ������ �������� ������. ��������� ����: ";
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
	int* mass_of_save_values{ nullptr }; //������ �������� ��� ��������.
	int count_of_save_values{}; //������� �������� � �������.
	std::cout << "������� �������� ��������� E ����� ������: ";
	std::string ValueSet{ getValueString(func, mass_of_save_values, count_of_save_values) };
	if (func->n == 1)
	{
		for (int x{}; x < func->k; x++)
		{
			bool x_is_in_set{ false }; //���� ������� �������� ���������� ����������� �������� ���������, ����� �������� �������� �������.
			for (int index{}; index < count_of_save_values; index++)
				if (x == mass_of_save_values[index])
				{
					x_is_in_set = true;
					break;
				}
			if (x_is_in_set)
			{
				bool res_is_in_set{ false };//���� ������� �������� ������� ����������� �������� ���������, ������ ���������.
				for (int index{}; index < count_of_save_values; index++)
					if (result_of_function[x] == mass_of_save_values[index])
					{
						res_is_in_set = true;
						break;
					}
				if (!res_is_in_set)
				{
					std::cout << "f(x) �� ����������� T(E), �� ���� �� ��������� E: {";
					printMassOfSaveValues(mass_of_save_values, count_of_save_values);
					delete[] mass_of_save_values;
					return;
				}
			}
		}
		std::cout << "f(x) ����������� T(E), �� ���� ��������� E: {";
	}
	else
	{
		for (int x{}; x < func->k; x++)
			for (int y{}; y < func->k; y++)
			{
				bool x_is_in_set{ false };//���� ������� �������� ���������� � ����������� �������� ���������, ����� �������� �������� �������.
				bool y_is_in_set{ false };//���� ������� �������� ���������� � ����������� �������� ���������, ����� �������� �������� �������.
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
					bool res_is_in_set{ false }; //���� ������� �������� ������� ����������� �������� ���������, ������ ���������.
					for (int index{}; index < count_of_save_values; index++)
						if (result_of_function[x * func->k + y] == mass_of_save_values[index])
						{
							res_is_in_set = true;
							break;
						}
					if (!res_is_in_set)
					{
						std::cout << "f(x,y) �� ����������� T(E), �� ���� �� ��������� E: {";
						printMassOfSaveValues(mass_of_save_values, count_of_save_values);
						delete[] mass_of_save_values;
						return;
					}
				}
			}
		std::cout << "f(x,y) ����������� T(E), �� ���� ��������� E: {";
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