#ifndef CHECKS_H
#define CHECKS_H

#include "codeoperationtable.h"

#include <QTextEdit>
#include <QTableWidget>
#include <QString>
#include <QChar>

class Checks
{
private:
    bool CheckLengthSymbolicName(const QString& symbolic_name);
    bool CheckCharsSymbolicName(const QString& symbolic_name);
    bool CheckIncorrectName(const QString& name);
    bool CheckCharsMCOP(const QString& mnemonic_code);

public:
    Checks() = default;
    bool CorrectTableCodeOperation(const CodeOperationTable& opCodeTable, QTextEdit* fpe_text);
    QString CheckRegister(const QString& reg);
    bool CheckAmountMemoryForAddress(const QString &amountMemory);
    bool CheckAddressCounterAvailable(QTextEdit* fpe_text, const int& row, const int &address_counter);
    bool CheckRowSourceCode(QTextEdit* textEdit_FPE, const int& row, QString& prog_name, const QString& label, const QString& mnemonic_code);
    QString CheckProgramName(const QString& prog_name);
    QString CheckProgramDownloadAddress(const QString& download_address);
    QString CheckOtherOperandPart(const QString &second_operand, const QString& mnemonic_code, const int& row);
    QString CheckDirective(const QString& mnemonic_code);
    bool CheckCorrectAmountMemoryForCodeOperation(const QString& amount_memory);
    bool CheckCorrectAmountMemoryForDecNumber(const QString &amount_memory);
    bool CheckAllocAmountMemoryForByte(const QString& alloc_memory);
    bool CheckCorrectAmountMemoryForHexNumber(const QString& amount_memory);
    bool CheckCorrectAmountMemoryForUnicodeString(const QString& amount_memory);
    bool CheckAllocAmountMemoryForWord(const QString& alloc_memory);
    bool CheckAllocAmountMemoryForRES(const QString& amount_memory);
    int GetDecOpcode(QString const& command_binary_code, const int& type_addressing);

};

#endif // CHECKS_H
