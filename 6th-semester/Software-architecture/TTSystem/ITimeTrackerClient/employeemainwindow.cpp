#include "employeemainwindow.h"
#include "ui_employeemainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QStandardItemModel>

//Глобальная переменная для хранения хука
HHOOK g_hKeyboardHook = NULL;
//Объявление глобальной переменной, которая применит хук к данному окну.
EmployeeMainWindow* g_pEmployeeMainWindow = nullptr;

EmployeeMainWindow::EmployeeMainWindow(ServerConnection* serverConn, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployeeMainWindow)
    , serverConn(serverConn)
    , allowWorkControl(true)
    , blockingLocation("")
{
    ui->setupUi(this);
    connect(serverConn, &ServerConnection::getEmployeeCreditalsDataResult, this, &EmployeeMainWindow::slotGetEmployeeCreditalsDataResult);
    connect(serverConn, &ServerConnection::getEmployeeCompleteTasksResult, this, &EmployeeMainWindow::slotGetEmployeeCompleteTasksResult);
    connect(serverConn, &ServerConnection::getEmployeeUnfinishedTasksResult, this, &EmployeeMainWindow::slotGetEmployeeUnfinishedTasksResult);
    connect(serverConn, &ServerConnection::getEmployeeTimeDataResult, this, &EmployeeMainWindow::slotGetEmployeeTimeData);
    connect(serverConn, &ServerConnection::getEmployeeWorkGrafResult, this, &EmployeeMainWindow::slotGetEmployeeWorkGrafResult);
    connect(serverConn, &ServerConnection::getEmployeeTableTimeAnomaliesResult, this, &EmployeeMainWindow::slotGetEmployeeTableTimeAnomaliesResult);
    connect(serverConn, &ServerConnection::getRequestCategoriesResult, this, &EmployeeMainWindow::slotGetRequestCategories);
    connect(serverConn, &ServerConnection::getEmployeeProjectsResult, this, &EmployeeMainWindow::slotGetEmployeeProjectsResult);
    connect(ui->comboBox_Projects, &QComboBox::currentIndexChanged, this, &EmployeeMainWindow::slotUpdateProjectDescription);
    connect(serverConn, &ServerConnection::getEmployeeProjectTasksResult, this, &EmployeeMainWindow::slotGetEmployeeProjectTasksResult);
    connect(ui->comboBox_ProjectTasks, &QComboBox::currentIndexChanged, this, &EmployeeMainWindow::slotUpdateProjectTaskDescription);
    connect(serverConn, &ServerConnection::getEmployeeReadyTaskRequestResult, this, &EmployeeMainWindow::slotGetReadyTaskRequestResult);
    connect(serverConn, &ServerConnection::getEmployeeTaskNotesResult, this, &EmployeeMainWindow::slotGetEmployeeTaskNotesResult);
    connect(serverConn, &ServerConnection::getEmployeeSaveTaskNotesResult, this, &EmployeeMainWindow::slotGetEmployeeSaveTaskNotesResult);
    connect(serverConn, &ServerConnection::getEmployeeRequestsDataResult, this, &EmployeeMainWindow::slotGetEmployeeRequestsDataResult);
    connect(ui->comboBox_requestCategoriesForCheck, &QComboBox::currentIndexChanged, this, &EmployeeMainWindow::slotUpdateEmployeeRequestsData);
    connect(serverConn, &ServerConnection::getEmployeeTableEmployeesDataResult, this, &EmployeeMainWindow::slotGetEmployeeTableEmployeesDataResult);
    //Сигнал-слоты для учета рабочего времени сотрудника при переключении на окна.
    connect(serverConn, &ServerConnection::readyTakeIntoMainTime, this, &EmployeeMainWindow::slotReadyTakeIntoMainTime);

    // Установка глобальной переменной на текущий экземпляр EmployeeMainWindow
    g_pEmployeeMainWindow = this;
    // Регистрация хука клавиатуры
    g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, reinterpret_cast<HOOKPROC>(&EmployeeMainWindow::KeyboardProc), GetModuleHandle(NULL), 0);

    ui->stackedWidget_emp_funcs->setCurrentIndex(0);
    serverConn->getEmployeeCreditalsData();
}

EmployeeMainWindow::~EmployeeMainWindow()
{
    // Удаление хука клавиатуры
    if (g_hKeyboardHook != NULL) {
        UnhookWindowsHookEx(g_hKeyboardHook);
    }

    // Сброс указателя на текущий экземпляр
    g_pEmployeeMainWindow = nullptr;
    delete ui;
}

// Функция обработки хука клавиатуры
LRESULT CALLBACK EmployeeMainWindow::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT *)lParam;
            if (kbdStruct->vkCode == 'L' && (GetKeyState(VK_LWIN) & 0x8000)) {
                if (g_pEmployeeMainWindow && !g_pEmployeeMainWindow->allowWorkControl && g_pEmployeeMainWindow->blockingLocation == "Task") {
                    g_pEmployeeMainWindow->allowWorkControl = true;
                    g_pEmployeeMainWindow->blockingLocation = "";
                    g_pEmployeeMainWindow->ui->statusBar_emp->showMessage("");
                    g_pEmployeeMainWindow->ui->statusBar_emp->repaint();
                    g_pEmployeeMainWindow->serverConn->sendEndSubmainTimeData("Закончить Выполнение проектной задачи");
                }
                HWND hwnd = FindWindow(NULL, L"EmployeeMainWindow");
                if (hwnd) {
                    PostMessage(hwnd, WM_HOTKEY, 1, 0);
                }
                return 1; // Заблокировать системное действие
            }
        }
    }
    return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}

void EmployeeMainWindow::on_action_common_statistic_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 0){
        ui->stackedWidget_emp_funcs->setCurrentIndex(0);
        serverConn->sendMainTimeData("Раздел Общая статистика");
    }
}


void EmployeeMainWindow::on_action_reg_time_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 1){
        ui->stackedWidget_emp_funcs->setCurrentIndex(1);
        serverConn->sendMainTimeData("Раздел Регистрация времени");
        ui->textEdit_regTimeInfo->setText("***Справка о регистрации времени***\n\n"
                                          "Регистрируемое время учитывается в системе, но выбор и продолжительность регистрируемого "
                                          "времени остается на Ваше усмотрение.\n\n"
                                          "⚙Обеденный перерыв и его продолжительность определяются Вашим руководством. Старайтесь соблюдать его согласно "
                                          "нормативным документам Вашей Компании.\n"
                                          "⚙Оффлайн/Онлайн совещания и их продолжительность определяются Вами. При необходимости принять участие в них "
                                          "регистрируйте время для объективности дальнейшей оценки руководством Вашего рабочего времени.\n"
                                          "⚙Отсутствие по рабочей причине может включать в себя учет всевозможных действий, необходимых для поддержания "
                                          "большей продуктивности на работе, например, обсуждения задач с коллегами или других вопросов.\n"
                                          "⚙Отсутствие по личной нужде включает в себя биологические потребности Вашего организма, необходимые "
                                          "для поддержания продуктивности на работе.");
    }
}

void EmployeeMainWindow::on_action_work_graf_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 2){
        ui->stackedWidget_emp_funcs->setCurrentIndex(2);
        serverConn->sendMainTimeData("Раздел Рабочий график");
    }
}


void EmployeeMainWindow::on_action_exception_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 3){
        ui->stackedWidget_emp_funcs->setCurrentIndex(3);
        serverConn->sendMainTimeData("Раздел Исключительные ситуации");
    }
}


void EmployeeMainWindow::on_action_work_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 4){
        ui->stackedWidget_emp_funcs->setCurrentIndex(4);
        serverConn->sendMainTimeData("Раздел Начать работу над проектами и задачами");
    }
}


void EmployeeMainWindow::on_action_sent_queries_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 5){
        ui->stackedWidget_emp_funcs->setCurrentIndex(5);
        serverConn->sendMainTimeData("Раздел Отправить запрос");
    }
}


void EmployeeMainWindow::on_action_got_queries_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 6){
        ui->stackedWidget_emp_funcs->setCurrentIndex(6);
        serverConn->sendMainTimeData("Раздел Просмотр запросов");
    }
}


void EmployeeMainWindow::on_action_users_triggered()
{
    if (this->allowWorkControl && ui->stackedWidget_emp_funcs->currentIndex() != 7){
        ui->stackedWidget_emp_funcs->setCurrentIndex(7);
        serverConn->sendMainTimeData("Раздел Просмотр активных пользователей");
    }
}


void EmployeeMainWindow::on_action_exit_triggered()
{
    this->close();
}

void EmployeeMainWindow::slotGetEmployeeWorkGrafResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> work_graf_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    QColor beginColor(0, 128, 0);
    QColor endColor(0, 0, 128);
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            QString value = work_graf_data[i][j];
            if (value.isNull())
                value = "Выходной";
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
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
    ui->tableView_workGraf->setModel(model);
    ui->tableView_workGraf->resizeColumnsToContents();
    ui->tableView_workGraf->show();
}

void EmployeeMainWindow::slotGetEmployeeTableTimeAnomaliesResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> time_anomalies_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int descrColumn = headerLabels.indexOf("Описание исключительной ситуации");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = time_anomalies_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == descrColumn){
                model->setData(index, QColor(204, 0, 0), Qt::ForegroundRole);
            }
        }
    }
    ui->tableView_anomalyTimeList->setModel(model);
    ui->tableView_anomalyTimeList->resizeColumnsToContents();
    ui->tableView_anomalyTimeList->show();
}

void EmployeeMainWindow::slotGetRequestCategories(QStringList categories)
{
    if (ui->stackedWidget_emp_funcs->currentIndex() == 5) {
        ui->comboBox_requestCategoriesForSend->clear();
        ui->comboBox_requestCategoriesForSend->setMaxVisibleItems(6);
        for (const QString &category : categories) {
            ui->comboBox_requestCategoriesForSend->addItem(category);
        }
        ui->comboBox_requestCategoriesForSend->setCurrentIndex(0);
    } else if (ui->stackedWidget_emp_funcs->currentIndex() == 6) {
        ui->comboBox_requestCategoriesForCheck->clear();
        ui->comboBox_requestCategoriesForCheck->setMaxVisibleItems(6);
        for (const QString &category : categories) {
            ui->comboBox_requestCategoriesForCheck->addItem(category);
        }
        ui->comboBox_requestCategoriesForCheck->setCurrentIndex(0);
    }
}

void EmployeeMainWindow::slotGetReadyTaskRequestResult(bool correct)
{
    if (!correct)
        QMessageBox::warning(this, "Ошибка выполнения отправки запроса", "Вы уже отправляли данный запрос в систему!\n"
                                                                         "Если администратор еще не ответил Вам, дождитесь ответа администратора. "
                                                                         "Иначе, в случае отрицательного ответа, повторите отправку запроса.\n\n"
                                                                         "***Если указанная задача имеет положительный статус, то Вы не сможете "
                                                                         "отправить запрос снова.");
    else
        QMessageBox::information(this, "Отправка запроса о выполнении проектной задачи", "Запрос о проверке готовности проектной задачи был успешно отправлен.");
}

void EmployeeMainWindow::slotGetEmployeeProjectsResult(QList<QStringList> projects)
{
    ui->comboBox_Projects->clear();
    ui->comboBox_Projects->setMaxVisibleItems(6);
    this->projects = projects;
    for (const QStringList& current_project : this->projects) {
        ui->comboBox_Projects->addItem(current_project.at(0));
    }
    ui->comboBox_Projects->setCurrentIndex(0);
}

void EmployeeMainWindow::slotGetEmployeeProjectTasksResult(QList<QStringList> proj_tasks)
{
    int progressPercent = 0, completedTasks = 0, totalTasks = proj_tasks.size();
    ui->comboBox_ProjectTasks->clear();
    ui->comboBox_ProjectTasks->setMaxVisibleItems(6);
    this->proj_tasks = proj_tasks;
    for (const QStringList& current_task : this->proj_tasks) {
        ui->comboBox_ProjectTasks->addItem(current_task.at(0));
        if (current_task.at(3) == "Завершено"){
            ui->comboBox_ProjectTasks->setItemData(proj_tasks.indexOf(current_task), QColor(Qt::green), Qt::BackgroundRole);
            ++completedTasks;
        }
        else if (current_task.at(3) == "Не завершено" && current_task.at(4) == "false"){
            ui->comboBox_ProjectTasks->setItemData(proj_tasks.indexOf(current_task), QColor(Qt::red), Qt::BackgroundRole);
        }
        else {
            ui->comboBox_ProjectTasks->setItemData(proj_tasks.indexOf(current_task), QColor(Qt::yellow), Qt::BackgroundRole);
        }
    }
    ui->comboBox_ProjectTasks->setCurrentIndex(0);
    if (totalTasks > 0){
        progressPercent = static_cast<int>((static_cast<double>(completedTasks) / totalTasks) * 100);
    }
    ui->progressBar_Project->setValue(progressPercent);
}

void EmployeeMainWindow::slotGetEmployeeTaskNotesResult(QStringList emp_notes)
{
    ui->textEdit_empNotes->clear();
    for (const QString& emp_note : emp_notes){
        ui->textEdit_empNotes->append(emp_note);
    }
}

void EmployeeMainWindow::slotGetEmployeeSaveTaskNotesResult()
{
    QMessageBox::information(this, "Заметки к проектной задаче", "Заметки к проектной задаче были успешно обновлены.");
}

void EmployeeMainWindow::slotGetEmployeeRequestsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_requests_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int statusColumn = headerLabels.indexOf("Статус запроса");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = emp_requests_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == statusColumn){
                if (value == "Ожидание") {
                    model->setData(index, QColor(153, 153, 0), Qt::ForegroundRole);
                } else if (value == "Принято"){
                    model->setData(index, QColor(0, 153, 0), Qt::ForegroundRole);
                }
                else{
                    model->setData(index, QColor(204, 0, 0), Qt::ForegroundRole);
                }
            }
        }
    }
    ui->tableView_employeeRequestsData->setModel(model);
    ui->tableView_employeeRequestsData->resizeColumnsToContents();
    ui->tableView_employeeRequestsData->show();
}

void EmployeeMainWindow::slotGetEmployeeTableEmployeesDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int statusColumn = headerLabels.indexOf("Статус сотрудника");
    int projColumn = headerLabels.indexOf("Проект");
    int projTaskColumn = headerLabels.indexOf("Проектная задача");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = employees_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == statusColumn){
                if (value == "Онлайн") {
                    model->setData(index, QColor(0, 153, 0), Qt::ForegroundRole);
                } else{
                    model->setData(index, QColor(204, 0, 0), Qt::ForegroundRole);
                }
            } else if (j == projColumn){
                model->setData(index, QColor(128, 0, 128), Qt::ForegroundRole);
            }
            else if (j == projTaskColumn){
                model->setData(index, QColor(75, 0, 130), Qt::ForegroundRole);
            }
        }
    }
    ui->tableView_employeeList->setModel(model);
    ui->tableView_employeeList->resizeColumnsToContents();
    ui->tableView_employeeList->show();
}

void EmployeeMainWindow::slotReadyTakeIntoMainTime(QString location)
{
    if (location == "Раздел Общая статистика"){
        serverConn->getEmployeeCreditalsData();
    }
    else if (location == "Раздел Рабочий график"){
        serverConn->getEmployeeWorkGraf();
    }
    else if (location == "Раздел Исключительные ситуации"){
        serverConn->getEmployeeTableTimeAnomalies();
    }
    else if (location == "Раздел Начать работу над проектами и задачами"){
        serverConn->getEmployeeProjects();
    }
    else if (location == "Раздел Отправить запрос"){
        serverConn->getRequestCategories();
    }
    else if (location == "Раздел Просмотр запросов"){
        serverConn->getRequestCategories();
    }
    else if (location == "Раздел Просмотр активных пользователей"){
        serverConn->getEmployeeTableEmployeesData();
    }
}

void EmployeeMainWindow::slotUpdateProjectDescription(int selected_index)
{
    if (selected_index >= 0 && selected_index < projects.size()) {
        QStringList project = projects[selected_index];
        if (project.size() >= 3) {
            QString proj_name = project[0];
            QString manager = project[2];
            QString description = project[1];
            QString text = "<b>Название проекта:</b> " + proj_name + "<br><b>Руководитель:</b> " + manager + "<br><b>Описание:</b> " + description;
            ui->textEdit_selectProjDescr->setText(text);
        }
        serverConn->getEmployeeProjectTasks(project[0]);
    }
}

void EmployeeMainWindow::slotUpdateProjectTaskDescription(int selected_index)
{
    if (selected_index >= 0 && selected_index < proj_tasks.size()) {
        QStringList proj_task = proj_tasks[selected_index];
        if (proj_task.size() >= 3) {
            QString proj_task_name = proj_task[0];
            QString assignee_employee = proj_task[2];
            QString description = proj_task[1];
            QString text = "<b>Название задачи:</b> " + proj_task_name + "<br><b>Ответственный:</b> " + assignee_employee + "<br><b>Описание:</b> " + description;
            ui->textEdit_selectProjTaskDescr->setText(text);
        }
        serverConn->getEmployeeTaskNotes(proj_task[0]);
    }
}

void EmployeeMainWindow::slotUpdateEmployeeRequestsData(int selected_index)
{
    if (selected_index >= 0){
        serverConn->getEmployeeRequestsData(ui->comboBox_requestCategoriesForCheck->currentText());
    }
}

void EmployeeMainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Закрыть приложение?",
                                                               tr("Вы уверены, что хотите выйти из аккаунта и вернуться на окно авторизации?\n"
                                                                  "Убедитесь, что не получите штрафа перед выходом, или сообщите администратору."),
                                                               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        disconnect(serverConn, &ServerConnection::getEmployeeCreditalsDataResult, this, &EmployeeMainWindow::slotGetEmployeeCreditalsDataResult);
        disconnect(serverConn, &ServerConnection::getEmployeeCompleteTasksResult, this, &EmployeeMainWindow::slotGetEmployeeCompleteTasksResult);
        disconnect(serverConn, &ServerConnection::getEmployeeUnfinishedTasksResult, this, &EmployeeMainWindow::slotGetEmployeeUnfinishedTasksResult);
        disconnect(serverConn, &ServerConnection::getEmployeeTimeDataResult, this, &EmployeeMainWindow::slotGetEmployeeTimeData);
        disconnect(serverConn, &ServerConnection::getEmployeeWorkGrafResult, this, &EmployeeMainWindow::slotGetEmployeeWorkGrafResult);
        disconnect(serverConn, &ServerConnection::getEmployeeTableTimeAnomaliesResult, this, &EmployeeMainWindow::slotGetEmployeeTableTimeAnomaliesResult);
        disconnect(serverConn, &ServerConnection::getRequestCategoriesResult, this, &EmployeeMainWindow::slotGetRequestCategories);
        disconnect(serverConn, &ServerConnection::getEmployeeProjectsResult, this, &EmployeeMainWindow::slotGetEmployeeProjectsResult);
        disconnect(ui->comboBox_Projects, &QComboBox::currentIndexChanged, this, &EmployeeMainWindow::slotUpdateProjectDescription);
        disconnect(serverConn, &ServerConnection::getEmployeeProjectTasksResult, this, &EmployeeMainWindow::slotGetEmployeeProjectTasksResult);
        disconnect(ui->comboBox_ProjectTasks, &QComboBox::currentIndexChanged, this, &EmployeeMainWindow::slotUpdateProjectTaskDescription);
        disconnect(serverConn, &ServerConnection::getEmployeeReadyTaskRequestResult, this, &EmployeeMainWindow::slotGetReadyTaskRequestResult);
        disconnect(serverConn, &ServerConnection::getEmployeeTaskNotesResult, this, &EmployeeMainWindow::slotGetEmployeeTaskNotesResult);
        disconnect(serverConn, &ServerConnection::getEmployeeSaveTaskNotesResult, this, &EmployeeMainWindow::slotGetEmployeeSaveTaskNotesResult);
        disconnect(serverConn, &ServerConnection::getEmployeeRequestsDataResult, this, &EmployeeMainWindow::slotGetEmployeeRequestsDataResult);
        disconnect(ui->comboBox_requestCategoriesForCheck, &QComboBox::currentIndexChanged, this, &EmployeeMainWindow::slotUpdateEmployeeRequestsData);
        disconnect(serverConn, &ServerConnection::getEmployeeTableEmployeesDataResult, this, &EmployeeMainWindow::slotGetEmployeeTableEmployeesDataResult);
        //Сигнал-слоты для учета рабочего времени сотрудника.
        disconnect(serverConn, &ServerConnection::readyTakeIntoMainTime, this, &EmployeeMainWindow::slotReadyTakeIntoMainTime);
        emit returnToAutorization();
        this->close();
    }
}


void EmployeeMainWindow::on_pushButton_send_clicked()
{
    if (ui->textEdit_sendQuery->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Внимание", "Поле описание вашего запроса не может быть пустым!");
        return;
    }
    QMessageBox::information(this, "Информация", "Ваш запрос успешно отправлен!");
    serverConn->sendEmployeeRequest(ui->comboBox_requestCategoriesForSend->currentText(), ui->textEdit_sendQuery->toPlainText());
    ui->textEdit_sendQuery->setText("");
}

void EmployeeMainWindow::on_pushButton_updateProjData_clicked()
{
    if (this->allowWorkControl){
        serverConn->getEmployeeProjects();
    }
}


void EmployeeMainWindow::on_pushButton_BeginTask_clicked()
{
    if (this->allowWorkControl){

        if (proj_tasks.size() > 0 && this->proj_tasks[ui->comboBox_ProjectTasks->currentIndex()][4] == "true"
            && this->proj_tasks[ui->comboBox_ProjectTasks->currentIndex()][3] != "Завершено")
        {
            this->allowWorkControl = false;
            this->blockingLocation = "Task";
            serverConn->sendBeginSubmainTimeData("Начать Выполнение проектной задачи");
            ui->statusBar_emp->showMessage("Для возобновления работы приложения вам необходимо нажать кнопку об окончании выполнения проектной задачи.");
            QMessageBox::information(this, "Статусная строка","Обратите внимание на статусную строку, расположенную внизу окна.");
        }
        else{
            QMessageBox::warning(this, "Выполнение проектной задачи", "У вас нет разрешения на выполнение выбранной проектной задачи, поскольку "
                                                                      "либо задача уже выполнена, либо не существует, либо выделена не Вам.\n"
                                                                     "Попробуйте обновить данные о проектах и задачах, если это не так.\n"
                                                                     "Иначе обратитесь к администратору за дополнительной информацией.");
        }
    }
}


void EmployeeMainWindow::on_pushButton_EndTask_clicked()
{
    if (!this->allowWorkControl && this->blockingLocation == "Task")
    {
        this->allowWorkControl = true;
        this->blockingLocation = "";
        ui->statusBar_emp->showMessage("");
        serverConn->sendEndSubmainTimeData("Закончить Выполнение проектной задачи");
        QMessageBox::information(this, "Работа приложения","Работа приложения была возобновлена. Вы можете продолжать работать.");
    }
}


void EmployeeMainWindow::on_pushButton_readyTask_clicked()
{
    if (this->allowWorkControl){
        if (proj_tasks.size() > 0 && this->proj_tasks[ui->comboBox_ProjectTasks->currentIndex()][4] == "true"){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Выполнение проектной задачи", "Вы уверены, что хотите отправить запрос о проверке готовности проектной задачи?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                serverConn->sendEmployeeReadyTaskRequest("Проект: " + ui->comboBox_Projects->currentText() + "; Задача: " + ui->comboBox_ProjectTasks->currentText());
            }
        }
        else{
            QMessageBox::warning(this, "Выполнение проектной задачи", "У вас нет разрешения на выполнение выбранной проектной задачи, поскольку "
                                                                      "либо задача уже выполнена, либо не существует, либо выделена не Вам.\n"
                                                                      "Попробуйте обновить данные о проектах и задачах, если это не так.\n"
                                                                      "Иначе обратитесь к администратору за дополнительной информацией.");
        }
    }
}


void EmployeeMainWindow::on_pushButton_saveEmpNote_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Изменение заметок к проектной задаче", "Вы уверены, что хотите изменить заметки к текущей проектной задаче?\n"
                                                                                "Будут сохранены только те заметки, которые содержатся в текстовом поле на данный момент.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes){
        QString save_emp_notes = ui->textEdit_empNotes->toPlainText();
        QStringList new_emp_notes = save_emp_notes.split("\n");
        serverConn->sendEmployeeTaskNotesForSave(new_emp_notes, ui->comboBox_ProjectTasks->currentText());
        serverConn->getEmployeeTaskNotes(ui->comboBox_ProjectTasks->currentText());
    }
}


void EmployeeMainWindow::on_pushButton_updateEmpRequestsData_clicked()
{
    if (this->allowWorkControl){
        serverConn->getEmployeeRequestsData(ui->comboBox_requestCategoriesForCheck->currentText());
    }
}


void EmployeeMainWindow::on_pushButton_beginLunchBreak_clicked()
{
    if (this->allowWorkControl){
        this->allowWorkControl = false;
        this->blockingLocation = "LunchBreak";
        serverConn->sendBeginSubmainTimeData("Начать Обеденный перерыв");
        ui->statusBar_emp->showMessage("Для возобновления работы приложения вам необходимо нажать кнопку об окончании обеденного перерыва.");
        QMessageBox::information(this, "Статусная строка","Обратите внимание на статусную строку, расположенную внизу окна.");
    }
}


void EmployeeMainWindow::on_pushButton_finishLunchBreak_clicked()
{
    if (!this->allowWorkControl && this->blockingLocation == "LunchBreak")
    {
        this->allowWorkControl = true;
        this->blockingLocation = "";
        ui->statusBar_emp->showMessage("");
        serverConn->sendEndSubmainTimeData("Закончить Обеденный перерыв");
        QMessageBox::information(this, "Работа приложения","Работа приложения была возобновлена. Вы можете продолжать работать.");
    }
}


void EmployeeMainWindow::on_pushButton_beginMeeting_clicked()
{
    if (this->allowWorkControl){
        this->allowWorkControl = false;
        this->blockingLocation = "Meeting";
        serverConn->sendBeginSubmainTimeData("Начать Совещание");
        ui->statusBar_emp->showMessage("Для возобновления работы приложения вам необходимо нажать кнопку об окончании совещания.");
        QMessageBox::information(this, "Статусная строка","Обратите внимание на статусную строку, расположенную внизу окна.");
    }
}


void EmployeeMainWindow::on_pushButton_finishMeeting_clicked()
{
    if (!this->allowWorkControl && this->blockingLocation == "Meeting")
    {
        this->allowWorkControl = true;
        this->blockingLocation = "";
        ui->statusBar_emp->showMessage("");
        serverConn->sendEndSubmainTimeData("Закончить Совещание");
        QMessageBox::information(this, "Работа приложения","Работа приложения была возобновлена. Вы можете продолжать работать.");
    }
}


void EmployeeMainWindow::on_pushButton_beginAbsenceDueToWork_clicked()
{
    if (this->allowWorkControl){
        this->allowWorkControl = false;
        this->blockingLocation = "AbsenceDueToWork";
        serverConn->sendBeginSubmainTimeData("Начать Отсутствие по работе");
        ui->statusBar_emp->showMessage("Для возобновления работы приложения вам необходимо нажать кнопку об окончании отсутствия по рабочей причине.");
        QMessageBox::information(this, "Статусная строка","Обратите внимание на статусную строку, расположенную внизу окна.");
    }
}


void EmployeeMainWindow::on_pushButton_finishAbsenceDueToWork_clicked()
{
    if (!this->allowWorkControl && this->blockingLocation == "AbsenceDueToWork")
    {
        this->allowWorkControl = true;
        this->blockingLocation = "";
        ui->statusBar_emp->showMessage("");
        serverConn->sendEndSubmainTimeData("Закончить Отсутствие по работе");
        QMessageBox::information(this, "Работа приложения","Работа приложения была возобновлена. Вы можете продолжать работать.");
    }
}


void EmployeeMainWindow::on_pushButton_beginPersonalNeeded_clicked()
{
    if (this->allowWorkControl){
        this->allowWorkControl = false;
        this->blockingLocation = "PersonalNeeded";
        serverConn->sendBeginSubmainTimeData("Начать Отсутствие по личной нужде");
        ui->statusBar_emp->showMessage("Для возобновления работы приложения вам необходимо нажать кнопку об окончании отсутствия по личной нужде.");
        QMessageBox::information(this, "Статусная строка","Обратите внимание на статусную строку, расположенную внизу окна.");
    }
}


void EmployeeMainWindow::on_pushButton_finishPersonalNeeded_clicked()
{
    if (!this->allowWorkControl && this->blockingLocation == "PersonalNeeded")
    {
        this->allowWorkControl = true;
        this->blockingLocation = "";
        ui->statusBar_emp->showMessage("");
        serverConn->sendEndSubmainTimeData("Закончить Отсутствие по личной нужде");
        QMessageBox::information(this, "Работа приложения","Работа приложения была возобновлена. Вы можете продолжать работать.");
    }
}

void EmployeeMainWindow::on_pushButton_updateEmpTableData_clicked()
{
    if (this->allowWorkControl){
        serverConn->getEmployeeTableEmployeesData();
    }
}

void EmployeeMainWindow::slotGetEmployeeCreditalsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> creditals_data)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = creditals_data[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
        }
    }
    ui->tableView_credentials->setModel(model);
    ui->tableView_credentials->resizeColumnsToContents();
    ui->tableView_credentials->show();
    serverConn->getEmployeeTimeData();
}

void EmployeeMainWindow::slotGetEmployeeCompleteTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int projColumn = headerLabels.indexOf("Проект");
    int projTaskColumn = headerLabels.indexOf("Проектная задача");
    int statusColumn = headerLabels.indexOf("Статус выполнения задачи");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = complete_tasks[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == projColumn){
                model->setData(index, QColor(128, 0, 128), Qt::ForegroundRole);
            }
            else if (j == projTaskColumn){
                model->setData(index, QColor(75, 0, 130), Qt::ForegroundRole);
            }
            else if (j == statusColumn){
                model->setData(index, QColor(0, 130, 0), Qt::ForegroundRole);
            }
        }
    }
    ui->tableView_completeProjectTasks->setModel(model);
    ui->tableView_completeProjectTasks->resizeColumnsToContents();
    ui->tableView_completeProjectTasks->show();
    serverConn->getEmployeeUnfinishedTasks();

}

void EmployeeMainWindow::slotGetEmployeeUnfinishedTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> unfinished_tasks)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(columnCount);
    model->setRowCount(rowCount);
    model->setHorizontalHeaderLabels(headerLabels);
    int projColumn = headerLabels.indexOf("Проект");
    int projTaskColumn = headerLabels.indexOf("Проектная задача");
    int statusColumn = headerLabels.indexOf("Статус выполнения задачи");
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QString value = unfinished_tasks[i][j];
            QModelIndex index = model->index(i, j);
            model->setData(index, value);
            if (j == projColumn){
                model->setData(index, QColor(128, 0, 128), Qt::ForegroundRole);
            }
            else if (j == projTaskColumn){
                model->setData(index, QColor(75, 0, 130), Qt::ForegroundRole);
            }
            else if (j == statusColumn){
                model->setData(index, QColor(130, 0, 0), Qt::ForegroundRole);
            }
        }
    }
    ui->tableView_unfinishedProjectTasks->setModel(model);
    ui->tableView_unfinishedProjectTasks->resizeColumnsToContents();
    ui->tableView_unfinishedProjectTasks->show();
}

void EmployeeMainWindow::slotGetEmployeeTimeData(QStringList time_data)
{
    if (time_data.size() >= 4){
        ui->label_notEnoughWork->setText(time_data[0]);
        ui->label_lateness->setText(time_data[1]);
        ui->label_enoughWork->setText(time_data[2]);
        ui->label_workTime->setText(time_data[3]);
    }
    serverConn->getEmployeeCompleteTasks();
}

void EmployeeMainWindow::on_pushButton_hideCredentials_clicked()
{
    if (allowWorkControl)
    {
        if (ui->tableView_credentials->isVisible()){
            ui->tableView_credentials->hide();
            ui->pushButton_hideCredentials->setText("Показать");
        }
        else{
            ui->tableView_credentials->show();
            ui->pushButton_hideCredentials->setText("Скрыть");
        }
    }
}

