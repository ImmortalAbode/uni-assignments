#include "adminmenu.h"
#include "ui_adminmenu.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

AdminMenu::AdminMenu(ServerConnection* serverConn, QString type_admin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
    this->type_admin = type_admin;
    this->serverConn = serverConn;
    //Скрыть уникальные действия админа на панели инструментов для менеджера.
    if (type_admin == "Manager")
    {
        this->setWindowTitle("Администратор");
        ui->action_add_man->setVisible(false);
        ui->action_remove_change_man->setVisible(false);
        ui->action_add_project->setVisible(false);
        ui->action_remove_change_project->setVisible(false);

        int index;
        QAction *separatorAction;
        //Удаление
        index = 4;
        separatorAction = ui->toolBar->actions().at(index);
        ui->toolBar->removeAction(separatorAction);
        index = 13;
        separatorAction = ui->toolBar->actions().at(index);
        ui->toolBar->removeAction(separatorAction);
    }
    connect(this->serverConn, &ServerConnection::getAdminSaveReportResult, this, &AdminMenu::slotAdminSaveReportResult);
    connect(this->serverConn, &ServerConnection::getAdminRemoveAnomalyResult, this, &AdminMenu::slotAdminRemoveAnomaly);
    connect(this->serverConn, &ServerConnection::getAdminAnomalyDataResult, this, &AdminMenu::slotGetAdminAnomalyDataResult);
    connect(ui->comboBox_empIDForAnomaly, &QComboBox::currentIndexChanged, this, &AdminMenu::slotAdminUpdateAnomalyTable);
    connect(this->serverConn, &ServerConnection::getAdminEmployeeTableForAnomalyResult, this, &AdminMenu::slotAdminEmployeeTableForAnomalyResult);
    connect(this->serverConn, &ServerConnection::getAdminRemoveWeekendResult, this, &AdminMenu::slotGetAdminRemoveWeekendResult);
    connect(this->serverConn, &ServerConnection::getAdminWorkWithWeekendResult, this, &AdminMenu::slotGetAdminWorkWithWeekendResult);
    connect(this->serverConn, &ServerConnection::getAdminRemoveGrafResult, this, &AdminMenu::slotGetAdminRemoveGrafResult);
    connect(this->serverConn, &ServerConnection::getAdminWorkWithGrafResult, this, &AdminMenu::slotGetAdminWorkWithGrafResult);
    connect(this->serverConn, &ServerConnection::getAdminEmployeeWeekendsResult, this, &AdminMenu::slotGetAdminEmployeeWeekendsResult);
    connect(this->serverConn, &ServerConnection::getAdminEmployeeGrafsResult, this, &AdminMenu::slotGetAdminEmployeeGrafsResult);
    connect(this->serverConn, &ServerConnection::getAdminEmployeeDataResult, this, &AdminMenu::slotGetAdminEmployeeDataResult);
    connect(this->serverConn, &ServerConnection::getAdminCompleteProjectTasksResult, this, &AdminMenu::slotGetAdminCompleteProjectTasksResult);
    connect(ui->comboBox_projID, &QComboBox::currentIndexChanged, this, &AdminMenu::slotUpdateProjectTasksTable);
    connect(this->serverConn, &ServerConnection::getAdminCompleteProjectsResult, this, &AdminMenu::slotGetAdminCompleteProjectsResult);
    connect(this->serverConn, &ServerConnection::getAdminCredentialsDataResult, this, &AdminMenu::slotGetAdminCredentialsDataResult);
    connect(this->serverConn, &ServerConnection::employeeTableDataResult, this, &AdminMenu::slotEmployeeTableDataResult);
    connect(this->serverConn, &ServerConnection::registrationResult, this, &AdminMenu::slotAddedEmployeeSuccess);
    connect(this->serverConn, &ServerConnection::removedEmployeeResult, this, &AdminMenu::slotRemovedEmployeeSuccess);
    connect(this->serverConn, &ServerConnection::changedEmployeeResult, this, &AdminMenu::slotChangedEmployeeResult);
    connect(this->serverConn, &ServerConnection::employeeRequestsResult, this, &AdminMenu::slotGetEmployeeRequests);
    connect(this->serverConn, &ServerConnection::requestStatusesResult, this, &AdminMenu::slotGetRequestStatuses);
    connect(this->serverConn, &ServerConnection::adminTableDataResult, this, &AdminMenu::slotAdminTableDataResult_remove);
    connect(this->serverConn, &ServerConnection::removedAdminResult, this, &AdminMenu::slotRemovedAdminSuccess);
    connect(this->serverConn, &ServerConnection::addedAdminResult, this, &AdminMenu::slotAddedAdminSuccess);
    connect(this->serverConn, &ServerConnection::changedAdminResult, this, &AdminMenu::slotChangedAdminResult);
    connect(this->serverConn, &ServerConnection::allClosedRequestsResult, this, &AdminMenu::slotAllClosedRequests);
    connect(this->serverConn, &ServerConnection::projectsAndTasksResult, this, &AdminMenu::slotAllProjectsAndTasks);
    connect(this->serverConn, &ServerConnection::addProjectDataResult, this, &AdminMenu::slotAddProjectsDataRequest);
    connect(this->serverConn, &ServerConnection::changeProjectDataResult, this, &AdminMenu::slotProjectsDataForChange);
    connect(this->serverConn, &ServerConnection::removedChangedProjectSuccess, this, &AdminMenu::slotRemoveChangeProjectCompleted);
    connect(this->serverConn, &ServerConnection::taskDataTableResult, this, &AdminMenu::slotTaskTableDataResult);
    connect(this->serverConn, &ServerConnection::empsForTaskDataTableResult, this, &AdminMenu::slotEmployeeForTaskTableDataResult);
    connect(this->serverConn, &ServerConnection::removedChangedTaskSuccess, this, &AdminMenu::slotRemoveChangeTaskCompleted);
    connect(this->serverConn, &ServerConnection::adminCloseRequestSuccess, this, &AdminMenu::slotCloseRequestCompleted);
    connect(this->serverConn, &ServerConnection::addProjectSuccess, this, &AdminMenu::slotAddProjectCompleted);
    connect(this->serverConn, &ServerConnection::addTaskSuccess, this, &AdminMenu::slotAddTaskCompleted);
    connect(this->serverConn, &ServerConnection::teamDataTableResult, this, &AdminMenu::slotTeamDataTableResult);
    connect(this->serverConn, &ServerConnection::onlineDataTableResult, this, &AdminMenu::slotOnlineDataTableResult);

    ui->stackedWidget_admin_funcs->setCurrentIndex(0);
    serverConn->getAdminCredentialsData();
}

AdminMenu::~AdminMenu()
{
    delete ui;
}

void AdminMenu::on_action_common_statistic_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 0)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(0);
        serverConn->getAdminCredentialsData();
    }
}

void AdminMenu::on_action_report_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 1)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(1);
        ui->dateEdit_ReportBegin->setDate(QDate::currentDate());
        ui->dateEdit_ReportEnd->setDate(QDate::currentDate());
        serverConn->getAdminEmployeeTableForAnomaly(type_admin);
    }
}

void AdminMenu::on_action_team_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 2)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(2);
        serverConn->getTeam(type_admin);
    }
}

void AdminMenu::on_action_add_man_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 3)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(3);
        disconnect(this->serverConn, &ServerConnection::employeeTableDataResult, nullptr, nullptr);
        connect(this->serverConn, &ServerConnection::employeeTableDataResult, this, &AdminMenu::slotAdminTableDataResult);
        serverConn->getEmployeeDataTable(type_admin);
    }
}

void AdminMenu::on_action_remove_change_man_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 4)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(4);
        disconnect(this->serverConn, &ServerConnection::employeeTableDataResult, nullptr, nullptr);
        serverConn->getAdminTableData();
    }
}

void AdminMenu::on_action_add_emp_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 5)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(5);
        disconnect(this->serverConn, &ServerConnection::employeeTableDataResult, nullptr, nullptr);
        connect(this->serverConn, &ServerConnection::employeeTableDataResult, this, &AdminMenu::slotEmployeeTableDataResult);
        serverConn->getEmployeeDataTable(type_admin);
    }
}

void AdminMenu::on_action_remove_change_emp_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 6)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(6);
        disconnect(this->serverConn, &ServerConnection::employeeTableDataResult, nullptr, nullptr);
        connect(this->serverConn, &ServerConnection::employeeTableDataResult, this, &AdminMenu::slotEmployeeTableDataResult);
        serverConn->getEmployeeDataTable(type_admin);
    }
}

void AdminMenu::on_action_grafs_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 7)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(7);
        serverConn->getAdminEmployeeData(type_admin);
    }
}

void AdminMenu::on_action_projects_tasks_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 8)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(8);
        serverConn->getAllProjectsAndTasksTableData(type_admin);
    }
}

void AdminMenu::on_action_add_project_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 9)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(9);
        serverConn->getAddProjectTableData();
    }
}

void AdminMenu::on_action_remove_change_project_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 10)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(10);
        serverConn->getProjectsDataForChange();
    }
}

void AdminMenu::on_action_add_task_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 11)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(11);
        serverConn->getTasksDataTable(type_admin);
    }
}

void AdminMenu::on_action_remove_change_task_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 12)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(12);
        serverConn->getTasksDataTable(type_admin);
    }
}

void AdminMenu::on_action_users_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 13)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(13);
        serverConn->getAllOnlineUsers();
    }
}

void AdminMenu::on_action_unprocessed_query_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 14)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(14);
        serverConn->getEmployeeRequestsDataTable(type_admin);
    }
}

void AdminMenu::on_action_close_query_triggered()
{
    if (ui->stackedWidget_admin_funcs->currentIndex() != 15)
    {
        ui->stackedWidget_admin_funcs->setCurrentIndex(15);
        serverConn->getClosedRequestsTableData();
    }
}

void AdminMenu::on_action_exit_triggered()
{
    close();
}

void AdminMenu::slotEmployeeTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = users_data[i][j];
            QModelIndex index = model->index(i, j);

            // Установка цвета текста столбцов.
            if (j == 10) {
                model->setData(index, QBrush(Qt::blue), Qt::ForegroundRole);
            }
            if (j == 4){
                if (value == "Оффлайн") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                } else if (value == "Онлайн") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                }
            }
            model->setData(index, value);
        }
    }
    ui->tableView_UsersTable_add->setModel(model);
    ui->tableView_UsersTable_add->resizeColumnsToContents();
    ui->tableView_UsersTable_rem_ch->setModel(model);
    ui->tableView_UsersTable_rem_ch->resizeColumnsToContents();
    ui->tableView_UsersTable_add->show();
    ui->tableView_UsersTable_rem_ch->show();
}

void AdminMenu::slotAdminTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = users_data[i][j];
            QModelIndex index = model->index(i, j);
            // Установка цвета текста столбцов.
            if (j == 10) {
                model->setData(index, QBrush(Qt::blue), Qt::ForegroundRole);
            }
            if (j == 4){
                if (value == "Оффлайн") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                } else if (value == "Онлайн") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                }
            }
            model->setData(index, value);
            model->setData(index, value);
        }
    }
    ui->tableView_UsersTable_add_man->setModel(model);
    ui->tableView_UsersTable_add_man->resizeColumnsToContents();
    ui->tableView_UsersTable_add_man->show();
}

void AdminMenu::slotAdminTableDataResult_remove(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = users_data[i][j];
            QModelIndex index = model->index(i, j);
            // Установка цвета текста столбцов.
            if (j == 9) {
                model->setData(index, QBrush(Qt::blue), Qt::ForegroundRole);
            }
            if (j == 4){
                if (value == "Оффлайн") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                } else if (value == "Онлайн") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                }
            }
            model->setData(index, value);
            model->setData(index, value);
        }
    }
    ui->tableView_UsersData_remove_man->setModel(model);
    ui->tableView_UsersData_remove_man->resizeColumnsToContents();
    ui->tableView_UsersData_remove_man->show();
}

void AdminMenu::slotRemovedAdminSuccess(bool removing_success)
{
    if (removing_success){
        QMessageBox::information(this, "Удаление руководителя", "Указанный менеджер был разжалован, однако его данные, как руководителя, до удаления сохранены в системе.");
        ui->lineEdit_ManID_remove_man->setText("");
    }
    else{
        QMessageBox::warning(this, "Удаление руководителя", "Ошибка! Проверьте корректность указываемого ID пользователя и его отсутствие в сети.");
    }
    serverConn->getAdminTableData();
}

void AdminMenu::slotAddedAdminSuccess(bool adding_success)
{
    if (adding_success){
        QMessageBox::information(this, "Информация", "Сотрудник успешно был повышен до руководителя!");
        ui->lineEdit_EmployeeID_add_man->setText("");
        ui->lineEdit_JobTitle_add_man->setText("");
    }
    else{
        QMessageBox::warning(this, "Добавление руководителя", "Ошибка! Проверьте корректность указываемого ID пользователя и его отсутствие в сети.");
    }
    serverConn->getEmployeeDataTable(type_admin);
}

void AdminMenu::slotChangedAdminResult(QMap<QString, bool> change_employee_success)
{
    if (!change_employee_success["ManagerID"]){
        QMessageBox::warning(this, "Изменение данных руководителя", "Ошибка! Руководителя с указанным ID не найдено либо ID указан неверно. "
                                                                    "ID руководителя должно быть целым положительным числом (см. таблицу). "
                                                                    "Проверьте корректность введенных данных.");
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Изменение данных руководителя");
        msgBox.setText("Вы успешно изменили данные руководителя! Его прошлое, как сотрудника, осталось без изменений.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
        {
            ui->lineEdit_JobTitle_change_man->setText("");
            ui->lineEdit_ContactInf_change_man->setText("");
        }
    }
    serverConn->getAdminTableData();
}

void AdminMenu::slotAllClosedRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = users_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);

            // Установка цвета текста для седьмого столбца.
            if (j == 6) {
                if (value == "Принято") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                } else if (value == "Отклонено") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_AllClosedRequests->setModel(model);
    ui->tableView_AllClosedRequests->resizeColumnsToContents();
    ui->tableView_AllClosedRequests->show();
}

void AdminMenu::slotAllProjectsAndTasks(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = projects_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);

            //Установка цвета текста для третьего и девятого столбцов.
            if (j == 2 || j == 8) {
                if (value == "Завершено") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                } else if (value == "Не завершено") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_AllProjects->setModel(model);
    ui->tableView_AllProjects->resizeColumnsToContents();
    ui->tableView_AllProjects->show();
}

void AdminMenu::slotAddProjectsDataRequest(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data)
{
    ui->comboBox_ProjectManagerID->clear();
    ui->comboBox_ProjectManagerID->setMaxVisibleItems(6);
    ui->comboBox_projectID->clear();
    ui->comboBox_projectID->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = projects_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);

            if (j == 0){
                if (ui->comboBox_ProjectManagerID->findText(value) == -1)
                {
                    ui->comboBox_ProjectManagerID->addItem(value);
                }
            }
            if (j == 4 && value != "0"){
                if (ui->comboBox_projectID->findText(value) == -1)
                {
                    ui->comboBox_projectID->addItem(value);
                }
            }
            //Установка цвета текста для седьмого столбца.
            if (j == 7) {
                if (value == "Завершено") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                } else if (value == "Не завершено") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_projects->setModel(model);
    ui->tableView_projects->resizeColumnsToContents();
    ui->tableView_projects->show();
}

void AdminMenu::slotProjectsDataForChange(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data)
{
    ui->comboBox_IDProject->clear();
    ui->comboBox_IDProject->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = projects_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == 0){
                if (ui->comboBox_IDProject->findText(projects_data[i][j]) == -1)
                {
                    ui->comboBox_IDProject->addItem(projects_data[i][j]);
                }
            }
            //Установка цвета текста для четвертого и десятого столбцов.
            if (j == 3 || j == 9) {
                if (value == "Завершено") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                } else if (value == "Не завершено") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_remove_project->setModel(model);
    ui->tableView_remove_project->resizeColumnsToContents();
    ui->tableView_remove_project->show();
}

void AdminMenu::slotRemoveChangeProjectCompleted()
{
    serverConn->getProjectsDataForChange();
}

void AdminMenu::slotTaskTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> tasks_data)
{
    ui->comboBox_task_project_id->clear();
    ui->comboBox_task_id->clear();
    ui->comboBox_task2_id->clear();
    ui->comboBox_task_project_id->setMaxVisibleItems(6);
    ui->comboBox_task_id->setMaxVisibleItems(6);
    ui->comboBox_task2_id->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = tasks_data[i][j];
            QModelIndex index = model->index(i, j);
            if (j == 3){
                if (ui->comboBox_task_project_id->findText(value) == -1)
                {
                    ui->comboBox_task_project_id->addItem(value);
                }
            }
            if (j == 6){
                ui->comboBox_task_id->addItem(value);
                if (value != "0"){
                    ui->comboBox_task2_id->addItem(value);
                }
            }
            //Установка цвета текста для столбцов.
            if (j == 5 || j == 8) {
                if (value == "Завершено") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                } else if (value == "Не завершено") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                }
            }
            model->setData(index, value);
        }
    }
    ui->tableView_add_task->setModel(model);
    ui->tableView_add_task->resizeColumnsToContents();
    ui->tableView_add_task->show();
    ui->tableView_remove_task->setModel(model);
    ui->tableView_remove_task->resizeColumnsToContents();
    ui->tableView_remove_task->show();
    serverConn->getEmployeeDataTableForTask(type_admin);
}

void AdminMenu::slotEmployeeForTaskTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emps_data)
{
    ui->comboBox_task_emp_id->clear();
    ui->comboBox_task_emp_id->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = emps_data[i][j];
            QModelIndex index = model->index(i, j);
            if (j == 0){
                ui->comboBox_task_emp_id->addItem(value);
            }
            model->setData(index, value);
        }
    }
    ui->tableView_task_all_employees->setModel(model);
    ui->tableView_task_all_employees->resizeColumnsToContents();
    ui->tableView_task_all_employees->show();
    ui->tableView_task2_all_employees->setModel(model);
    ui->tableView_task2_all_employees->resizeColumnsToContents();
    ui->tableView_task2_all_employees->show();
}

void AdminMenu::slotRemoveChangeTaskCompleted()
{
    serverConn->getTasksDataTable(type_admin);
}

void AdminMenu::slotCloseRequestCompleted()
{
    serverConn->getEmployeeRequestsDataTable(type_admin);
}

void AdminMenu::slotAddProjectCompleted()
{
    serverConn->getAddProjectTableData();
}

void AdminMenu::slotAddTaskCompleted(bool adding_success)
{
    if (!adding_success){
        QMessageBox::warning(this, "Добавление задача", "Такое название задачи уже есть в системе. Попробуйте изменить название или добавить формальную приписку к задаче. "
                                                        "Это нужно для единственной идентификации задачи в системе.");
    }
    serverConn->getTasksDataTable(type_admin);
}
void AdminMenu::slotTeamDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> team_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = team_data[i][j];
            QModelIndex index = model->index(i, j);
            //Установка цвета текста для столбцов.
            if (j == 8) {
                if (value == "Онлайн") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                } else if (value == "Оффлайн") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                }
            }
            model->setData(index, value);
        }
    }
    ui->tableView_team->setModel(model);
    ui->tableView_team->resizeColumnsToContents();
    ui->tableView_team->show();
}

void AdminMenu::slotOnlineDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> online_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = online_data[i][j];
            QModelIndex index = model->index(i, j);
            //Установка цвета текста для столбцов.
            if (j == 6) {
                if (value == "Онлайн") {
                    model->setData(index, QBrush(Qt::green), Qt::ForegroundRole);
                } else if (value == "Оффлайн") {
                    model->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
                }
            }
            model->setData(index, value);
        }
    }
    ui->tableView_onlineData->setModel(model);
    ui->tableView_onlineData->resizeColumnsToContents();
    ui->tableView_onlineData->show();
}

void AdminMenu::slotAddedEmployeeSuccess(QMap<QString, bool> reg_success)
{
    if (!reg_success["FirstName"] || !reg_success["LastName"] || !reg_success["MiddleName"] || !reg_success["JobTitle"])
    {
        QMessageBox::warning(this, "Добавление нового сотрудника", "Ошибка! Поля 'Имя', 'Фамилия', 'Отчество', 'Должность' не должны содержать символов, отличных от кириллицы."
                                                  "Поле 'Отчество' может быть пустым.");
    }
    else if (!reg_success["PersonnelNumber"])
    {
        QMessageBox::warning(this, "Добавление нового сотрудника", "Ошибка! Табельный номер добавляемого сотрудника должен быть уникальным и состоять из цифр."
                                                  " Проверьте корректность ввода или исправьте ситуацию иным способом.");
    }
    else if (!reg_success["Login"])
    {
        QMessageBox::warning(this, "Добавление нового сотрудника", "Ошибка! Логин добавляемого сотрудника должен быть уникальным. "
                                                                   "Придумайте новый логин и попробуйте заново.");
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Добавление нового сотрудника");
        msgBox.setText("Вы успешно зарегистрировали сотрудника! Не забудьте попросить записать его свои логин и пароль "
                       "для случая их потери.\n\nСотруднику необходимо авторизоваться для дальнейшей работы в системе.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
        {
            ui->lineEdit_FirstName_add->setText("");
            ui->lineEdit_LastName_add->setText("");
            ui->lineEdit_MiddleName_add->setText("");
            ui->lineEdit_JobTitle_add->setText("");
            ui->lineEdit_PersonnelNumber_add->setText("");
            ui->lineEdit_ContactInformation_add->setText("");
            ui->lineEdit_AdditionalInfo_add->setText("");
            serverConn->getEmployeeDataTable(type_admin);
        }
    }
}

void AdminMenu::slotRemovedEmployeeSuccess(bool removing_success)
{
    if (removing_success){
        QMessageBox::warning(this, "Удаление пользователя", "Указанный пользователь был успешно удален.");
        ui->lineEdit_EmployeeID->setText("");
        serverConn->getEmployeeDataTable(type_admin);
    }
    else{
        QMessageBox::warning(this, "Удаление пользователя", "Ошибка! Проверьте корректность указываемого ID пользователя и его отсутствие в сети.");
    }
}

void AdminMenu::slotChangedEmployeeResult(QMap<QString, bool> change_employee_success)
{
    if (!change_employee_success["EmployeeID"]){
        QMessageBox::warning(this, "Изменение данных сотрудника", "Ошибка! Сотрудника с указанным ID не найдено либо ID указан неверно. "
                                                                  "ID сотрудника должно быть целым положительным числом (см. таблицу). "
                                                                  "Проверьте корректность введенных данных.");
    }
    else if (!change_employee_success["FirstName"] || !change_employee_success["LastName"] || !change_employee_success["MiddleName"] || !change_employee_success["JobTitle"])
    {
        QMessageBox::warning(this, "Изменение данных сотрудника", "Ошибка! Поля 'Имя', 'Фамилия', 'Отчество', 'Должность' не должны содержать символов, отличных от кириллицы."
                                                                   "Поле 'Отчество' может быть пустым.");
    }
    else if (!change_employee_success["PersonnelNumber"])
    {
        QMessageBox::warning(this, "Изменение данных сотрудника", "Ошибка! Табельный номер изменяемого сотрудника указан неверно. "
                                                                  "Он должен быть уникальным (либо остаться прежним) и представлять целое положительное число."
                                                                  "Проверьте корректность ввода табельного номера и попробуйте заново.");
    }
    else if (!change_employee_success["Login"])
    {
        QMessageBox::warning(this, "Изменение данных сотрудника", "Ошибка! Логин изменяемого сотрудника должен быть уникальным или остаться прежним. "
                                                                   "Проверьте корректность ввода логина и попробуйте заново.");
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Изменение данных сотрудника");
        msgBox.setText("Вы успешно изменили данные сотрудника! Не забудьте попросить записать его свои новые данные при необходимости.\n\n"
                       "Сотруднику необходимо авторизоваться в след. раз с учетом новых данных.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
        {
            ui->lineEdit_EmployeeID->setText("");
            ui->lineEdit_FirstName_rem_ch->setText("");
            ui->lineEdit_LastName_rem_ch->setText("");
            ui->lineEdit_MiddleName_rem_ch->setText("");
            ui->lineEdit_JobTitle_rem_ch->setText("");
            ui->lineEdit_PersonnelNumber_rem_ch->setText("");
            ui->lineEdit_ContactInformation_rem_ch->setText("");
            ui->lineEdit_AdditionalInfo_rem_ch->setText("");
            ui->lineEdit_login_rem_ch->setText("");
            ui->lineEdit_pswd_rem_ch->setText("");
        }
        serverConn->getEmployeeDataTable(type_admin);
    }
}

void AdminMenu::slotGetEmployeeRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_requests_data)
{
    ui->comboBox_requestID->clear();
    ui->comboBox_requestID->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            if (j == 0) ui->comboBox_requestID->addItem(emp_requests_data[i][j]);
            QString value = emp_requests_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
        }
    }
    ui->tableView_empRequests->setModel(model);
    ui->tableView_empRequests->resizeColumnsToContents();
    ui->tableView_empRequests->show();
    serverConn->getRequestStatuses();
}

void AdminMenu::slotGetRequestStatuses(QStringList requestStatuses)
{
    ui->comboBox_requestStatus->clear();
    for (const QString &requestStatus : requestStatuses) {
        ui->comboBox_requestStatus->addItem(requestStatus);
    }
    ui->comboBox_requestStatus->setCurrentIndex(0);
}

void AdminMenu::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn;
    resBtn = QMessageBox::question(this, "Выход из аккаунта",
                          tr("Вы уверены, что хотите выйти из аккаунта и вернуться на окно авторизации?\n"),
                          QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        disconnect(this->serverConn, &ServerConnection::getAdminSaveReportResult, this, &AdminMenu::slotAdminSaveReportResult);
        disconnect(this->serverConn, &ServerConnection::getAdminRemoveAnomalyResult, this, &AdminMenu::slotAdminRemoveAnomaly);
        disconnect(this->serverConn, &ServerConnection::getAdminAnomalyDataResult, this, &AdminMenu::slotGetAdminAnomalyDataResult);
        disconnect(ui->comboBox_empIDForAnomaly, &QComboBox::currentIndexChanged, this, &AdminMenu::slotAdminUpdateAnomalyTable);
        disconnect(this->serverConn, &ServerConnection::getAdminEmployeeTableForAnomalyResult, this, &AdminMenu::slotAdminEmployeeTableForAnomalyResult);
        disconnect(this->serverConn, &ServerConnection::getAdminRemoveWeekendResult, this, &AdminMenu::slotGetAdminRemoveWeekendResult);
        disconnect(this->serverConn, &ServerConnection::getAdminWorkWithWeekendResult, this, &AdminMenu::slotGetAdminWorkWithWeekendResult);
        disconnect(this->serverConn, &ServerConnection::getAdminRemoveGrafResult, this, &AdminMenu::slotGetAdminRemoveGrafResult);
        disconnect(this->serverConn, &ServerConnection::getAdminWorkWithGrafResult, this, &AdminMenu::slotGetAdminWorkWithGrafResult);
        disconnect(this->serverConn, &ServerConnection::getAdminEmployeeWeekendsResult, this, &AdminMenu::slotGetAdminEmployeeWeekendsResult);
        disconnect(this->serverConn, &ServerConnection::getAdminEmployeeGrafsResult, this, &AdminMenu::slotGetAdminEmployeeGrafsResult);
        disconnect(this->serverConn, &ServerConnection::getAdminEmployeeDataResult, this, &AdminMenu::slotGetAdminEmployeeDataResult);
        disconnect(this->serverConn, &ServerConnection::getAdminCompleteProjectTasksResult, this, &AdminMenu::slotGetAdminCompleteProjectTasksResult);
        disconnect(ui->comboBox_projID, &QComboBox::currentIndexChanged, this, &AdminMenu::slotUpdateProjectTasksTable);
        disconnect(this->serverConn, &ServerConnection::getAdminCompleteProjectsResult, this, &AdminMenu::slotGetAdminCompleteProjectsResult);
        disconnect(this->serverConn, &ServerConnection::getAdminCredentialsDataResult, this, &AdminMenu::slotGetAdminCredentialsDataResult);
        disconnect(this->serverConn, &ServerConnection::employeeTableDataResult, this, &AdminMenu::slotEmployeeTableDataResult);
        disconnect(this->serverConn, &ServerConnection::registrationResult, this, &AdminMenu::slotAddedEmployeeSuccess);
        disconnect(this->serverConn, &ServerConnection::removedEmployeeResult, this, &AdminMenu::slotRemovedEmployeeSuccess);
        disconnect(this->serverConn, &ServerConnection::changedEmployeeResult, this, &AdminMenu::slotChangedEmployeeResult);
        disconnect(this->serverConn, &ServerConnection::employeeRequestsResult, this, &AdminMenu::slotGetEmployeeRequests);
        disconnect(this->serverConn, &ServerConnection::requestStatusesResult, this, &AdminMenu::slotGetRequestStatuses);
        disconnect(this->serverConn, &ServerConnection::adminTableDataResult, this, &AdminMenu::slotAdminTableDataResult_remove);
        disconnect(this->serverConn, &ServerConnection::removedAdminResult, this, &AdminMenu::slotRemovedAdminSuccess);
        disconnect(this->serverConn, &ServerConnection::addedAdminResult, this, &AdminMenu::slotAddedAdminSuccess);
        disconnect(this->serverConn, &ServerConnection::changedAdminResult, this, &AdminMenu::slotChangedAdminResult);
        disconnect(this->serverConn, &ServerConnection::allClosedRequestsResult, this, &AdminMenu::slotAllClosedRequests);
        disconnect(this->serverConn, &ServerConnection::projectsAndTasksResult, this, &AdminMenu::slotAllProjectsAndTasks);
        disconnect(this->serverConn, &ServerConnection::addProjectDataResult, this, &AdminMenu::slotAddProjectsDataRequest);
        disconnect(this->serverConn, &ServerConnection::changeProjectDataResult, this, &AdminMenu::slotProjectsDataForChange);
        disconnect(this->serverConn, &ServerConnection::removedChangedProjectSuccess, this, &AdminMenu::slotRemoveChangeProjectCompleted);
        disconnect(this->serverConn, &ServerConnection::taskDataTableResult, this, &AdminMenu::slotTaskTableDataResult);
        disconnect(this->serverConn, &ServerConnection::empsForTaskDataTableResult, this, &AdminMenu::slotEmployeeForTaskTableDataResult);
        disconnect(this->serverConn, &ServerConnection::removedChangedTaskSuccess, this, &AdminMenu::slotRemoveChangeTaskCompleted);
        disconnect(this->serverConn, &ServerConnection::adminCloseRequestSuccess, this, &AdminMenu::slotCloseRequestCompleted);
        disconnect(this->serverConn, &ServerConnection::addProjectSuccess, this, &AdminMenu::slotAddProjectCompleted);
        disconnect(this->serverConn, &ServerConnection::addTaskSuccess, this, &AdminMenu::slotAddTaskCompleted);
        disconnect(this->serverConn, &ServerConnection::teamDataTableResult, this, &AdminMenu::slotTeamDataTableResult);
        disconnect(this->serverConn, &ServerConnection::onlineDataTableResult, this, &AdminMenu::slotOnlineDataTableResult);
        emit returnToAutorization();
        this->close();
    }
}

void AdminMenu::on_pushButton_addNewEmployee_clicked()
{
    QLineEdit* lineEdits[] = {
        ui->lineEdit_FirstName_add,
        ui->lineEdit_LastName_add,
        ui->lineEdit_MiddleName_add,
        ui->lineEdit_JobTitle_add,
        ui->lineEdit_PersonnelNumber_add,
        ui->lineEdit_ContactInformation_add,
        ui->lineEdit_AdditionalInfo_add,
        ui->lineEdit_login_add,
        ui->lineEdit_pswd_add
    };

    QStringList new_employee_data;
    bool allFieldsFilled = true;

    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text().isEmpty() && lineEdit != lineEdits[2] && lineEdit != lineEdits[6]) {
            allFieldsFilled = false;
            break;
        }
    }

    if (allFieldsFilled) {
        for (QLineEdit* lineEdit : lineEdits) {
            new_employee_data << lineEdit->text();
        }
        serverConn->sendRegistrationData(new_employee_data);
    } else {
        QMessageBox::warning(this, "Добавление нового сотрудника", "Ошибка! Заполните все выделенные цветом поля, необходимые для добавления.");
    }
}

void AdminMenu::on_pushButton_removeEmployee_clicked()
{
    QString removedEmployeeID = ui->lineEdit_EmployeeID->text();
    if (removedEmployeeID == ""){
        QMessageBox::warning(this, "Удаление сотрудника", "Ошибка! Укажите ID удаляемого сотрудинка (красное поле).");
    }
    else{
        QMessageBox::StandardButton userChoice;
        userChoice = QMessageBox::question(this, "Удаление сотрудника", "Удаляя сотрудника, другие сотрудники потеряют доступ к задачам, связанным с данным сотрудником. "
                                                                        "ОБЯЗАТЕЛЬНО переназначьте сотрудника к связанным с удаленным сотрудником задачам!!! "
                                                                        "Также будут удалены все данные связанные с данным сотрудником!\n"
                                                                        "Вы запомнили? Продолжить?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (userChoice == QMessageBox::Yes) {
            serverConn->sendRemovedUserID(removedEmployeeID);
        }
    }
}

void AdminMenu::on_pushButton_changeEmployee_clicked()
{
    QString changedEmployeeID = ui->lineEdit_EmployeeID->text();
    if (changedEmployeeID == ""){
        QMessageBox::warning(this, "Изменение сотрудника", "Ошибка! Укажите ID изменяемого сотрудинка (красное поле).");
    }
    else{
        QLineEdit* lineEdits[] = {
            ui->lineEdit_FirstName_rem_ch,
            ui->lineEdit_LastName_rem_ch,
            ui->lineEdit_MiddleName_rem_ch,
            ui->lineEdit_JobTitle_rem_ch,
            ui->lineEdit_PersonnelNumber_rem_ch,
            ui->lineEdit_ContactInformation_rem_ch,
            ui->lineEdit_AdditionalInfo_rem_ch,
            ui->lineEdit_login_rem_ch,
            ui->lineEdit_pswd_rem_ch
        };

        QStringList change_data;
        bool allFieldsFilled = true;

        for (QLineEdit* lineEdit : lineEdits) {
            if (lineEdit->text().isEmpty() && lineEdit != lineEdits[2] && lineEdit != lineEdits[6]) {
                allFieldsFilled = false;
                break;
            }
        }

        if (allFieldsFilled) {
            for (QLineEdit* lineEdit : lineEdits) {
                change_data << lineEdit->text();
            }
            serverConn->sendChangedEmployeeData(changedEmployeeID, change_data);
        } else {
            QMessageBox::warning(this, "Изменение данных сотрудника", "Ошибка! Заполните все выделенные цветом поля, необходимые для изменения "
                                                                      "данных сотрудника (фиолетовые поля).\nЕсли какое-то из полей должно сохранить прежнее "
                                                                      "значение, то скопируйте значение из таблицы.");
        }
    }
}

void AdminMenu::on_pushButton_closeRequest_clicked()
{
    int rowCount = ui->tableView_empRequests->model()->rowCount();
    if (rowCount != 0){
        if (ui->textEdit->toPlainText().isEmpty())
        {
            QMessageBox::warning(this, "Внимание", "Поле ответа на запрос не может быть пустым!");
            return;
        }
        serverConn->sendCloseRequest(ui->comboBox_requestID->currentText().toInt(), ui->comboBox_requestStatus->currentText(), ui->textEdit->toPlainText());
        QMessageBox::information(this, "Информация", "Ответ на запрос был успешно отправлен!");
        ui->textEdit->setText("");
        ui->comboBox_requestID->setCurrentIndex(0);
        ui->comboBox_requestStatus->setCurrentIndex(0);
    }
    else
    {
        QMessageBox::information(this, "Информация", "Запросы от сотрудников отсутствуют! Отвечать не на что.");
    }
}

void AdminMenu::on_pushButton_add_man_clicked()
{
    QString UpEmployeeID = ui->lineEdit_EmployeeID_add_man->text();
    QString JobTitleEmployee = ui->lineEdit_JobTitle_add_man->text();
    if (UpEmployeeID == ""){
        QMessageBox::warning(this, "Повышение сотрудника", "Ошибка! Укажите ID сотрудинка для повышения.");
    }
    else{
        if (JobTitleEmployee == ""){
            QMessageBox::warning(this, "Повышение сотрудника", "Ошибка! Укажите новую должность сотрудинка как руководителя, либо оставьте прежнюю должность, "
                                 "скопировав её из таблицы.");
        }
        else{
            serverConn->sendAddAdmin(UpEmployeeID, JobTitleEmployee);
        }
    }
}

void AdminMenu::on_pushButton_remove_man_clicked()
{
    QString removedManID = ui->lineEdit_ManID_remove_man->text();
    if (removedManID == ""){
        QMessageBox::warning(this, "Удаление руководителя", "Ошибка! Укажите ID удаляемого руководителя (красное поле).");
    }
    else{
        QMessageBox::StandardButton userChoice;
        userChoice = QMessageBox::question(this, "Удаление руководителя", "Удаляя руководителя, проект не сможет больше редактироваться! ОБЯЗАТЕЛЬНО переназначьте "
                                                                          "руководителя к проектам, если это нужно!!! "
                                                                          "Вы запомнили?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (userChoice == QMessageBox::Yes) {
            serverConn->sendRemovedAdminID(removedManID);
        }
    }
}

void AdminMenu::on_pushButton_change_man_clicked()
{
    QString changedManagerID = ui->lineEdit_ManID_remove_man->text();
    if (changedManagerID == ""){
        QMessageBox::warning(this, "Изменение сотрудника", "Ошибка! Укажите ID изменяемого руководителя (красное поле).");
    }
    else{
        QLineEdit* lineEdits[] = {
            ui->lineEdit_JobTitle_change_man,
            ui->lineEdit_ContactInf_change_man,
        };

        QStringList change_data;
        bool allFieldsFilled = true;

        for (QLineEdit* lineEdit : lineEdits) {
            if (lineEdit->text().isEmpty()) {
                allFieldsFilled = false;
                break;
            }
        }

        if (allFieldsFilled) {
            for (QLineEdit* lineEdit : lineEdits) {
                change_data << lineEdit->text();
            }
            serverConn->sendChangedAdminData(changedManagerID, change_data);
        } else {
            QMessageBox::warning(this, "Изменение данных руководителя", "Ошибка! Заполните все выделенные цветом поля, необходимые для изменения "
                                                                      "данных руководителя (фиолетовые поля).\nЕсли какое-то из полей должно сохранить прежнее "
                                                                      "значение, то скопируйте значение из таблицы.");
        }
    }
}

void AdminMenu::on_pushButton_add_project_clicked()
{
    QString projectManagerID = ui->comboBox_ProjectManagerID->currentText();
    QString projectName = ui->textEdit_project_name->toPlainText();
    QString projectDescription = ui->textEdit_project_description->toPlainText();
    if (projectManagerID == ""){
        QMessageBox::warning(this, "Добавление проекта", "Нельзя добавить новый проект, не имея руководителей, управляющих проектами.");
        return;
    }
    else if (projectName == ""){
        QMessageBox::warning(this, "Добавление проекта", "Ошибка! Укажите название нового проекта.");
    }
    else if (projectDescription == ""){
        QMessageBox::warning(this, "Добавление проекта", "Ошибка! Укажите описание нового проекта.");
    }
    else {
        serverConn->sendNewProjectData(projectManagerID, projectName, projectDescription);
        QMessageBox::information(this, "Информация", "Проект был успешно добавлен в разработку.");
        ui->textEdit_project_name->setText("");
        ui->textEdit_project_description->setText("");
        ui->comboBox_ProjectManagerID->setCurrentText(0);
    }
}

void AdminMenu::on_pushButton_remove_project_clicked()
{
    QString removedProjectID = ui->comboBox_IDProject->currentText();
    if (removedProjectID == ""){
        QMessageBox::warning(this, "Удаление проекта", "Ошибка! Укажите ID удаляемого проекта.");
    }
    else{
        QMessageBox::StandardButton userChoice;
        userChoice = QMessageBox::question(this, "Удаление проекта", "Удаляя проект, который находится в статусе 'В разработке...', также будут удалены все задачи, "
                                                                     "связанные с ним, а также любая другая информация. Проекты в статусе 'Завершено' и 'Не завершено' удалить не "
                                                                     "получится. Проверьте статус проекта. Вы согласны?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (userChoice == QMessageBox::Yes) {
            serverConn->sendRemovedProjectID(removedProjectID);
            ui->textEdit_newProjectName->setText("");
            ui->textEdit_newProjectDescription->setText("");
            ui->comboBox_IDProject->setCurrentText(0);
        }
    }
}

void AdminMenu::on_pushButton_change_project_clicked()
{
    QString changedProjectID = ui->comboBox_IDProject->currentText();
    if (changedProjectID == ""){
        QMessageBox::warning(this, "Изменение проекта", "Ошибка! Укажите ID изменяемого проекта.");
    }
    else{
        QString newProjectName = ui->textEdit_newProjectName->toPlainText(),
            newProjectDescription = ui->textEdit_newProjectDescription->toPlainText();
        if (newProjectName != "" && newProjectDescription != "") {
            QMessageBox::information(this, "Информация", "Проект был успешно изменен.");
            serverConn->sendChangedProjectData(changedProjectID, newProjectName, newProjectDescription);
            ui->textEdit_newProjectName->setText("");
            ui->textEdit_newProjectDescription->setText("");
            ui->comboBox_IDProject->setCurrentText(0);
        } else {
            QMessageBox::warning(this, "Изменение данных проекта", "Ошибка! Заполните все поля, необходимые для изменения "
                                                                      "данных проекта.\nЕсли какое-то из полей должно сохранить прежнее "
                                                                      "значение, то скопируйте значение из таблицы.");
        }
    }
}


void AdminMenu::on_pushButton_add_task_clicked()
{
    QString
        projectID =  ui->comboBox_task_project_id->currentText(),
        empID = ui->comboBox_task_emp_id->currentText(),
        taskName = ui->lineEdit_task_name->text(),
        taskDescription = ui->textEdit_task_description->toPlainText();
    if (projectID == "" || empID == "" || taskName == ""  || taskDescription == ""){
        QMessageBox::warning(this, "Добавление задачи", "Ошибка! Либо в системе недостаточно данных для добавления новой задачи, либо Вы не заполнили всю информацию, что есть на Вашем экране.");
    }
    else{
        QStringList add_data;
        add_data << projectID << empID << taskName << taskDescription;
        serverConn->sendAddTaskData(add_data);
        ui->comboBox_task_project_id->setCurrentIndex(0);
        ui->comboBox_task_emp_id->setCurrentIndex(0);
        ui->lineEdit_task_name->setText("");
        ui->textEdit_task_description->setText("");
    }
}


void AdminMenu::on_pushButton_change_task_clicked()
{
    QString changeTaskID = ui->comboBox_task_id->currentText();
    if (changeTaskID == ""){
        QMessageBox::warning(this, "Изменение задачи", "Ошибка! Укажите ID изменяемой задачи.");
    }
    else{
        QString newTaskName = ui->lineEdit_change_task_name->text(),
            newTaskDescription = ui->textEdit_task_change_description->toPlainText();
        if (newTaskName != "" && newTaskDescription != "") {
            QMessageBox::information(this, "Информация", "Задача была успешно изменена.");
            serverConn->sendChangedTaskData(changeTaskID, newTaskName, newTaskDescription);
            ui->lineEdit_change_task_name->setText("");
            ui->textEdit_task_change_description->setText("");
            ui->comboBox_task_id->setCurrentText(0);
        } else {
            QMessageBox::warning(this, "Изменение данных задачи", "Ошибка! Заполните все поля, необходимые для изменения "
                                                                   "данных задачи.\nЕсли какое-то из полей должно сохранить прежнее "
                                                                   "значение, то скопируйте значение из таблицы.");
        }
    }
}


void AdminMenu::on_pushButton_remove_task_clicked()
{
    QString removedTaskID = ui->comboBox_task_id->currentText();
    if (removedTaskID == ""){
        QMessageBox::warning(this, "Удаление задачи", "Ошибка! Укажите ID удаляемой задачи.");
    }
    else{
        QMessageBox::StandardButton userChoice;
        userChoice = QMessageBox::question(this, "Удаление задачи", "Задачи в статусе 'Завершено' и 'Не завершено' удалить не "
                                                                    "получится, для удаления доступны только задачи статуса 'В разработке...'. "
                                                                    "Проверьте статус задачи. Вы согласны?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (userChoice == QMessageBox::Yes) {
            serverConn->sendRemovedTaskID(removedTaskID);
            ui->lineEdit_change_task_name->setText("");
            ui->textEdit_task_change_description->setText("");
            ui->comboBox_task_id->setCurrentText(0);
        }
    }
}


void AdminMenu::on_pushButton_project_work_clicked()
{
    QString workProjectID = ui->comboBox_IDProject->currentText();
    if (workProjectID == ""){
        QMessageBox::warning(this, "Выведение проекта в работу", "Ошибка! Укажите ID выводимого проекта.");
    }
    else{
        QMessageBox::StandardButton userChoice;
        userChoice = QMessageBox::question(this, "Выведение проекта в работу", "Выводя проект в работу, также будут выведены в работу все проектные задачи"
                                                                               "(Они имеют статус 'В разработке...'), связанные с ним.\n"
                                                                               "Вы не сможете удалить проект в дальнейшем, а также связанные с ним проектные задачи. Вы уверены?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (userChoice == QMessageBox::Yes) {
            serverConn->sendWorkedProjectID(workProjectID);
            ui->textEdit_newProjectName->setText("");
            ui->textEdit_newProjectDescription->setText("");
            ui->comboBox_IDProject->setCurrentText(0);
        }
    }
}


void AdminMenu::on_pushButton_task_work_clicked()
{
    QString workTaskID = ui->comboBox_task_id->currentText();
    if (workTaskID == ""){
        QMessageBox::warning(this, "Выведение задачи в работу", "Ошибка! Укажите ID выводимой задачи.");
    }
    else{
        QMessageBox::StandardButton userChoice;
        userChoice = QMessageBox::question(this, "Выведение задачи в работу", "Выводя задачу в работу, также будет выведен в работу проект, который относится к данной задаче, если он "
                                                                              "имел статус 'В разработке...'.\n"
                                                                              "Вы не сможете удалить задачу в дальнейшем, а также связанную с ней информацию. Вы уверены?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (userChoice == QMessageBox::Yes) {
            serverConn->sendWorkedTaskID(workTaskID);
            ui->lineEdit_change_task_name->setText("");
            ui->textEdit_task_change_description->setText("");
            ui->comboBox_task_id->setCurrentText(0);
        }
    }
}


void AdminMenu::on_pushButton_newProjectMan_clicked()
{
    QString projectManagerID = ui->comboBox_ProjectManagerID->currentText();
    QString projectID = ui->comboBox_projectID->currentText();
    if (projectManagerID == "" || projectID == ""){
        QMessageBox::warning(this, "Переназначение проекта", "Нельзя переназначить проект, не имея руководителей проектов или самих проектов.");
        return;
    }
    else {
        serverConn->sendNewProjectManagerForProjectData(projectManagerID, projectID);
        QMessageBox::information(this, "Информация", "Проект был успешно переназначен.");
        ui->textEdit_project_name->setText("");
        ui->textEdit_project_description->setText("");
        ui->comboBox_ProjectManagerID->setCurrentText(0);
        ui->comboBox_projectID->setCurrentText(0);
    }
}


void AdminMenu::on_pushButton_newEmployeeForTask_clicked()
{
    QString employeeID = ui->comboBox_task_emp_id->currentText();
    QString taskID = ui->comboBox_task2_id->currentText();
    if (employeeID == "" || taskID == ""){
        QMessageBox::warning(this, "Переназначение задачи", "Нельзя переназначить задачу, не имея сотрудников или самих задач.");
        return;
    }
    else {
        serverConn->sendNewEmployeeForTaskData(employeeID, taskID);
        QMessageBox::information(this, "Информация", "Задача была успешно переназначена.");
        ui->comboBox_task_project_id->setCurrentText(0);
        ui->comboBox_task_emp_id->setCurrentText(0);
        ui->comboBox_task2_id->setCurrentText(0);
        ui->lineEdit_task_name->setText("");
        ui->textEdit_task_description->setText("");
    }
}

void AdminMenu::slotGetAdminCredentialsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> credentials_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = credentials_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
        }
    }
    ui->tableView_managerCredentials->setModel(model);
    ui->tableView_managerCredentials->resizeColumnsToContents();
    ui->tableView_managerCredentials->show();
    serverConn->getAdminCompleteProjects(type_admin);
}


void AdminMenu::on_pushButton_hideCredentials_clicked()
{
    if (ui->tableView_managerCredentials->isVisible()){
        ui->tableView_managerCredentials->hide();
        ui->pushButton_hideCredentials->setText("Показать");
    }
    else{
        ui->tableView_managerCredentials->show();
        ui->pushButton_hideCredentials->setText("Скрыть");
    }
}

void AdminMenu::slotGetAdminEmployeeWeekendsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> weekends_data)
{
    ui->comboBox_WeekendID->clear();
    ui->comboBox_WeekendID->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    QColor beginColor(0, 128, 0);
    QColor endColor(0, 0, 128);
    int weekendIDColumn = headerLabels.indexOf("ID отпуска");
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            QString value = weekends_data[i][j];
            if (value.isNull())
                value = "Выходной";
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == weekendIDColumn){
                ui->comboBox_WeekendID->addItem(value);
                model->setData(index, QColor(0,0,130), Qt::ForegroundRole);
            }
            else{
                if (headerLabels[j].contains("Начало")) {
                    model->setData(index, beginColor, Qt::ForegroundRole);
                } else if (headerLabels[j].contains("Конец")) {
                    model->setData(index, endColor, Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_empWeekends->setModel(model);
    ui->tableView_empWeekends->resizeColumnsToContents();
    ui->comboBox_WeekendID->setCurrentIndex(0);
    //Установка данных в dateEdit.
    ui->dateEdit_WeekendBegin->setDate(QDate::currentDate());
    ui->dateEdit_WeekendEnd->setDate(QDate::currentDate());
    ui->textEdit_NoteForWeekend->clear();
    ui->tableView_empWeekends->show();
}

void AdminMenu::slotGetAdminEmployeeGrafsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> grafs_data)
{
    ui->comboBox_grafID->clear();
    ui->comboBox_grafID->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    QColor beginColor(0, 128, 0);
    QColor endColor(0, 0, 128);
    int grafIDColumn = headerLabels.indexOf("ID графика");
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            QString value = grafs_data[i][j];
            if (value.isNull())
                value = "Выходной";
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == grafIDColumn){
                ui->comboBox_grafID->addItem(value);
                model->setData(index, QColor(0,0,130), Qt::ForegroundRole);
            }
            else{
                if (value != "Выходной"){
                    if (headerLabels[j].contains("Начало")) {
                        model->setData(index, beginColor, Qt::ForegroundRole);
                    } else if (headerLabels[j].contains("Конец")) {
                        model->setData(index, endColor, Qt::ForegroundRole);
                    }
                }
                else{
                    model->setData(index, QColor(128, 0, 0), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_empGrafs->setModel(model);
    ui->tableView_empGrafs->resizeColumnsToContents();
    ui->tableView_empGrafs->show();
    ui->comboBox_grafID->setCurrentIndex(0);
    //Установка данных в dateTimeEdit.
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int dayOfWeek = currentDateTime.date().dayOfWeek();
    int daysToAdd = 1 - dayOfWeek; // Находим разницу между текущим днем недели и понедельником.
    // Устанавливаем начальную дату текущей недели.
    QDateTime mondayBegin = currentDateTime.addDays(daysToAdd);
    mondayBegin.setTime(QTime(0, 0)); // Устанавливаем время на начало дня (00:00).
    // Устанавливаем конечную дату текущей недели (воскресенье)
    QDateTime sundayEnd = mondayBegin.addDays(6);
    sundayEnd.setTime(QTime(23, 59, 00));
    // Устанавливаем значения для каждого dateTimeEdit
    ui->dateTimeEdit_MondayBegin->setDateTime(mondayBegin);
    ui->dateTimeEdit_MondayEnd->setDateTime(sundayEnd.addDays(-6));
    ui->dateTimeEdit_TuesdayBegin->setDateTime(mondayBegin.addDays(1));
    ui->dateTimeEdit_TuesdayEnd->setDateTime(sundayEnd.addDays(-5));
    ui->dateTimeEdit_WednesdayBegin->setDateTime(mondayBegin.addDays(2));
    ui->dateTimeEdit_WednesdayEnd->setDateTime(sundayEnd.addDays(-4));
    ui->dateTimeEdit_ThursdayBegin->setDateTime(mondayBegin.addDays(3));
    ui->dateTimeEdit_ThursdayEnd->setDateTime(sundayEnd.addDays(-3));
    ui->dateTimeEdit_FridayBegin->setDateTime(mondayBegin.addDays(4));
    ui->dateTimeEdit_FridayEnd->setDateTime(sundayEnd.addDays(-2));
    ui->dateTimeEdit_SaturdayBegin->setDateTime(mondayBegin.addDays(5));
    ui->dateTimeEdit_SaturdayEnd->setDateTime(sundayEnd.addDays(-1));
    ui->dateTimeEdit_SundayBegin->setDateTime(mondayBegin.addDays(6));
    ui->dateTimeEdit_SundayEnd->setDateTime(sundayEnd);

    serverConn->getAdminEmployeeWeekends(type_admin);
}

void AdminMenu::slotGetAdminEmployeeDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data)
{
    ui->comboBox_empID->clear();
    ui->comboBox_empID->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int employeeIDColumn= headerLabels.indexOf("ID сотрудника");
    int statusColumn = headerLabels.indexOf("Статус сотрудника");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = employees_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == employeeIDColumn){
                model->setData(index, QColor(0, 0, 130), Qt::ForegroundRole);
                ui->comboBox_empID->addItem(value);
            }
            if (j == statusColumn){
                if (value == "Онлайн"){
                    model->setData(index, QColor(0, 130, 0), Qt::ForegroundRole);
                }
                else if (value == "Оффлайн"){
                    model->setData(index, QColor(130, 0, 0), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_empList->setModel(model);
    ui->tableView_empList->resizeColumnsToContents();
    ui->tableView_empList->show();
    ui->comboBox_empID->setCurrentIndex(0);
    serverConn->getAdminEmployeeGrafs(type_admin);
}

void AdminMenu::slotGetAdminCompleteProjectTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int projTaskIDColumn= headerLabels.indexOf("ID проектной задачи");
    int statusColumn = headerLabels.indexOf("Статус проектной задачи");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = complete_tasks_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == projTaskIDColumn){
                model->setData(index, QColor(0, 0, 130), Qt::ForegroundRole);
            }
            if (j == statusColumn){
                if (value == "Завершено"){
                    model->setData(index, QColor(0, 130, 0), Qt::ForegroundRole);
                }
                else{
                    model->setData(index, QColor(130, 0, 0), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_completeProjectTasks->setModel(model);
    ui->tableView_completeProjectTasks->resizeColumnsToContents();
    ui->tableView_completeProjectTasks->show();
}

void AdminMenu::slotUpdateProjectTasksTable(int selected_index)
{
    if (selected_index >= 0){
        serverConn->getAdminCompleteProjTasks(ui->comboBox_projID->currentText());
    }
}

void AdminMenu::slotGetAdminCompleteProjectsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_projs_data)
{
    ui->comboBox_projID->clear();
    ui->comboBox_projID->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int projIDColumn= headerLabels.indexOf("ID проекта");
    int statusColumn = headerLabels.indexOf("Статус проекта");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = complete_projs_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == projIDColumn){
                ui->comboBox_projID->addItem(value);
                model->setData(index, QColor(0, 0, 130), Qt::ForegroundRole);
            }
            if (j == statusColumn){
                if (value == "Завершено"){
                    model->setData(index, QColor(0, 130, 0), Qt::ForegroundRole);
                }
                else{
                    model->setData(index, QColor(130, 0, 0), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_completeProjects->setModel(model);
    ui->tableView_completeProjects->resizeColumnsToContents();
    ui->tableView_completeProjects->show();
    ui->comboBox_projID->setCurrentIndex(0);
}


void AdminMenu::on_pushButton_addGraf_clicked()
{
    if (ui->comboBox_empID->currentText() == ""){
        QMessageBox::warning(this, "Добавление графика сотрудника", "Для того, чтобы добавить график сотрудника, необходимо выбрать ID сотрудника."
                                                                    " Затем настроить в верхней левой части окна график и нажать кнопку Добавить.\n\n"
                                                                    "Для указания выходных дней, используйте одинаковые дату и время в начале и конце рабочего дня.");
    }
    else {
        QStringList workSchedule;
        // Понедельник
        workSchedule << ui->dateTimeEdit_MondayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_MondayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Вторник
        workSchedule << ui->dateTimeEdit_TuesdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_TuesdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Среда
        workSchedule << ui->dateTimeEdit_WednesdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_WednesdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Четверг
        workSchedule << ui->dateTimeEdit_ThursdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_ThursdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Пятница
        workSchedule << ui->dateTimeEdit_FridayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_FridayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Суббота
        workSchedule << ui->dateTimeEdit_SaturdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_SaturdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Воскресенье
        workSchedule << ui->dateTimeEdit_SundayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_SundayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Запрос
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение добавления", "Вы уверены, что хотите добавить график сотрудника? Прочитайте справку.",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminWorkWithGraf("Добавить", ui->comboBox_empID->currentText(), workSchedule);
        }
    }
}


void AdminMenu::on_pushButton_changeGraf_clicked()
{
    if (ui->comboBox_grafID->currentText() == ""){
        QMessageBox::warning(this, "Изменение графика сотрудника", "Для того, чтобы изменить график сотрудника, необходимо выбрать ID графика."
                                                                    " Затем настроить в верхней левой части окна график и нажать кнопку Изменить.\n\n"
                                                                    "Для указания выходных дней, используйте одинаковые дату и время в начале и конце рабочего дня.");
    }
    else{
        QStringList workSchedule;
        // Понедельник
        workSchedule << ui->dateTimeEdit_MondayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_MondayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Вторник
        workSchedule << ui->dateTimeEdit_TuesdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_TuesdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Среда
        workSchedule << ui->dateTimeEdit_WednesdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_WednesdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Четверг
        workSchedule << ui->dateTimeEdit_ThursdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_ThursdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Пятница
        workSchedule << ui->dateTimeEdit_FridayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_FridayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Суббота
        workSchedule << ui->dateTimeEdit_SaturdayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_SaturdayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Воскресенье
        workSchedule << ui->dateTimeEdit_SundayBegin->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        workSchedule << ui->dateTimeEdit_SundayEnd->dateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz");
        // Запрос
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение изменения", "Вы уверены, что хотите изменить график сотрудника? Прочитайте справку.",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminWorkWithGraf("Изменить", ui->comboBox_grafID->currentText(), workSchedule);
        }
    }
}

void AdminMenu::on_pushButton_remGraf_clicked()
{
    if (ui->comboBox_grafID->currentText() == ""){
        QMessageBox::warning(this, "Удаление графика сотрудника", "Для того, чтобы удалить график сотрудника, необходимо выбрать ID графика."
                                                                  " Затем нажать кнопку Удалить.");
    }
    else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение удаления", "Вы уверены, что хотите удалить график сотрудника? Прочитайте справку.",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminRemoveGraf(ui->comboBox_grafID->currentText());
        }
    }
}


void AdminMenu::on_pushButton_addWeekend_clicked()
{
    if (ui->comboBox_empID->currentText() == ""){
        QMessageBox::warning(this, "Добавление отпуска сотрудника", "Для того, чтобы добавить отпуск сотрудника, необходимо выбрать ID сотрудника."
                                                                    " Затем настроить в нижней правой части окна отпуск и нажать кнопку Добавить.");
    }
    else{
        QString WeekendBegin = ui->dateEdit_WeekendBegin->dateTime().toString("yyyy-MM-dd");
        QString WeekendEnd = ui->dateEdit_WeekendEnd->dateTime().toString("yyyy-MM-dd");
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение добавления", "Вы уверены, что хотите добавить отпуск сотрудника? Прочитайте справку.",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminWorkWithWeekend("Добавить", ui->comboBox_empID->currentText(), WeekendBegin, WeekendEnd,
                                                 ui->textEdit_NoteForWeekend->toPlainText());
        }
    }
}


void AdminMenu::on_pushButton_remWeekend_clicked()
{
    if (ui->comboBox_WeekendID->currentText() == ""){
        QMessageBox::warning(this, "Удаление отпуска сотрудника", "Для того, чтобы удалить отпуск сотрудника, необходимо выбрать ID отпуска."
                                                                  " Затем нажать кнопку Удалить.");
    }
    else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение удаления", "Вы уверены, что хотите удалить отпуск сотрудника? Прочитайте справку.",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminRemoveWeekend(ui->comboBox_WeekendID->currentText());
        }
    }
}


void AdminMenu::on_pushButton_changeWeekend_clicked()
{
    if (ui->comboBox_WeekendID->currentText() == ""){
        QMessageBox::warning(this, "Изменение отпуска сотрудника", "Для того, чтобы изменить отпуск сотрудника, необходимо выбрать ID отпуска."
                                                                   " Затем настроить в нижней правой части окна отпуск и нажать кнопку Изменить.");
    }
    else{
        QString WeekendBegin = ui->dateEdit_WeekendBegin->date().toString("yyyy-MM-dd");
        QString WeekendEnd = ui->dateEdit_WeekendEnd->date().toString("yyyy-MM-dd");
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение изменения", "Вы уверены, что хотите изменить отпуск сотрудника? Прочитайте справку.",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminWorkWithWeekend("Изменить", ui->comboBox_WeekendID->currentText(),
                                                 WeekendBegin, WeekendEnd, ui->textEdit_NoteForWeekend->toPlainText());
        }
    }
}

void AdminMenu::slotGetAdminRemoveWeekendResult(bool access)
{
    if (access){
        QMessageBox messageBox;
        messageBox.setWindowTitle("Удаление отпуска сотрудника");
        messageBox.setText("Отпуск сотрудника был успешно удален из системы.");
        if (messageBox.exec() == QMessageBox::Ok){
            serverConn->getAdminEmployeeData(type_admin);
        }
    }
    else{
        //Обработка в случае некорректного удаления отпуска сотрудника.
    }
}

void AdminMenu::slotGetAdminWorkWithWeekendResult(QString action, bool access)
{
    if (action == "Добавить"){
        if (access){
            QMessageBox messageBox;
            messageBox.setWindowTitle("Добавление отпуска сотрудника");
            messageBox.setText("Отпуск сотрудника был успешно добавлен в систему.");
            if (messageBox.exec() == QMessageBox::Ok){
                serverConn->getAdminEmployeeData(type_admin);
            }
        }
        else{
            //Обработка в случае некорректного добавления отпуска сотрудника.
        }
    }
    else if (action == "Изменить"){
        if (access){
            QMessageBox messageBox;
            messageBox.setWindowTitle("Изменение отпуска сотрудника");
            messageBox.setText("Отпуск сотрудника был успешно изменен в системе.");
            if (messageBox.exec() == QMessageBox::Ok){
                serverConn->getAdminEmployeeData(type_admin);
            }
        }
        else{
            //Обработка в случае некорректного изменения отпуска сотрудника.
        }
    }
}

void AdminMenu::slotGetAdminRemoveGrafResult(bool access)
{
    if (access){
        QMessageBox messageBox;
        messageBox.setWindowTitle("Удаление графика сотрудника");
        messageBox.setText("График сотрудника был успешно удален из системы.");
        if (messageBox.exec() == QMessageBox::Ok){
            serverConn->getAdminEmployeeData(type_admin);
        }
    }
    else{
        //Обработка в случае некорректного удаления графика сотрудника.
    }
}

void AdminMenu::slotGetAdminWorkWithGrafResult(QString action, bool access)
{
    if (action == "Добавить"){
        if (access){
            QMessageBox messageBox;
            messageBox.setWindowTitle("Добавление графика сотрудника");
            messageBox.setText("График сотрудника был успешно добавлен в систему.");
            if (messageBox.exec() == QMessageBox::Ok){
                serverConn->getAdminEmployeeData(type_admin);
            }
        }
        else{
            //Обработка в случае некорректного добавления графика сотрудника.
        }
    }
    else if (action == "Изменить"){
        if (access){
            QMessageBox messageBox;
            messageBox.setWindowTitle("Изменение графика сотрудника");
            messageBox.setText("График сотрудника был успешно изменен в системе.");
            if (messageBox.exec() == QMessageBox::Ok){
                serverConn->getAdminEmployeeData(type_admin);
            }
        }
        else{
            //Обработка в случае некорректного изменения графика сотрудника.
        }
    }
}


void AdminMenu::on_pushButton_getInfo_clicked()
{
    QMessageBox::information(this, "СПРАВКА",
                             "*Добавление графика сотрудника*\n"
                             "Для того, чтобы добавить график сотрудника, вам необходимо:\n"
                             "- выбрать ID сотрудника;\n"
                             "- определить его график, тщательно проанализировав выставляемые дату и время (в случае каких-то несостыковок в графике, "
                             "а именно нахождении сотрудника в онлайне в данный момент или изменении графика текущего рабочего дня и тп, учет времени "
                             "сотрудника может сильно исказиться, поэтому учитывайте, что данная версия приложения ITimeTracker полностью снимает с себя "
                             "ответственность за подобные ситуации и не предоставляет корректной возможности ее исправления);\n"
                             "- в случае необходимости выставления выходных дней, указывайте одинаковые начало и окончание рабочего дня (либо изменяйте "
                             "концы рабочих дней значений по умолчанию - текущая дата и время без учета секунд);\n"
                             "- нажмите кнопку ДОБАВИТЬ под таблицей с графиками сотрудников.\n\n"
                             "*Изменение графика сотрудника*\n"
                             "Аналогично добавлению графика, выберите ID графика, настройте график и нажмите кнопку ИЗМЕНИТЬ под таблицей с "
                             "графиками сотрудников.\n\n"
                             "*Удаление графика сотрудника*\n"
                             "- выберите ID графика;\n"
                             "- нажмите кнопку УДАЛИТЬ под таблицей с графиками сотрудников.\n\n"
                             "*Добавление отпуска сотрудника*\n"
                             "- выберите ID сотрудника;\n"
                             "- определите время его отпуска, тщательно проанализиров выставляемые даты (ситуация аналогична графику);"
                             "- нажмите кнопку ДОБАВИТЬ под таблицей с отпусками сотрудников.\n\n"
                             "*Изменение отпуска сотрудника*\n"
                             "Аналогично добавлению отпуска, выберите ID отпуска, настройте отпуск и нажмите кнопку ИЗМЕНИТЬ под таблицей с "
                             "отпусками сотрудников,\n\n"
                             "*Удаление отпуска сотрудника*\n"
                             "- выберите ID отпуска;\n"
                             "- нажмите кнопку УДАЛИТЬ под таблицей с отпусками сотрудников.\n\n"
                             "Также учитывайте, что важно, чтобы день недели (ПН, ВТ, СР, ..., ВС) и дата по каледарю совпадали! По умолчанию даты стоят корректно.\n\n\n"
                             "C уважением, команда ITimeTracker");
}

void AdminMenu::slotGetAdminAnomalyDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> anomalies_data)
{
    ui->comboBox_anomalyID->clear();
    ui->comboBox_anomalyID->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int anomalyIDColumn= headerLabels.indexOf("ID аномалии");
    int descrColumn = headerLabels.indexOf("Описание аномалии");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = anomalies_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == anomalyIDColumn){
                ui->comboBox_anomalyID->addItem(value);
                model->setData(index, QColor(0, 0, 130), Qt::ForegroundRole);
            }
            else if (j == descrColumn){
                model->setData(index, QColor(130, 0, 0), Qt::ForegroundRole);
            }
        }
    }
    ui->tableView_anomalyTimeTable->setModel(model);
    ui->tableView_anomalyTimeTable->resizeColumnsToContents();
    ui->tableView_anomalyTimeTable->show();
    ui->comboBox_anomalyID->setCurrentIndex(0);
}

void AdminMenu::slotAdminUpdateAnomalyTable(int selected_index)
{
    if (selected_index >= 0){
        serverConn->sendAdminAnomalyData(ui->comboBox_empIDForAnomaly->currentText());
    }
}

void AdminMenu::slotAdminEmployeeTableForAnomalyResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data)
{
    ui->comboBox_empIDForAnomaly->clear();
    ui->comboBox_empIDForAnomaly->setMaxVisibleItems(6);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int employeeIDColumn= headerLabels.indexOf("ID сотрудника");
    int statusColumn = headerLabels.indexOf("Статус сотрудника");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = employees_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == employeeIDColumn){
                model->setData(index, QColor(0, 0, 130), Qt::ForegroundRole);
                ui->comboBox_empIDForAnomaly->addItem(value);
            }
            if (j == statusColumn){
                if (value == "Онлайн"){
                    model->setData(index, QColor(0, 130, 0), Qt::ForegroundRole);
                }
                else if (value == "Оффлайн"){
                    model->setData(index, QColor(130, 0, 0), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_EmployeeTable->setModel(model);
    ui->tableView_EmployeeTable->resizeColumnsToContents();
    ui->tableView_EmployeeTable->show();
    ui->comboBox_empIDForAnomaly->setCurrentIndex(0);
}


void AdminMenu::on_pushButton_remAnomaly_clicked()
{
    if (ui->comboBox_anomalyID->currentText() == ""){
        QMessageBox::warning(this, "Удаление аномалии сотрудника", "Для того, чтобы удалить аномалию сотрудника, необходимо выбрать ID аномалии."
                                                                   " Затем в нижней левой части окна нажать кнопку Удалить аномалию.");
    }
    else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение удаления", "Вы уверены, что хотите удалить аномалию сотрудника?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminRemoveAnomaly(ui->comboBox_anomalyID->currentText());
        }
    }
}

void AdminMenu::slotAdminRemoveAnomaly(bool access)
{
    if (access){
        QMessageBox messageBox;
        messageBox.setWindowTitle("Удалении аномалии времени сотрудника");
        messageBox.setText("Аномалия времени сотрудника была успешно удалена.");
        if (messageBox.exec() == QMessageBox::Ok){
            serverConn->getAdminEmployeeTableForAnomaly(type_admin);
        }
    }
    else{
        //Можно добавить дополнительную обработку для удаления аномалии времени сотрудника.
    }
}


void AdminMenu::on_pushButton_createReport_clicked()
{
    if (ui->comboBox_empIDForAnomaly->currentText() != ""){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение формирования отчета", "Вы уверены, что хотите сформировать отчет с указанными данными (ID сотрудника "
                                                                                 "и дата начала/конца формирования отчета)?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            serverConn->sendAdminSaveReport(ui->comboBox_empIDForAnomaly->currentText(), ui->dateEdit_ReportBegin->dateTime().toString("yyyy-MM-dd"),
                                            ui->dateEdit_ReportEnd->dateTime().toString("yyyy-MM-dd"));
        }
    }
    else{
        QMessageBox::warning(this, "Формирование отчета", "Для формирования отчета необходимо выбрать ID сотрудника.");
    }
}

void AdminMenu::slotAdminSaveReportResult(QString report)
{
    // Открываем диалоговое окно сохранения файла.
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить отчет"), "", tr("Text Files (*.txt);;All Files (*)"));
    // Проверяем, был ли выбран файл.
    if (fileName.isEmpty()) {
        QMessageBox::information(this, tr("Информация"), tr("Сохранение отменено."));
        return;
    }
    // Создаем файл и открываем его для записи.
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл для записи."));
        return;
    }
    // Записываем данные в файл.
    QTextStream out(&file);
    out << report;
    // Закрываем файл.
    file.close();
    // Информируем пользователя об успешном сохранении.
    QMessageBox::information(this, tr("Успех"), tr("Отчет успешно сохранен."));
}

