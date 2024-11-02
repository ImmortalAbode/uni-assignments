#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TablesManager.h"
#include "codeoperationtable.h"
#include "StructSupportTable.h"
#include "symbolicnamestable.h"
#include "passprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TablesManager* TManager{};
    std::vector<AssemblerInstruction> sourceText_code{};
    CodeOperationTable opCode_table{};
    std::vector<SupportTable> sup_table{};
    SymbolicNamesTable symb_table{};
    PassProcessor pp{};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_choice_example_comboBox_activated(int index);

    void on_table_operation_codes_tableWidget_cellChanged(int row, int column);
    void on_auxiliary_table_tableWidget_cellChanged(int row, int column);
    void on_table_symbolic_names_tableWidget_cellChanged(int row, int column);
    void on_source_text_textEdit_textChanged();

    void on_first_pass_pushButton_clicked();
    void on_second_pass_pushButton_clicked();

private:
    void setupGeometry();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
