#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

bool init(double mass[NM], double& a, int& n)
{
    std::cout << "Введите действительное число a: ";
    a = checkValue();
    std::cout << "Введите натуральное число n: ";
    while (true)
    {
        if (getValue_mass(n))
        {
            std::cout << "Введите числа x1, x2, ..., xn соответственно такие, что x{1} <= x{2} <= ... <= x{n}: " << std::endl;
            for (int i = 0; i <= n - 1; i++)
            {
                std::cout << "Число x{" << i + 1 << "}=";
                mass[i] = checkValue();
                if (i > 0 && mass[i] < mass[i - 1])
                {
                    std::cout << "Введённое вами число x{" << i + 1 << "} < числа x{" << i << "}, что не удовлетворяет условию задачи." << std::endl;
                    return false;
                };
            }
            return true;
        }
        else
        {
            std::cout << "Число n должно быть натуральным, повторите ввод:" << std::endl;
        }
    }
}
bool finit(std::ifstream& f, double mass[NM], double& a, int& n, double& b)
{
    f >> a;
    if (f.fail())
    {
        std::cout << "Ошибка ввода из файла числа a." << std::endl;
        return false;
    }
    f >> b;
    if (f.fail() || b <= 0 || b != int(b))
    {
        std::cout << "Ошибка ввода из файла числа n." << std::endl;
        return false;
    }
    else
        n = int(b);
    for (unsigned i = 0; i <= n - 1; i++)
    {
        f >> mass[i];
        if (f.fail())
        {
            std::cout << "Ошибка ввода из файла числа d{" << i << "}" << std::endl;
            return false;
        }
        if (i > 0 && mass[i] < mass[i - 1])
        {
            std::cout << "Введённое из файла число x{" << i + 1 << "} < числа x{" << i << "}, что не удовлетворяет условию задачи." << std::endl;
            return false;
        }
    }
    return true;
}
double checkValue()
{
    while (true)
    {
        double a;
        std::cin >> a;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Вы ввели не число. Повторите ввод: \n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}
double getValue_mass(int& n)
{
    while (true)
    {
        double a;
        std::cin >> a;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Вы ввели не число. Повторите ввод: \n";
        }
        else
        {
            if (a != int(a) || a <= 0)
                return false;
            else
            {
                n = a;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;
            }
        }
    }
}
void forder(std::ostream& f, double mass[NM], double a, int n)
{
    f << "Введенные вами числа a, n соответственно: " << a << " " << n << std::endl;
    f << "Введенные вами числа x1, x2, ..., xn соответственно:" << std::endl;
    for (int i = 0; i <= n - 1;i++)
    {
        f << mass[i] << "\t";
    }
    f << std::endl;
    mass[n] = a;
    double k;
    for (int i = 0;i <= n - 1; i++)
    {
        for (int j = 0;j <= n - 1; j++)
        {
            if (mass[j] > mass[j + 1])
            {
                k = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = k;
            }
        }
    }
    f << "Ваша искомая последовательность y{1}, ..., y{n+1} такая, что y{1} <= y{2} <= ... <= y{n+1} :" << std::endl;
    f << mass[0] << " ";
    for (int i = 1;i <= n; i++)
    {
        f << "<= " << mass[i] << " ";
    }
    f << std::endl;
}
bool getNext()
{
    std::cout << "Продолжить? (0 - нет, 1 - да): ";
    while (true)
    {
        char sm;
        std::cin >> sm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (sm == '0' || sm == '1')
        {
            return sm == '1' ? true : false;
        }
        else
        {
            std::cout << "Ошибка ввода. Введите 0 или 1: \n";
        }
    }
}
unsigned char get_0_1()
{
    while (true)
    {
        char sm;
        std::cin >> sm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (sm == '0' || sm == '1')
        {
            return sm;
        }
        else
        {
            std::cout << "Ошибка ввода. Введите 0 или 1: \n";
        }
    }
}
