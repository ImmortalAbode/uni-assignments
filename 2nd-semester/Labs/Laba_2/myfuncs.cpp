#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

bool init(double mass[NM], double& a, int& n)
{
    std::cout << "������� �������������� ����� a: ";
    a = checkValue();
    std::cout << "������� ����������� ����� n: ";
    while (true)
    {
        if (getValue_mass(n))
        {
            std::cout << "������� ����� x1, x2, ..., xn �������������� �����, ��� x{1} <= x{2} <= ... <= x{n}: " << std::endl;
            for (int i = 0; i <= n - 1; i++)
            {
                std::cout << "����� x{" << i + 1 << "}=";
                mass[i] = checkValue();
                if (i > 0 && mass[i] < mass[i - 1])
                {
                    std::cout << "�������� ���� ����� x{" << i + 1 << "} < ����� x{" << i << "}, ��� �� ������������� ������� ������." << std::endl;
                    return false;
                };
            }
            return true;
        }
        else
        {
            std::cout << "����� n ������ ���� �����������, ��������� ����:" << std::endl;
        }
    }
}
bool finit(std::ifstream& f, double mass[NM], double& a, int& n, double& b)
{
    f >> a;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ����� a." << std::endl;
        return false;
    }
    f >> b;
    if (f.fail() || b <= 0 || b != int(b))
    {
        std::cout << "������ ����� �� ����� ����� n." << std::endl;
        return false;
    }
    else
        n = int(b);
    for (unsigned i = 0; i <= n - 1; i++)
    {
        f >> mass[i];
        if (f.fail())
        {
            std::cout << "������ ����� �� ����� ����� d{" << i << "}" << std::endl;
            return false;
        }
        if (i > 0 && mass[i] < mass[i - 1])
        {
            std::cout << "�������� �� ����� ����� x{" << i + 1 << "} < ����� x{" << i << "}, ��� �� ������������� ������� ������." << std::endl;
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
            std::cout << "������ �����. �� ����� �� �����. ��������� ����: \n";
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
            std::cout << "������ �����. �� ����� �� �����. ��������� ����: \n";
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
    f << "��������� ���� ����� a, n ��������������: " << a << " " << n << std::endl;
    f << "��������� ���� ����� x1, x2, ..., xn ��������������:" << std::endl;
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
    f << "���� ������� ������������������ y{1}, ..., y{n+1} �����, ��� y{1} <= y{2} <= ... <= y{n+1} :" << std::endl;
    f << mass[0] << " ";
    for (int i = 1;i <= n; i++)
    {
        f << "<= " << mass[i] << " ";
    }
    f << std::endl;
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
