#ifndef CODEOPERATIONTABLE_H
#define CODEOPERATIONTABLE_H

#include <QString>

struct CodeOperation
{
    QString mnemonic_code{}; //МКОП
    QString binary_code{};   //Двоичный код
    QString size{};          //Длина команды
    CodeOperation() = default;
    CodeOperation(const QString& mnem_code, const QString& bin_code, const QString& s)
        : mnemonic_code(mnem_code), binary_code(bin_code), size(s) {}
};

class CodeOperationTable
{
private:
    static const size_t TABLE_SIZE{64};
    CodeOperation opCode_table[TABLE_SIZE];

public:
    CodeOperationTable() = default;
    void insert(const QString& mnemonic, const QString& binary, const QString& size);
    bool find(const QString& mnemonic, CodeOperation& operation) const;
    void remove(const QString& mnemonic);
    void clear();
    size_t getOpCodeTableSize() const;
    const CodeOperation* getOpCodeTable() const;

private:
    size_t hash(const QString& key) const;
};

#endif // CODEOPERATIONTABLE_H
