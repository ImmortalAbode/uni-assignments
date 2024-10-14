#include "codeoperationtable.h"

size_t CodeOperationTable::hash(const QString& key) const
{
    size_t hash_value = 0;
    for (QChar c : key) {
        hash_value = (hash_value * 31 + c.unicode()) % TABLE_SIZE;
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
    for (size_t i = 0; i < TABLE_SIZE; ++i)
        opCode_table[i] = CodeOperation();
}

size_t CodeOperationTable::getOpCodeTableSize() const
{
    return TABLE_SIZE;
}

const CodeOperation* CodeOperationTable::getOpCodeTable() const
{
    return opCode_table;
}


