#include "codeoperationtable.h"

CodeOperationTable::CodeOperationTable(size_t size)
    : opCode_table(size)
{
}

size_t CodeOperationTable::hash(const QString& key) const
{
    size_t hash_value = 0;
    for (QChar c : key) {
        hash_value = (hash_value * 31 + c.unicode()) % opCode_table.size();
    }
    return hash_value;
}

void CodeOperationTable::insert(const QString& mnemonic, const QString& binary, const QString& size)
{
    size_t index = hash(mnemonic.toUpper());
    opCode_table[index] = CodeOperation(mnemonic, binary, size);
}

bool CodeOperationTable::find(const QString& mnemonic, CodeOperation& operation) const
{
    size_t index = hash(mnemonic.toUpper());
    if (opCode_table[index].mnemonic_code == mnemonic)
    {
        operation = opCode_table[index];
        return true;
    }
    return false;
}

void CodeOperationTable::remove(const QString& mnemonic)
{
    size_t index = hash(mnemonic.toUpper());
    if (opCode_table[index].mnemonic_code == mnemonic)
    {
        opCode_table[index] = CodeOperation();
    }
}

void CodeOperationTable::clear()
{
    opCode_table.clear();
}

const std::vector<CodeOperation> &CodeOperationTable::getOpCodeTable() const
{
    return opCode_table;
}


