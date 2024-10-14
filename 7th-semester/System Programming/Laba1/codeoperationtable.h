#ifndef CODEOPERATIONTABLE_H
#define CODEOPERATIONTABLE_H

#include <vector>
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
public:
    CodeOperationTable(size_t size = 101);
    void insert(const QString& mnemonic, const QString& binary, const QString& size);
    bool find(const QString& mnemonic, CodeOperation& operation) const;
    void remove(const QString& mnemonic);
    void clear();
    const std::vector<CodeOperation>& getOpCodeTable() const;

private:
    std::vector<CodeOperation> opCode_table;
    size_t hash(const QString& key) const;
};

#endif // CODEOPERATIONTABLE_H
