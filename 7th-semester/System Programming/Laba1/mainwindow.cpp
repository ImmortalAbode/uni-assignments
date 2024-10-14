#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "TablesManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , TManager( new TablesManager())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Установка положения окна.
    setupGeometry();
    //Установка выбора примеров.
    ui->choice_example_comboBox->addItem("Пример по умолчанию (без ошибок)");
    ui->choice_example_comboBox->activated(0);
    //Блокирование второй кнопки, пока не будет нажата кнопка "первого прохода".
    ui->second_pass_pushButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete TManager;
    sourceText_code.clear();
    opCode_table.clear();
    symb_table.clear();
    sup_table.clear();
}

void MainWindow::setupGeometry()
{
    this->setGeometry(250, 40, 1000, 800);
}

//Загрузка исходного текста программы и таблицы кодов операций (ТКО) из примеров.
void MainWindow::on_choice_example_comboBox_activated(int index)
{
    //Очищаем элементы интерфейса.
    ui->source_text_textEdit->clear();

    ui->table_operation_codes_tableWidget->clear();
    ui->table_operation_codes_tableWidget->setColumnCount(0);
    ui->table_operation_codes_tableWidget->setRowCount(0);

    ui->auxiliary_table_tableWidget->clear();
    ui->auxiliary_table_tableWidget->setColumnCount(0);
    ui->auxiliary_table_tableWidget->setRowCount(0);

    ui->table_symbolic_names_tableWidget->clear();
    ui->table_symbolic_names_tableWidget->setColumnCount(0);
    ui->table_symbolic_names_tableWidget->setRowCount(0);

    ui->first_pass_errors_textBrowser->clear();
    switch (index)
    {
    case 0:
        TManager->LoadDefaultAssemblerSourceCode(ui->source_text_textEdit);
        TManager->LoadDefaultAssemplerOperationCode(ui->table_operation_codes_tableWidget);
        break;
    default:
        break;
    }
}

//Автоматическое обновление таблиц при вставке/удалении.
void MainWindow::on_table_operation_codes_tableWidget_cellChanged(int row, int column)
{
    TManager->UpdateViewOfTable(ui->table_operation_codes_tableWidget, row, column);
    //Если изменяется таблица ТКО, то очистить таблицу символических имен и вспомогательную.
    ui->auxiliary_table_tableWidget->clear();
    ui->auxiliary_table_tableWidget->setColumnCount(0);
    ui->auxiliary_table_tableWidget->setRowCount(0);

    ui->table_symbolic_names_tableWidget->clear();
    ui->table_symbolic_names_tableWidget->setColumnCount(0);
    ui->table_symbolic_names_tableWidget->setRowCount(0);
    //Заблокировать кнопку второго прохода.
    ui->second_pass_pushButton->setEnabled(false);
}
void MainWindow::on_auxiliary_table_tableWidget_cellChanged(int row, int column)
{
    TManager->UpdateViewOfTable(ui->auxiliary_table_tableWidget, row, column);
}
void MainWindow::on_table_symbolic_names_tableWidget_cellChanged(int row, int column)
{
    TManager->UpdateViewOfTable(ui->table_symbolic_names_tableWidget, row, column);
}
void MainWindow::on_source_text_textEdit_textChanged()
{
    //Если изменяется исходный текст программы, то очистить таблицу символических имен и вспомогательную.
    ui->auxiliary_table_tableWidget->clear();
    ui->auxiliary_table_tableWidget->setColumnCount(0);
    ui->auxiliary_table_tableWidget->setRowCount(0);

    ui->table_symbolic_names_tableWidget->clear();
    ui->table_symbolic_names_tableWidget->setColumnCount(0);
    ui->table_symbolic_names_tableWidget->setRowCount(0);
    //Заблокировать кнопку второго прохода.
    ui->second_pass_pushButton->setEnabled(false);
}

//Первый проход.
void MainWindow::on_first_pass_pushButton_clicked()
{
    //Очищаем все структуры.
    this->sourceText_code.clear();
    this->opCode_table.clear();
    this->sup_table.clear();
    this->symb_table.clear();
    this->sourceText_code = TManager->ParseAssemblerSourceCode(ui->source_text_textEdit);
    if(!this->TManager->ParseAssemblerOperationCode(ui->table_operation_codes_tableWidget, opCode_table, ui->first_pass_errors_textBrowser))
        return;
    if (!this->fpp.LoadSymbolicNamesTable(ui->first_pass_errors_textBrowser, sourceText_code, opCode_table, ui->auxiliary_table_tableWidget,
                                     sup_table, ui->table_symbolic_names_tableWidget, symb_table))
    {
        //Очищаем элементы интерфейса.
        ui->auxiliary_table_tableWidget->clear();
        ui->auxiliary_table_tableWidget->setColumnCount(0);
        ui->auxiliary_table_tableWidget->setRowCount(0);

        ui->table_symbolic_names_tableWidget->clear();
        ui->table_symbolic_names_tableWidget->setColumnCount(0);
        ui->table_symbolic_names_tableWidget->setRowCount(0);
        return;
    }
    ui->second_pass_pushButton->setEnabled(true);
}
//Второй проход.
void MainWindow::on_second_pass_pushButton_clicked()
{
    //Обработка второго прохода.
}

