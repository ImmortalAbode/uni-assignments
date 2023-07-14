#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

bool init(double mass[NM], double& a, double& h, double& b, int& n)
{
    std::cout << "������� �������������� ����� a: ";
    a = getValue();
    std::cout << "������� �������������� ����� h: ";
    h = getValue();
    std::cout << "������� �������������� ����� b: ";
    b = getValue();
    std::cout << "������� ����������� ����� n: ";
    n = checkValue();
    if (checkValue_mass(n))
    {
        std::cout << "������� ����� d0, d1, ..., dn ��������������: " << std::endl;
        for (int i = 0; i <= n; i++)
        {
            std::cout << "����� d{" << i << "}=";
            mass[i] = getValue();
        }
    }
    else
    {
        std::cout << "����� n ������ ���� �����������, ��������� ����." << std::endl;
        return false;
    }
    return true;
}

bool finit(std::ifstream& f, double mass[NM], double& a, double& h, double& b, int& n)
{
    f >> a;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ����� a." << std::endl;
        return false;
    }
    f >> h;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ����� h." << std::endl;
        return false;
    }
    f >> b;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ����� b." << std::endl;
        return false;
    }
    f >> n;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ����� n." << std::endl;
        return false;
    }
    if (checkValue_mass(n))
    {
        for (unsigned i = 0; i <= n; i++)
        {
            f >> mass[i];
            if (f.fail())
            {
                std::cout << "������ ����� �� ����� ����� d{"
                    << i << "}" << std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cout << "����� n ������ ���� �����������, ��������� ����." << std::endl;
        return false;
    }
    return true;
}

void fsum(std::ostream& f, double mass[NM], double a, double h, double b, int n, double sum) {
    f << "��������� ���� ����� a, h, b, n ��������������: " << a << " " << h << " " << b << " " << n << std::endl;
    f << "��������� ���� ����� d0, d1, ..., dn ��������������:" << std::endl;
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

    f << "��������, ����������� �� ����� ������:";
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
            std::cout << "������ �����. �� ����� �� �����. ��������� ����:\n";
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
            std::cout << "������ �����. �� ����� �� �����. ��������� ����: \n";
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
    std::cout << "����������? (0 - ���, 1 - ��): ";
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
            std::cout << "������ �����. ������� 0 ��� 1: \n";
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
            std::cout << "������ �����. ������� 0 ��� 1: \n";
        }
    }
}

bool checkValue_mass(int n)
{
    return(n > 0 && n * 10 % 10 == 0) ? true : false;
}
