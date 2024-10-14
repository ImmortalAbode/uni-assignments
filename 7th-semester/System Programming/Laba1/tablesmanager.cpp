#include "TablesManager.h"

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "StructSupportTable.h"
#include "symbolicnamestable.h"

#include <QString>
#include <QTextEdit>
#include <QTableWidget>

//Функции загрузок в соответствующую таблицу одной строки.
void TablesManager::LoadOneLineToAssemblerSourceCode(QTextEdit *source_text_TextEdit, const AssemblerInstruction &AssInstr)
{
    QString new_line{};
    new_line += AssInstr.label.value_or("") + "\t";
    new_line += AssInstr.mnemonic + "\t";
    new_line += AssInstr.operand1 + "\t";
    new_line += AssInstr.operand2.value_or("");
    source_text_TextEdit->append(new_line);
}
void TablesManager::LoadOneLIneToAssemblerOperationCode(QTableWidget *table_operation_codes_TableWidget, const CodeOperation &OpCode)
{
    int last_row = table_operation_codes_TableWidget->rowCount() - 1;
    table_operation_codes_TableWidget->setItem(last_row, 0, new QTableWidgetItem(OpCode.mnemonic_code));
    table_operation_codes_TableWidget->setItem(last_row, 1, new QTableWidgetItem(OpCode.binary_code));
    table_operation_codes_TableWidget->setItem(last_row, 2, new QTableWidgetItem(OpCode.size));
}
void TablesManager::LoadOneLineToSupportTable(QTableWidget *aux_table, const SupportTable &aux)
{
    if (aux_table == nullptr){
        qDebug() << "Pointer to aux_table was empty in TablesManager::LoadSupportTable.";
        return;
    }
    else
    {
        int last_row = aux_table->rowCount() - 1;
        aux_table->setItem(last_row, 0, new QTableWidgetItem(aux.machine_code));
        aux_table->setItem(last_row, 1, new QTableWidgetItem(aux.operation_code));
        aux_table->setItem(last_row, 2, new QTableWidgetItem(aux.operand1));
        aux_table->setItem(last_row, 3, new QTableWidgetItem(aux.operand2));
    }
}
void TablesManager::LoadOneLineToSymbolicNamesTable(QTableWidget *symb_table, const SymbolicNamesTable &symb, QString name)
{
    if (symb_table == nullptr){
        qDebug() << "Pointer to symb_table was empty in TablesManager::LoadOneLineToSymbolicNamesTable.";
        return;
    }
    else
    {
        QString address{};
        symb.find(name, address);
        int last_row = symb_table->rowCount() - 1;
        symb_table->setItem(last_row, 0, new QTableWidgetItem(name));
        symb_table->setItem(last_row, 1, new QTableWidgetItem(address));
    }
}

//Функции загрузок прримеров.
void TablesManager::LoadDefaultAssemblerSourceCode(QTextEdit *source_text_TextEdit)
{
    if (source_text_TextEdit == nullptr)
    {
        qDebug() << "Pointer to source_text_TextEdit was empty in TablesManager::LoadDefaultAssemblerSourceCode.";
        return;
    }
    else
    {
        //Очищаем поле ввода исходного текста программы.
        source_text_TextEdit->clear();
        //Вставляем пример.
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"Prog1", "START", "100", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"", "JMP", "L1", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"A1", "RESB", "10", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"A2", "RESW", "20", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"B1", "WORD", "4096", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"B2", "BYTE", "X'2F4C008A'", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"B3", "BYTE", "C'Hello!'", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"B4", "BYTE", "128", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"L1", "LOADR1", "B1", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"", "LOADR2", "B4", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"", "ADD", "R1", "R2"});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"", "SAVER1", "B1", ""});
        this->LoadOneLineToAssemblerSourceCode(source_text_TextEdit, {"", "END", "100", ""});
    }
}
void TablesManager::LoadDefaultAssemplerOperationCode(QTableWidget *table_operation_codes_tableWidget)
{
    if (table_operation_codes_tableWidget == nullptr){
        qDebug() << "Pointer to table_operation_codes_tableWidget was empty in TablesManager::LoadDefaultAssemplerOperationCode.";
        return;
    }
    else
    {
        //Очищаем имеющуюся ТКО (интерфейс).
        table_operation_codes_tableWidget->clear();
        table_operation_codes_tableWidget->setColumnCount(3);
        table_operation_codes_tableWidget->setRowCount(1);
        //Вставляем пример.
        LoadOneLIneToAssemblerOperationCode(table_operation_codes_tableWidget, {"JMP", "01", "4"});
        LoadOneLIneToAssemblerOperationCode(table_operation_codes_tableWidget, {"LOADR1", "02", "4"});
        LoadOneLIneToAssemblerOperationCode(table_operation_codes_tableWidget, {"LOADR2", "03", "4"});
        LoadOneLIneToAssemblerOperationCode(table_operation_codes_tableWidget, {"ADD", "04", "2"});
        LoadOneLIneToAssemblerOperationCode(table_operation_codes_tableWidget, {"SAVER1", "05", "4"});
    }
}

//Функции парсинга данных из элементов интерфейса в структуру.
std::vector<AssemblerInstruction> TablesManager::ParseAssemblerSourceCode(QTextEdit *source_text_TextEdit)
{
    std::vector<AssemblerInstruction> source_code{};
    QString text = source_text_TextEdit->toPlainText();
    QStringList lines = text.split("\n");
    for (const QString &line : lines)
    {
        static const QRegularExpression for_split_on_parts{"\\s+"};
        QStringList parts = line.split(for_split_on_parts, Qt::SkipEmptyParts);
        AssemblerInstruction temp_code_line{};
        bool startsWithSpace = line.startsWith(" ") || line.startsWith("\t");
        if (startsWithSpace)
            parts.prepend("");
        if (parts.size() > 0){ temp_code_line.label = parts[0];};
        if (parts.size() > 1){ temp_code_line.mnemonic = parts[1];};
        if (parts.size() > 2){ temp_code_line.operand1 = parts[2];};
        if (parts.size() > 3){ temp_code_line.operand2 = parts.mid(3).join(" ");};
        source_code.push_back(temp_code_line);
    }

    return source_code;

}
CodeOperationTable TablesManager::ParseAssemblerOperationCode(QTableWidget *table_operation_codes_tableWidget)
{
    CodeOperationTable opCode_table{};
    for (int row{}; row < table_operation_codes_tableWidget->rowCount(); ++row)
    {
        QString mnemonic_code{table_operation_codes_tableWidget->item(row, 0) == nullptr ? "" : table_operation_codes_tableWidget->item(row, 0)->text()};
        QString binary_code{table_operation_codes_tableWidget->item(row, 1) == nullptr ? "" : table_operation_codes_tableWidget->item(row, 1)->text()};
        QString size{table_operation_codes_tableWidget->item(row, 2) == nullptr ? "" : table_operation_codes_tableWidget->item(row, 2)->text()};

        opCode_table.insert(mnemonic_code.toUpper(), binary_code.toUpper(), size);
    }
    return opCode_table;
}

//Функция обновления таблиц при их изменении.
void TablesManager::UpdateViewOfTable(QTableWidget *current_table, const int& row, const int& column)
{
    if (current_table == nullptr) {
        qDebug() << "Pointer to current_table was empty in TablesManager::UpdateViewOfTable.";
        return;
    }
    //Если последняя строка таблицы не пустая, то вставляем пустую строку.
    if (row == current_table->rowCount() - 1)
    {
        if (current_table->item(row, column) != nullptr &&
            !current_table->item(row, column)->text().isEmpty())
        {
            current_table->insertRow(row + 1);
        }
    }
    //Удаление пустых строк в таблице (кроме последней).
    for (int i = 0; i < current_table->rowCount() - 1; ++i)
    {
        bool rowEmpty = true;
        for (int col = 0; col < current_table->columnCount(); ++col)
        {
            if (current_table->item(i, col) != nullptr &&
                !current_table->item(i, col)->text().isEmpty())
            {
                rowEmpty = false;
                break;
            }
        }
        if (rowEmpty)
        {
            current_table->removeRow(i);
            --i;
        }
    }
}
