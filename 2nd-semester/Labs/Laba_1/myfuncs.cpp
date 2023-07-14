#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

bool init(double mass[NM], double& a, double& h, double& b, int& n)
{
    std::cout << "Введите действительное число a: ";
    a = getValue();
    std::cout << "Введите действительное число h: ";
    h = getValue();
    std::cout << "Введите действительное число b: ";
    b = getValue();
    std::cout << "Введите натуральное число n: ";
    n = checkValue();
    if (checkValue_mass(n))
    {
        std::cout << "Введите числа d0, d1, ..., dn соответственно: " << std::endl;
        for (int i = 0; i <= n; i++)
        {
            std::cout << "Число d{" << i << "}=";
            mass[i] = getValue();
        }
    }
    else
    {
        std::cout << "Число n должно быть натуральным, повторите ввод." << std::endl;
        return false;
    }
    return true;
}

bool finit(std::ifstream& f, double mass[NM], double& a, double& h, double& b, int& n)
{
    f >> a;
    if (f.fail())
    {
        std::cout << "Ошибка ввода из файла числа a." << std::endl;
        return false;
    }
    f >> h;
    if (f.fail())
    {
        std::cout << "Ошибка ввода из файла числа h." << std::endl;
        return false;
    }
    f >> b;
    if (f.fail())
    {
        std::cout << "Ошибка ввода из файла числа b." << std::endl;
        return false;
    }
    f >> n;
    if (f.fail())
    {
        std::cout << "Ошибка ввода из файла числа n." << std::endl;
        return false;
    }
    if (checkValue_mass(n))
    {
        for (unsigned i = 0; i <= n; i++)
        {
            f >> mass[i];
            if (f.fail())
            {
                std::cout << "Ошибка ввода из файла числа d{"
                    << i << "}" << std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cout << "Число n должно быть натуральным, повторите ввод." << std::endl;
        return false;
    }
    return true;
}

void fsum(std::ostream& f, double mass[NM], double a, double h, double b, int n, double sum) {
    f << "Введенные вами числа a, h, b, n соответственно: " << a << " " << h << " " << b << " " << n << std::endl;
    f << "Введенные вами числа d0, d1, ..., dn соответственно:" << std::endl;
    for (int i = 0; i <= n;i++)
    {
        f << mass[i] << "\t";
    }
    f << std::endl;
    sum = mass[0];
    double pr;
    pr = 1;
    for (int i = 1; i <= n; i++)
    {
        pr = pr * (b - a - (i - 1) * h);
        sum = sum + mass[i] * pr;
    }

    f << "Значение, вычисленное по вашим данным:";
    f << sum << std::endl;
}

unsigned checkValue()
{
    while (true)
    {
        unsigned a;
        std::cin >> a;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Вы ввели не число. Повторите ввод:\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}

double getValue()
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

bool checkValue_mass(int n)
{
    return(n > 0 && n * 10 % 10 == 0) ? true : false;
}
