#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

//Рассматриваемая функция.
double f(double Zn_vod) {
    double Zn_v{ 200 }, Zn_s_l{ 0.375 };
    return 4334.3 - 68193.5 * Zn_vod + 183.6 * Zn_s_l + 644657.2 * pow(Zn_vod, 2) - 134.2 * pow(Zn_s_l, 2) + 806.4 * log(Zn_vod) - 14.9 * log(Zn_s_l) - Zn_v;
}

//Функция для нахождения корня методом Больцано.
double Bolzano_method(double a, double b, double TOL, std::ofstream& outResFile) 
{
    if (f(a) * f(b) >= 0) 
    {
        std::cerr << "Функция не пересекает ось абсцисс!" << std::endl;
        return NAN;
    }

    double c{};  //середина отрезка
    int iter{};  //итерации

    outResFile << "Выполнение метода Больцано:\n";
    outResFile << std::setw(10) << "Итерация" << std::setw(20) << "a" << std::setw(20) << "b" << std::setw(20) << "c" << std::setw(20) << "f(c)" << std::endl;

    while ((b - a) / 2.0 > TOL) {
        c = (a + b) / 2.0;
        iter++;

        //Вывод в файл.
        outResFile << std::setw(10) << iter
            << std::setw(20) << a
            << std::setw(20) << b
            << std::setw(20) << c
            << std::setw(20) << f(c) << std::endl;

        if (f(a) * f(c) < 0) 
        {
            b = c;  //переходим к отрезку [a, c]
        }
        else if (f(c) * f(b) < 0)
        {
            a = c;  //переходим к отрезку [c, b]
        }
        else
            break;
    }
    iter++;
    c = (a + b) / 2.0;
    outResFile << std::setw(10) << iter
        << std::setw(20) << a
        << std::setw(20) << b
        << std::setw(20) << c
        << std::setw(20) << f(c) << std::endl;
    return c;
}

//Функция для нахождения корня методом секущих.
double Secant_method(double x0, double x1, double TOL, std::ofstream& outResFile) {
    double x2{}; //новая точка
    int iter{}; //итерации

    outResFile << "\nВыполнение метода секущих:\n";
    outResFile << std::setw(10) << "Итерация" << std::setw(20) << "x0" << std::setw(20) << "x1" << std::setw(20) << "x2" << std::setw(20) << "f(x2)" << std::endl;

    while (true) {
        double f_x0 = f(x0);
        double f_x1 = f(x1);

        //Проверка на деление на ноль.
        if (f_x1 - f_x0 == 0) {
            std::cerr << "Деление на ноль! Метод секущих не может продолжаться." << std::endl;
            return NAN;
        }

        // Формула метода секущих
        x2 = x1 - f_x1 * (x1 - x0) / (f_x1 - f_x0);
        iter++;

        //Вывод в файл.
        outResFile << std::setw(10) << iter
            << std::setw(20) << x0
            << std::setw(20) << x1
            << std::setw(20) << x2
            << std::setw(20) << f(x2) << std::endl;

        // Если достигли нужной точности, выходим
        if (std::fabs(x2 - x1) < TOL) {
            return x2;
        }

        // Переход к следующей итерации
        x0 = x1;
        x1 = x2;
    }
}

int main() {
    //std::setlocale(LC_ALL, "RUS");
    std::system("chcp 1251 > nul");

    //Начальные параметры.
    double a{ 0.04 }, b{ 0.06 }; //отрезок
    double TOL{ 1e-4 }; //точность

    //Файл для сохранения результатов.
    std::ofstream outResFile("result.txt");
    if (!outResFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }
    outResFile << std::fixed << std::setprecision(4);
    //Переменные для хранения результатов.
    double root_bolzano{}; //Метод Больцано (деления пополам)
    double root_secant{}; //Метод секущих

    //Выполнение метода Больцано.
    root_bolzano = Bolzano_method(a, b, TOL, outResFile);

    //Выполнение метода секущих.
    double x0 = 0.04;  //первое приближение для метода секущих
    double x1 = 0.06; //второе приближение для метода секущих
    root_secant = Secant_method(x0, x1, TOL, outResFile);

    //Запись результатов в файл.
    outResFile << std::endl;
    outResFile << "Метод Больцано:\n" << "Точность: " << TOL << "\n" << "Приближенное значение корня: " << root_bolzano << "\n" << "f(root) = " << f(root_bolzano) << "\n\n";

    outResFile << "Метод секущих:\n" << "Точность: " << TOL << "\n" << "Приближенное значение корня: " << root_secant << "\n" << "f(root) = " << f(root_secant) << "\n\n";

    outResFile.close();
    std::cout << "Результаты были записаны в файл result.txt." << std::endl;

    std::system("chcp 866 > nul");
    return 0;
}
