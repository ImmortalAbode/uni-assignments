#ifndef FIRSTPASSPROCESSOR_H
#define FIRSTPASSPROCESSOR_H

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "symbolicnamestable.h"
#include "TablesManager.h"
#include "checks.h"

#include <QTableWidget>
#include <QTextEdit>

class FirstPassProcessor
{
private:
    SymbolicNamesTable symbolic_table{};
    TablesManager TManager{};
    //Объект класса Checks для различных глобальных проверок.
    Checks check{};

public:
    FirstPassProcessor() : symbolic_table(){};

    bool LoadSymbolicNamesTable(QTextEdit* fpe_text, const std::vector<AssemblerInstruction>& sourceText_code, const CodeOperationTable& opCode_table,
                                QTableWidget* aux_table, std::vector<SupportTable> sup_table,
                                QTableWidget* table_symbolic_names, SymbolicNamesTable& symb_table);
};

#endif // FIRSTPASSPROCESSOR_H
