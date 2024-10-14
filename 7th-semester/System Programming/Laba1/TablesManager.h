#ifndef TABLESMANAGER_H
#define TABLESMANAGER_H

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "StructSupportTable.h"
#include "symbolicnamestable.h"
#include <QTextEdit>
#include <QTableWidget>

class TablesManager
{

public:
    TablesManager() = default;
    ~TablesManager() = default;

    void LoadOneLineToAssemblerSourceCode(QTextEdit* source_text_TextEdit, const AssemblerInstruction& AssInstr);
    void LoadOneLIneToAssemblerOperationCode(QTableWidget* table_operation_codes_TableWidget, const CodeOperation& OpCode);
    void LoadOneLineToSupportTable(QTableWidget* aux_table, const SupportTable& aux);
    void LoadOneLineToSymbolicNamesTable(QTableWidget* symb_table, const SymbolicNamesTable& symb, QString name);

    void LoadDefaultAssemblerSourceCode(QTextEdit* source_text_TextEdi);
    void LoadDefaultAssemplerOperationCode(QTableWidget* table_operation_codes_tableWidget);

    std::vector<AssemblerInstruction> ParseAssemblerSourceCode(QTextEdit* source_text_TextEdit);
    CodeOperationTable ParseAssemblerOperationCode(QTableWidget* table_operation_codes_tableWidget);

    void UpdateViewOfTable(QTableWidget* current_table, const int& row, const int& column);
};

#endif // TABLESMANAGER_H
