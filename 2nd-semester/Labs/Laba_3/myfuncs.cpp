#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

bool init(double*** massOut, unsigned& NMOut)
{
    std::cout << "������� ����������� ������� ������� n:";
    while (true)
    {
        if (getValue_mass(NMOut) && makeMass(massOut, NMOut))
        {
            std::cout << "��������� ��������� ������ ���������������� ���������� (�������): " << std::endl;
            std::cout << "������� �������:" << std::endl;
            for (unsigned i = 0; i < NMOut;i++)
            {
                for (unsigned j = 0;j < NMOut;j++)
                {
                    std::cout << "[" << i << "][" << j << "]=";
                    *(*((*massOut) + i) + j) = getValue();
                }
            }
            return true;
        }
        else
        {
            std::cout << "����� n ������ ���� >= 2 � ���� �����. ��������� ����: " << std::endl;
        }
    }
}
bool finit(std::istream& f, double*** massOut, unsigned& NMOut, double& b)
{
    f >> b;
    if (f.fail() || b <= 0 || b != int(b))
    {
        std::cout << "������ ����� �� ����� ����� n." << std::endl;
        return false;
    }
    else
        NMOut = int(b);
    if (makeMass(massOut, NMOut) && NMOut >= 2)
    {
        for (unsigned i = 0; i < NMOut; i++)
        {
            for (unsigned j = 0; j < NMOut; j++)
            {
                f >> *(*((*massOut) + i) + j);
                if (f.fail())
                {
                    std::cout << "������ ����� �� ����� �������� [" << i << "][" << j << "]." << std::endl;
                    return false;
                }
            }
        }
    }
    else
    {
        std::cout << "����� n ������ ���� ������ 2." << std::endl;
        return false;
    }
    return true;
}
void forder(std::ostream& f, double** mass, unsigned NM)
{
    f << "��������� ���� ����� n ��������������: " << NM << std::endl;
    f << "��������� ���� �������� ���������� ������� �������������:" << std::endl;
    for (unsigned i = 0; i < NM;i++)
    {
        for (unsigned j = 0;j < NM;j++)
        {
            f << mass[i][j] << "\t";
        }
        f << std::endl << std::endl;
    }
    double* order_a = new double[NM];
    double* order_b = new double[NM];
    unsigned count_a{}, count_b{};
    for (unsigned i = 0; i < NM; i++)
    {
        for (unsigned j = 0; j < NM - 1; j++)
        {
            if (mass[i][j] < mass[i][j + 1])
            {
                count_a += 1;
            }
            else if (mass[i][j] > mass[i][j + 1])
            {
                count_b += 1;
            }
        }
        if (count_a == NM - 1) order_a[i] = 1;
        else order_a[i] = 0;
        if (count_b == NM - 1 || count_a == NM - 1) order_b[i] = 1;
        else order_b[i] = 0;
        count_a = 0;
        count_b = 0;
    }
    f << "���� ������� ������������������ b[1], ..., b[n] �� ����� � ������, � ������� b[i] = 1, ����� � ������ �����, �����:" << std::endl;
    f << "a) �������� i - ������ ������� �������� ������������ ������������������." << std::endl;
    for (unsigned i = 0;i < NM;i++)
    {
        f << order_a[i] << "\t";
    }
    f << std::endl << std::endl;
    f << "�) �������� i-������ ������� �������� ������������ ��� ��������� ������������������." << std::endl;
    for (unsigned i = 0;i < NM;i++)
    {
        f << order_b[i] << "\t";
    }
    f << std::endl << std::endl;
    for (unsigned i = 0;i < NM;i++) delete[] * (mass + i);
    delete[] mass;
    delete[] order_a;
    delete[] order_b;
}
double getValue_mass(unsigned& NMOut)
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
            if (a != int(a) || a < 2)
                return false;
            else
            {
                NMOut = static_cast<unsigned>(a);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;
            }
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
bool makeMass(double*** massOut, unsigned NM)
{
    *massOut = new (std::nothrow) double* [NM] {};
    if (!(*massOut))
    {
        std::cout << "�� ������� �������� ������ ��� �������!" << std::endl;
        return false;
    }
    else
    {
        for (unsigned i = 0; i < NM;i++)
        {
            *(*massOut + i) = new (std::nothrow) double[NM] {};
            if (!(*(*massOut + i)))
            {
                std::cout << "�� ������� �������� ������ ��� �������!" << std::endl;
            }
        }
    }
    return true;
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
