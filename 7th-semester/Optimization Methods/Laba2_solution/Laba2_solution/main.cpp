#include <iostream>
#include <fstream>
#include "myfuncs.h"

int main() {
    //std::setlocale(LC_ALL, "RUS");
    std::system("chcp 1251 > nul");

    //Файлы для сохранения результатов.
    std::ofstream outResFile_regularSymplex("regularSymplex.txt");
    if (!outResFile_regularSymplex.is_open()) 
    {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }
    std::ofstream outResFile_deformablePolyhedron("deformablePolyhedron.txt");
    if (!outResFile_deformablePolyhedron.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }

    //Вывод в файлы индивидуального задания.
    outResFile_regularSymplex << "Формулировка задачи:\n"
        << "Минимизировать функцию F(X) = 4*x1^2 + x2^2 - 40 * x1 - 12 * x2 + 136, используя в качестве начального многогранник "
        << "с вершинами X^1=(8;9)^T, X^2=(10;11)^T, X^3=(8;11)^T."
        << std::endl;
    outResFile_deformablePolyhedron << "Формулировка задачи:\n"
        << "Минимизировать функцию F(X) = 4*x1^2 + x2^2 - 40 * x1 - 12 * x2 + 136, используя в качестве начального многогранник "
        << "с вершинами X^1=(8;9)^T, X^2=(10;11)^T, X^3=(8;11)^T."
        << std::endl;

    /*-------------------------------------------------------------
     | МЕТОД МИНИМИЗАЦИИ ФУНКЦИИ ПОИСКОМ ПО ПРАВИЛЬНОМУ СИМПЛЕКСУ |
     -------------------------------------------------------------*/
    outResFile_regularSymplex << "ПОИСК ПО ПРАВИЛЬНОМУ СИМПЛЕКСУ." << std::endl;

    //Вызовы с различными параметрами.
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-1, 1.0);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-2, 0.5);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-2, 0.5);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-3, 0.5);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-3, 1.0);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-3, 2.0);

    /*--------------------------------------------------------------------
     | МЕТОД МИНИМИЗАЦИИ ФУНКЦИИ ПОИСКОМ ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ |
     --------------------------------------------------------------------*/
    outResFile_deformablePolyhedron << "ПОИСК ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ." << std::endl;
    //Вызовы с различными параметрами.
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 1.5);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 1.75);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 2.0);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 2.5);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-3, 1, 0.5, 2);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-3, 1, 0.5, 2);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-1, 1, 0.6, 2);

    //Закрытие файлов.
    outResFile_regularSymplex.close();
    outResFile_deformablePolyhedron.close();
    return 0;
}