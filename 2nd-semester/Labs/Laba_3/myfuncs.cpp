#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

bool init(double*** massOut, unsigned& NMOut)
{
    std::cout << "Задайте размерность массива порядка n:";
    while (true)
    {
        if (getValue_mass(NMOut) && makeMass(massOut, NMOut))
        {
            std::cout << "Заполните построчно массив соответствующими элементами (числами): " << std::endl;
            std::cout << "Элемент массива:" << std::endl;
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
            std::cout << "Число n должно быть >= 2 и быть целым. Повторите ввод: " << std::endl;
        }
    }
}
bool finit(std::istream& f, double*** massOut, unsigned& NMOut, double& b)
{
    f >> b;
    if (f.fail() || b <= 0 || b != int(b))
    {
        std::cout << "Ошибка ввода из файла числа n." << std::endl;
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
                    std::cout << "Ошибка ввода из файла элемента [" << i << "][" << j << "]." << std::endl;
                    return false;
                }
            }
        }
    }
    else
    {
        std::cout << "Число n должно быть больше 2." << std::endl;
        return false;
    }
    return true;
}
void forder(std::ostream& f, double** mass, unsigned NM)
{
    f << "Введенные вами число n соответственно: " << NM << std::endl;
    f << "Введенные вами элементы квадратной матрицы соотвественно:" << std::endl;
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
    f << "Ваша искомая последовательность b[1], ..., b[n] из нулей и единиц, в которой b[i] = 1, тогда и только тогда, когда:" << std::endl;
    f << "a) элементы i - строки матрицы образуют возрастающую последовательность." << std::endl;
    for (unsigned i = 0;i < NM;i++)
    {
        f << order_a[i] << "\t";
    }
    f << std::endl << std::endl;
    f << "б) элементы i-строки матрицы образуют возрастающую или убывающую последовательность." << std::endl;
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
            std::cout << "Ошибка ввода. Вы ввели не число. Повторите ввод: \n";
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
            std::cout << "Ошибка ввода. Вы ввели не число. Повторите ввод: \n";
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
        std::cout << "Не удалось выделить память для массива!" << std::endl;
        return false;
    }
    else
    {
        for (unsigned i = 0; i < NM;i++)
        {
            *(*massOut + i) = new (std::nothrow) double[NM] {};
            if (!(*(*massOut + i)))
            {
                std::cout << "Не удалось выделить память для массива!" << std::endl;
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
            std::cout << "Ошибка ввода. Введите 0 или 1: \n";
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
