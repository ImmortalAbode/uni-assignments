#ifndef PASSPROCESSOR_H
#define PASSPROCESSOR_H

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "symbolicnamestable.h"
#include "TablesManager.h"
#include "checks.h"

#include <QTableWidget>
#include <QTextEdit>

class PassProcessor
{
private:
    TablesManager TManager{};
    //Объект класса Checks для различных проверок.
    Checks check{};
    //Счетчик адреса.
    int addressCounter{};
    //Адрес точки входа в программу.
    int end_prog_address{};
    //Адрес загрузки программы.
    int start_prog_address{};

public:
    PassProcessor() = default;

    bool LoadSymbolicNamesTable(QTextEdit* fpe_text, const std::vector<AssemblerInstruction>& sourceText_code, const CodeOperationTable& opCode_table,
                                QTableWidget* aux_table, std::vector<SupportTable>& sup_table,
                                QTableWidget* table_symbolic_names, SymbolicNamesTable& symb_table);

    bool LoadBinaryCodeText(QTableWidget* omh_table, QTextEdit* spe_text, QTextEdit* binaryCode_text,
                            const std::vector<SupportTable>& sup_table, const SymbolicNamesTable& symb_table);
};

#endif // PASSPROCESSOR_H
