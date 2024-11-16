#include <iostream>
#include <fstream>
#include "myfuncs.h"

int main() {
    //std::setlocale(LC_ALL, "RUS");
    std::system("chcp 1251 > nul");

    //����� ��� ���������� �����������.
    std::ofstream outResFile_regularSymplex("regularSymplex.txt");
    if (!outResFile_regularSymplex.is_open()) 
    {
        std::cerr << "�� ������� ������� ���� ��� ������!" << std::endl;
        return 1;
    }
    std::ofstream outResFile_deformablePolyhedron("deformablePolyhedron.txt");
    if (!outResFile_deformablePolyhedron.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������!" << std::endl;
        return 1;
    }

    //����� � ����� ��������������� �������.
    outResFile_regularSymplex << "������������ ������:\n"
        << "�������������� ������� F(X) = 4*x1^2 + x2^2 - 40 * x1 - 12 * x2 + 136, ��������� � �������� ���������� ������������ "
        << "� ��������� X^1=(8;9)^T, X^2=(10;11)^T, X^3=(8;11)^T."
        << std::endl;
    outResFile_deformablePolyhedron << "������������ ������:\n"
        << "�������������� ������� F(X) = 4*x1^2 + x2^2 - 40 * x1 - 12 * x2 + 136, ��������� � �������� ���������� ������������ "
        << "� ��������� X^1=(8;9)^T, X^2=(10;11)^T, X^3=(8;11)^T."
        << std::endl;

    /*-------------------------------------------------------------
     | ����� ����������� ������� ������� �� ����������� ��������� |
     -------------------------------------------------------------*/
    outResFile_regularSymplex << "����� �� ����������� ���������." << std::endl;

    //������ � ���������� �����������.
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-1, 1.0);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-2, 0.5);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-2, 0.5);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-3, 0.5);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-3, 1.0);
    PerformCorrectSymplex(outResFile_regularSymplex, 1e-3, 2.0);

    /*--------------------------------------------------------------------
     | ����� ����������� ������� ������� �� �������������� ������������� |
     --------------------------------------------------------------------*/
    outResFile_deformablePolyhedron << "����� �� �������������� �������������." << std::endl;
    //������ � ���������� �����������.
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 1.5);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 1.75);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 2.0);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-2, 1, 0.4, 2.5);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-3, 1, 0.5, 2);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-3, 1, 0.5, 2);
    PerformDeformablePolyhedron(outResFile_deformablePolyhedron, 1e-1, 1, 0.6, 2);

    //�������� ������.
    outResFile_regularSymplex.close();
    outResFile_deformablePolyhedron.close();
    return 0;
}