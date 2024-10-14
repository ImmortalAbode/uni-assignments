#ifndef STRUCTSUPPORTTABLE_H
#define STRUCTSUPPORTTABLE_H

#include <QString>

struct SupportTable
{
    QString machine_code{};
    QString operation_code{};
    QString operand1{};
    QString operand2{};
    //Конструктор по умолчанию.
    SupportTable() = default;
    //Конструктор с параметрами.
    SupportTable(const QString& m_code, const QString& op_code, const QString& op1, const QString& op2 = "")
        : machine_code(m_code), operation_code(op_code), operand1(op1), operand2(op2) {}
};

#endif // STRUCTSUPPORTTABLE_H
