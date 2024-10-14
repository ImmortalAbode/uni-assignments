#ifndef STRUCTASSEMBLERLINE_H
#define STRUCTASSEMBLERLINE_H

#include <QString>

struct AssemblerInstruction
{
    std::optional<QString> label{};
    QString mnemonic{};
    QString operand1{};
    std::optional<QString> operand2{};
    //Конструктор по умолчанию.
    AssemblerInstruction() = default;
    //Конструктор с параметрами.
    AssemblerInstruction(const QString& lbl, const QString& mnem, const QString& op1, const QString& op2 = "")
        : label(lbl), mnemonic(mnem), operand1(op1), operand2(op2) {}
};

#endif // STRUCTASSEMBLERLINE_H
