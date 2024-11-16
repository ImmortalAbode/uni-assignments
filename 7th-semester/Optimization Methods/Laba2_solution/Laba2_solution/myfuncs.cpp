#include "myfuncs.h"
#include "constants.h"
#include <math.h>
#include <iomanip>
#include <string>
#include <iostream>

/*--------------------------------
 |ПОИСК ПО ПРАВИЛЬНОМУ СИМПЛЕКСУ |
 --------------------------------*/
//Запись в файл дополнительных данных строки.
static void PrintTableCurIter(std::ofstream& output_file, const int& iter, const double& t)
{
    output_file << std::setw(10) << iter
        << std::setw(65) << "t = " << t
        << std::endl;
}
//Запись в файл результатов.
static void PrintResults(std::ofstream& output_file, const Symplex_coords mass_points[], const double& t) 
{
    output_file << std::endl << "Конечные значения:" << std::endl;
    for (int i{}; i < n + 1; ++i)
        PrintTableRow(output_file, "X^" + std::to_string(i), mass_points[i]);
    Symplex_coords x_middle = Symplex_coords((mass_points[0].x1 + mass_points[1].x1 + mass_points[2].x1) / 3,
        (mass_points[0].x2 + mass_points[1].x2 + mass_points[2].x2) / 3, NAN);
    x_middle.f = Function(x_middle);
    output_file << std::setw(10) << ""
        << std::setw(10) << "Xср."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << x_middle.f
        << std::setw(10) << "t = " << t
        << std::endl;
}
//Сортировка вершин в порядке F(X0)<=F(X1)<=...<=F(XN).
void SortPoints(Symplex_coords current_points[], const int& size)
{
    //Пузырьковая сортировка.
    for (int i{}; i < size; i++)
    {
        for (int j{ i + 1 }; j < size; j++)
        {
            if (current_points[j].f <= current_points[i].f)
            {
                Symplex_coords temp = current_points[i];
                current_points[i] = current_points[j];
                current_points[j] = temp;
            }
        }
    }
}
//Поиск центра тяжести XC вершин X0,X1,...,X(N-1).
static Symplex_coords Сentroid_n(const Symplex_coords mass_points[])
{
    Symplex_coords XC{};
    for (int j{}; j < n; j++)
    {
        XC.x1 += mass_points[j].x1;
        XC.x2 += mass_points[j].x2;
    }
    XC.x1 *= 1.0f / n;
    XC.x2 *= 1.0f / n;
    return XC;
}
//Поиск центра тяжести Xc вершин X0,X1,...,X(N-2),XN.
static Symplex_coords Сentroid_n_minus_1(const Symplex_coords mass_points[])
{
    Symplex_coords XC{};
    for (int i{}; i <= n; ++i) {
        if (i != n - 1) 
        {
            XC.x1 += mass_points[i].x1;
            XC.x2 += mass_points[i].x2;
        }
    }
    XC.x1 *= 1.0f / n;
    XC.x2 *= 1.0f / n;
    return XC;
}
//Функция для отражения точки. Для шага 5.
Symplex_coords Reflect(const Symplex_coords& worst, const Symplex_coords& XC)
{
    return { 2 * XC.x1 - worst.x1, 2 * XC.x2 - worst.x2, NAN };
}
//Главная функция поиска по правильному симплексу.
void SearchByCorrectSymplex(std::ofstream& file, const double& epsilon, double& t) 
{
    /*-------------------
     | Алгоритм решения |
     -------------------*/
    //Шаг 0: Построение начального симплекса.
    Symplex_coords X0{}, X1{}, X2{};
    X0.x1 = 5; X0.x2 = 6; //Базовая точка X^0.
    double d1{ t / (n * sqrt(2)) * (sqrt(n + 1) + n - 1) },
        d2{ t / (n * sqrt(2)) * (sqrt(n + 1) - 1) };

    X1.x1 = X0.x1 + d1; X1.x2 = X0.x2 + d2;
    X2.x1 = X0.x1 + d2; X2.x2 = X0.x2 + d1;

    //Для хранения точек текущего симплекса.
    Symplex_coords mass_points[n + 1]{ X0, X1, X2 };
    
    //Для учета итераций.
    int iter{}; 
    //Запись заголовков
    PrintTableHeader(file);

    while (true) 
    {
        //Шаг 1: Вычисление значений функции.
        for (int i{}; i < n + 1; i++)
            mass_points[i].f = Function(mass_points[i]);

        //Шаг 2: Сортировка по значениям функции.
        SortPoints(mass_points, n + 1);
        //Вывод строки с номером итерации и t.
        PrintTableCurIter(file, iter, t);
        //Вывод текущих вершин.
        for (int i{}; i < n + 1; ++i)
            PrintTableRow(file, "X^" + std::to_string(i), mass_points[i]);

        // Шаг 3: Проверка условия достижения точности.
        double sum_achieving{};
        for (int j{ 1 }; j <= n; j++)
            sum_achieving += pow(mass_points[j].f - mass_points[0].f, 2);
        double cur_achieving{ 1.0f / n * sum_achieving };
        if (cur_achieving < epsilon)
        {
            //Шаг 7: Завершение вычислений.
            std::cout << "Точность поиска по правильному симплексу достигнута. Результаты записаны в файл */outResFile_regularSymplex.txt." << std::endl;
            break;
        }

        // Шаг 4.
        Symplex_coords XC = Сentroid_n(mass_points);
        Symplex_coords XR = Reflect(mass_points[n], XC);
        XR.f = Function(XR);

        if (XR.f < mass_points[n].f)
        {
            mass_points[n] = XR;
            iter++;
            continue; // переход к шагу 2.
        }

        // Шаг 5.
        XC = Сentroid_n_minus_1(mass_points);
        XR = Reflect(mass_points[n - 1], XC);
        XR.f = Function(XR);

        if (XR.f < mass_points[n - 1].f)
        {
            mass_points[n] = XR;
            iter++;
            continue; // переход к шагу 2.
        }

        // Шаг 6. Сжатие симплекса.
        t = t / 2;
        for (int i{ 1 }; i < n + 1; ++i) 
        {
            mass_points[i].x1 = (mass_points[i].x1 + mass_points[0].x1) / 2;
            mass_points[i].x2 = (mass_points[i].x2 + mass_points[0].x2) / 2;
        }

        iter++;
    }

    // Шаг 7.
    PrintResults(file, mass_points, t);
}

/*---------------------------------------
 |ПОИСК ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ |
 ---------------------------------------*/
 //Запись в файл дополнительных данных строки.
static void PrintTableCurIter(std::ofstream& output_file, const int& iter) 
{
    output_file << std::setw(10) << iter
        << std::endl;
}
//Запиись в файл текущих вершин.
static void PrintCurrentPoints(std::ofstream& output_file, const Symplex_coords mass_points[]) 
{
    for (int i{}; i < n + 1; ++i) 
        PrintTableRow(output_file, "X^" + std::to_string(i + 1), mass_points[i]);
}
//Запись в файл результатов.
static void PrintResults(std::ofstream& output_file, const Symplex_coords mass_points[])
{
    output_file << std::endl << "Конечные значения:" << std::endl;
    for (int i{}; i < n + 1; ++i)
        PrintTableRow(output_file, "X^" + std::to_string(i + 1), mass_points[i]);
    Symplex_coords x_middle = Symplex_coords((mass_points[0].x1 + mass_points[1].x1 + mass_points[2].x1) / 3,
        (mass_points[0].x2 + mass_points[1].x2 + mass_points[2].x2) / 3, NAN);
    x_middle.f = Function(x_middle);
    output_file << std::setw(10) << ""
        << std::setw(10) << "Xср."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << x_middle.f
        << std::endl;
}
// Проверка критерия окончания поиска.
static bool AchievingPrecision(const Symplex_coords mass_points[], const Symplex_coords& X_n_plus_2, const double& epsilon)
{
    double sum_achieving{};
    for (int j{}; j < n + 1; ++j)
        sum_achieving += pow(mass_points[j].f - X_n_plus_2.f, 2);
    long double accuracy = sqrt(sum_achieving / (n + 1));
    if (accuracy <= epsilon)
    {
        std::cout << "Точность поиска по деформируемому многограннику достигнута. Результаты записаны в файл */deformablePolyhedron.txt." << std::endl;
        return true;
    }
    return false;
}
//Поиск номера вершины Xh, значение функции в которой максимальное.
static int MaxFValue(const Symplex_coords mass_points[])
{
    int h{};
    for (int i{}; i < n + 1; ++i)
        if (mass_points[i].f > mass_points[h].f)
            h = i;
    return h;
}
//Поиск номера вершины XL, значение функции в которой минимальное.
static int MinFValue(const Symplex_coords mass_points[])
{
    int L{};
    for (int i{}; i < n + 1; ++i)
        if (mass_points[i].f < mass_points[L].f)
            L = i;
    return L;
}
//Центр тяжести X^(n+2) всех вершин, исключая Xh.
static Symplex_coords Centroid_h(const Symplex_coords mass_points[], const int& h)
{
    Symplex_coords n_plus_2{};
    for (int i{}; i < n + 1; ++i) 
    {
        if (i != h) 
        {
            n_plus_2.x1 += mass_points[i].x1;
            n_plus_2.x2 += mass_points[i].x2;
        }
    }
    n_plus_2.x1 *= 1.0f / n;
    n_plus_2.x2 *= 1.0f / n;
    return n_plus_2;
}
//Отражение вершины Xh через центр тяжести X^(n+2).
static Symplex_coords Reflect(const Symplex_coords& X_n_plus_2, const Symplex_coords& Xh, const double& alpha) {
    Symplex_coords X_n_plus_3{};
    X_n_plus_3.x1 = X_n_plus_2.x1 + alpha * (X_n_plus_2.x1 - Xh.x1);
    X_n_plus_3.x2 = X_n_plus_2.x2 + alpha * (X_n_plus_2.x2 - Xh.x2);
    return X_n_plus_3;
}
// Растяжение вектора X(n+3)-X(n+2).
static Symplex_coords Stretch(const Symplex_coords& X_n_plus_3, const Symplex_coords& X_n_plus_2, const double& gamma) 
{
    Symplex_coords X_n_plus_4{};
    X_n_plus_4.x1 = X_n_plus_2.x1 + gamma * (X_n_plus_3.x1 - X_n_plus_2.x1);
    X_n_plus_4.x2 = X_n_plus_2.x2 + gamma * (X_n_plus_3.x2 - X_n_plus_2.x2);
    return X_n_plus_4;
}
// Сжатие вектора Xh-X(n+2).
static Symplex_coords Contract(const Symplex_coords& Xh, const Symplex_coords& X_n_plus_2, const double& beta) 
{
    Symplex_coords X_n_plus_5{};
    X_n_plus_5.x1 = X_n_plus_2.x1 + beta * (Xh.x1 - X_n_plus_2.x1);
    X_n_plus_5.x2 = X_n_plus_2.x2 + beta * (Xh.x2 - X_n_plus_2.x2);
    return X_n_plus_5;
}
// Редукция векторов Xj-XL в 2 раза.
static void Reduce(Symplex_coords mass_points[], const Symplex_coords& XL)
{
    for (int j{}; j < n + 1; ++j) 
    {
        mass_points[j].x1 = XL.x1 + (mass_points[j].x1 - XL.x1) / 2;
        mass_points[j].x2 = XL.x2 + (mass_points[j].x2 - XL.x2) / 2;
    }
}
//Ситуация, когда многогранник вырождается и дальнейшая минимизация просто бессмысленна.
bool Degenerate(const Symplex_coords mass_points[])
{
    const double value{ mass_points[0].f };
    for (int i{ 1 }; i < n + 1; ++i)
        if (mass_points[i].f != value)
            return false;
    return true;
}
//Главная функция поиска по деформируемому многограннику.
void SearchByDeformablePolyhedron(std::ofstream& file, const double& epsilon, const double& alpha, const double& beta, const double& gamma)
{
    /*-------------------
     | Алгоритм решения |
     -------------------*/
    //Начальный многогранник.
    Symplex_coords X1{ 8, 9, NAN },
        X2{ 10, 11, NAN },
        X3{ 8, 11, NAN };
    Symplex_coords mass_points[3]{ X1, X2, X3 };
    //Вычисление значений функции в вершинах X1, X2, X3.
    for (int i{}; i < n + 1; i++)
        mass_points[i].f = Function(mass_points[i]);

    //Для процедуры отсыкания вершины, в которой F(X) имеет лучшее значение.
    Symplex_coords X_n_plus_2{}; //Центр тяжести X^(n+2).
    Symplex_coords X_n_plus_3{}; //Отражение - X^(n+3).
    Symplex_coords X_n_plus_4{}; //Растяжение - X^(n+4).
    Symplex_coords X_n_plus_5{}; //Сжатие - X^(n+5).

    int iter{}; // Для учета числа итераций.

    //Вывод в файл исходных данных.
    PrintTableHeader(file); //Вывод заголовка таблицы в файл.
    PrintTableCurIter(file, iter); // Вывод строки с номером итерации.
    PrintCurrentPoints(file, mass_points); // Вывод текущих вершин.

    while (true)
    {
        int h = MaxFValue(mass_points); //Номер вершины, значение функции в которой максимально, - Xh (худшая).
        int L = MinFValue(mass_points); //Номер вершины, значение функции в которой минимально, - XL (лучшая).
        //Центр тяжести.
        X_n_plus_2 = Centroid_h(mass_points, h);
        X_n_plus_2.f = Function(X_n_plus_2);

        //Проверка критерия окончания поиска.
        if (AchievingPrecision(mass_points, X_n_plus_2, epsilon))
            break;
        //Вывод строки с номером итерации.
        PrintTableCurIter(file, iter + 1);

        //Отражение.
        X_n_plus_3 = Reflect(X_n_plus_2, mass_points[h], alpha);
        X_n_plus_3.f = Function(X_n_plus_3);

        //Если отраженная вершина лучше не только худшей, то имеет смысл выполнить растяжение, иначе - сжатие.
        //Проверка на сжатие.
        //Отраженная вершина хуже остальных вершин, но лучше худшей?
        bool contract{ true };
        for (int j{}; j < n + 1; ++j)
        {
            if (j != h)
            {
                if (!(X_n_plus_3.f > mass_points[j].f) || X_n_plus_3.f > mass_points[h].f)
                {
                    contract = false;
                    break;
                }
            }
        }
        //Проверка на рястяжение.
        //Отраженная вершина не только лучше худшей?
        if (X_n_plus_3.f < mass_points[h].f && !contract)
        {
            //Растяжение.
            X_n_plus_4 = Stretch(X_n_plus_3, X_n_plus_2, gamma);
            X_n_plus_4.f = Function(X_n_plus_4);
            //Растянутая отраженная вершина лучше лучшей и лучше отраженной?
            if (X_n_plus_4.f < mass_points[L].f && X_n_plus_4.f < X_n_plus_3.f)
            {
                //Если да, то худшая вершина = растянутой отраженной вершине.
                file << "После шага " << iter << " выполнено отражение->растяжение." << std::endl;
                mass_points[h] = X_n_plus_4; // Xh = X^(n+4).
                PrintCurrentPoints(file, mass_points);
                iter++;
                continue;
            }
            else
            {
                //Иначе худшая вершина = отраженной.
                file << "После шага " << iter << " выполнено отражение." << std::endl;
                mass_points[h] = X_n_plus_3; // Xh = X^(n+3).
                PrintCurrentPoints(file, mass_points);
                iter++;
                continue;
            }
        }

        //Сжатие.
        //Если имеет смысл выполнить сжатие, а отражение и растяжение не дает лучших результатов.
        if (contract)
        {
            file << "После шага " << iter << " выполнено сжатие." << std::endl;
            X_n_plus_5 = Contract(mass_points[h], X_n_plus_2, beta);
            X_n_plus_5.f = Function(X_n_plus_5);
            mass_points[h] = X_n_plus_5; // Xh = X^(n+5).
            PrintCurrentPoints(file, mass_points);
            iter++;
            continue;
        }
        //Редукция.
        //Отраженная вершина еще хуже, чем худшая => редукция.
        if (X_n_plus_3.f > mass_points[h].f)
        {
            file << "После шага " << iter << " выполнена редукция." << std::endl;
            Reduce(mass_points, mass_points[L]);
            for (int i{}; i < n + 1; ++i)
                mass_points[i].f = Function(mass_points[i]);
            PrintCurrentPoints(file, mass_points);
            iter++;
            continue;
        }

        //Ситуация, когда многогранник вырождается.
        if (Degenerate(mass_points))
        {
            file << "После шага " << iter << " деформируемый многогранник выродился. Минимизация была досрочно завершена." << std::endl;
            break;
        }
    }
    PrintResults(file, mass_points);
}

/*----------------
 | ОБЩИЕ ФУНКЦИИ |
 ----------------*/
 //Функция для выполнения поиска по правильному симплексу с заданными параметрами.
void PerformCorrectSymplex(std::ofstream& results_file, const double& epsilon, double t)
{
    for (int i{}; i <= 99; ++i)
        results_file << "-";
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "t = " << t << "." << std::endl;
    SearchByCorrectSymplex(results_file, epsilon, t);
}
//Функция для выполнения поиска по деформируемому многограннику.
void PerformDeformablePolyhedron(std::ofstream& results_file, const double& epsilon, const double& alpha, const double& beta, const double& gamma) {
    for (int i{}; i < 99; ++i)
        results_file << "-";
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "alpha = " << alpha << ", beta = " << beta << ", gamma = " << gamma << "." << std::endl;
    SearchByDeformablePolyhedron(results_file, epsilon, alpha, beta, gamma);
}
//Запись в файл заголовка таблицы.
void PrintTableHeader(std::ofstream& output_file) {
    output_file << std::setw(10) << "Итерация"
        << std::setw(10) << "Точка"
        << std::setw(15) << "x1"
        << std::setw(15) << "x2"
        << std::setw(15) << "F(X)"
        << std::endl;
}
//Запись в файл строки таблицы.
static void PrintTableRow(std::ofstream& output_file, const std::string& pointName, const Symplex_coords& point)
{
    output_file << std::setw(20) << pointName
        << std::setw(15) << point.x1
        << std::setw(15) << point.x2
        << std::setw(15) << point.f
        << std::endl;
}
//Вычисление значения заданной функции F(X)=4*x1^2 + x2^2 - 40*x1 - 12*x2 + 136.
double Function(const Symplex_coords& point)
{
    return (4 * pow(point.x1, 2) + pow(point.x2, 2) - 40 * point.x1 - 12 * point.x2 + 136);
}