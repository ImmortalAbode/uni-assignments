#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

//��������������� �������.
double f(double Zn_vod) {
    double Zn_v{ 200 }, Zn_s_l{ 0.375 };
    return 4334.3 - 68193.5 * Zn_vod + 183.6 * Zn_s_l + 644657.2 * pow(Zn_vod, 2) - 134.2 * pow(Zn_s_l, 2) + 806.4 * log(Zn_vod) - 14.9 * log(Zn_s_l) - Zn_v;
}

//������� ��� ���������� ����� ������� ��������.
double Bolzano_method(double a, double b, double TOL, std::ofstream& outResFile) 
{
    if (f(a) * f(b) >= 0) 
    {
        std::cerr << "������� �� ���������� ��� �������!" << std::endl;
        return NAN;
    }

    double c{};  //�������� �������
    int iter{};  //��������

    outResFile << "���������� ������ ��������:\n";
    outResFile << std::setw(10) << "��������" << std::setw(20) << "a" << std::setw(20) << "b" << std::setw(20) << "c" << std::setw(20) << "f(c)" << std::endl;

    while ((b - a) / 2.0 > TOL) {
        c = (a + b) / 2.0;
        iter++;

        //����� � ����.
        outResFile << std::setw(10) << iter
            << std::setw(20) << a
            << std::setw(20) << b
            << std::setw(20) << c
            << std::setw(20) << f(c) << std::endl;

        if (f(a) * f(c) < 0) 
        {
            b = c;  //��������� � ������� [a, c]
        }
        else if (f(c) * f(b) < 0)
        {
            a = c;  //��������� � ������� [c, b]
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

//������� ��� ���������� ����� ������� �������.
double Secant_method(double x0, double x1, double TOL, std::ofstream& outResFile) {
    double x2{}; //����� �����
    int iter{}; //��������

    outResFile << "\n���������� ������ �������:\n";
    outResFile << std::setw(10) << "��������" << std::setw(20) << "x0" << std::setw(20) << "x1" << std::setw(20) << "x2" << std::setw(20) << "f(x2)" << std::endl;

    while (true) {
        double f_x0 = f(x0);
        double f_x1 = f(x1);

        //�������� �� ������� �� ����.
        if (f_x1 - f_x0 == 0) {
            std::cerr << "������� �� ����! ����� ������� �� ����� ������������." << std::endl;
            return NAN;
        }

        // ������� ������ �������
        x2 = x1 - f_x1 * (x1 - x0) / (f_x1 - f_x0);
        iter++;

        //����� � ����.
        outResFile << std::setw(10) << iter
            << std::setw(20) << x0
            << std::setw(20) << x1
            << std::setw(20) << x2
            << std::setw(20) << f(x2) << std::endl;

        // ���� �������� ������ ��������, �������
        if (std::fabs(x2 - x1) < TOL) {
            return x2;
        }

        // ������� � ��������� ��������
        x0 = x1;
        x1 = x2;
    }
}

int main() {
    //std::setlocale(LC_ALL, "RUS");
    std::system("chcp 1251 > nul");

    //��������� ���������.
    double a{ 0.04 }, b{ 0.06 }; //�������
    double TOL{ 1e-4 }; //��������

    //���� ��� ���������� �����������.
    std::ofstream outResFile("result.txt");
    if (!outResFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������!" << std::endl;
        return 1;
    }
    outResFile << std::fixed << std::setprecision(4);
    //���������� ��� �������� �����������.
    double root_bolzano{}; //����� �������� (������� �������)
    double root_secant{}; //����� �������

    //���������� ������ ��������.
    root_bolzano = Bolzano_method(a, b, TOL, outResFile);

    //���������� ������ �������.
    double x0 = 0.04;  //������ ����������� ��� ������ �������
    double x1 = 0.06; //������ ����������� ��� ������ �������
    root_secant = Secant_method(x0, x1, TOL, outResFile);

    //������ ����������� � ����.
    outResFile << std::endl;
    outResFile << "����� ��������:\n" << "��������: " << TOL << "\n" << "������������ �������� �����: " << root_bolzano << "\n" << "f(root) = " << f(root_bolzano) << "\n\n";

    outResFile << "����� �������:\n" << "��������: " << TOL << "\n" << "������������ �������� �����: " << root_secant << "\n" << "f(root) = " << f(root_secant) << "\n\n";

    outResFile.close();
    std::cout << "���������� ���� �������� � ���� result.txt." << std::endl;

    std::system("chcp 866 > nul");
    return 0;
}
