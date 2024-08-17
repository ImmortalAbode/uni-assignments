#include "ServerConnection.h"

ServerConnection::ServerConnection(QString host, quint16 port, QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    reconnectTimer = new QTimer();
    this->host = host;
    this->port = port;
    this->isServerDown = false;
    connect(socket, &QTcpSocket::readyRead, this, &ServerConnection::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ServerConnection::slotDisconnected);
    connect(socket, &QTcpSocket::connected, this, &ServerConnection::slotConnected);
    connect(reconnectTimer, &QTimer::timeout, this, &ServerConnection::slotAttemptReconnect);
}

ServerConnection::~ServerConnection()
{
    delete socket;
    delete reconnectTimer;
}

void ServerConnection::connectToServer()
{
    socket->connectToHost(host, port);
    if (!isServerDown && !socket->waitForConnected(5000))
    {
        isServerDown = true;
        slotDisconnected();
    }
}

void ServerConnection::sendAuthorizationData(QString user_login, QString user_pswd)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::AUTHORISATION);
    out << user_login;
    out << user_pswd;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendRegistrationData(QStringList reg_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::REGISTRATION);
    foreach(const QString &str, reg_data)
    {
        out << str;
    }
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeCreditalsData()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_CREDITALS_DATA);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeCompleteTasks()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_COMPLETE_TASKS);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeUnfinishedTasks()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_UNFINISHED_TASKS);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeTimeData()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_GET_TIME_DATA);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeWorkGraf()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_GET_WORK_GRAF);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeTableTimeAnomalies()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_GET_TIME_ANOMALIES);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendEntryTimeData(bool manager_flag)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::TAKE_INTO_ENTRY_TIME);
    out << manager_flag;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendMainTimeData(QString location)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::TAKE_INTO_MAIN_TIME);
    out << location;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendBeginSubmainTimeData(QString action)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::TAKE_INTO_BEGIN_SUBMAIN_TIME);
    out << action;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendEndSubmainTimeData(QString action)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::TAKE_INTO_END_SUBMAIN_TIME);
    out << action;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendExitFromApp(QString user_login, QString user_pswd)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EXIT);
    out << user_login;
    out << user_pswd;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getRequestCategories()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::REQUEST_CATEGORIES);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendEmployeeRequest(QString type_request, QString text)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_REQUEST);
    out << type_request << text;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeProjects()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_PROJECTS);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeProjectTasks(QString proj_name)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_PROJECT_TASKS);
    out << proj_name;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendEmployeeReadyTaskRequest(QString task_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_READYTASK_REQUEST);
    out << task_data;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeTaskNotes(QString proj_task_name)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_NOTES);
    out << proj_task_name;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendEmployeeTaskNotesForSave(QStringList new_task_emp_notes, QString task_name)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_SAVE_NOTES);
    out << task_name;
    for (const QString& new_note : new_task_emp_notes){
        out << new_note;
    }
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeRequestsData(QString category_name)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_REQUESTS_DATA);
    out << category_name;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeTableEmployeesData()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_TABLE_EMPLOYEES_DATA);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAdminSaveReport(QString EmployeeID, QString dateStart, QString dateFinish)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_SAVE_REPORT);
    out << EmployeeID << dateStart << dateFinish;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAdminRemoveAnomaly(QString anomaly_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_ANOMALY);
    out << anomaly_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAdminAnomalyData(QString emp_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_ANOMALY_DATA);
    out << emp_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminEmployeeTableForAnomaly(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_EMPLOYEE_ANOMALY_DATA);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAdminRemoveWeekend(QString weekend_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_WEEKEND);
    out << weekend_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAdminWorkWithWeekend(QString action, QString object_id, QString weekend_begin, QString weekend_end, QString note)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_WORK_WITH_WEEKEND);
    out << action << object_id << weekend_begin << weekend_end << note;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAdminRemoveGraf(QString graf_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_GRAF);
    out << graf_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAdminWorkWithGraf(QString action, QString object_id, QStringList workSchedule)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_WORK_WITH_GRAF);
    out << action << object_id;
    foreach(const QString &day, workSchedule) {
        out << day;
    }
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminEmployeeWeekends(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_WEEKENDS);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminEmployeeGrafs(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_GRAFS);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminEmployeeData(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_DATA);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminCompleteProjTasks(QString projID)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_COMPLETE_TASKS);
    out << projID;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminCompleteProjects(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_COMPLETE_PROJECTS);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminCredentialsData()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_CREDENTIALS_DATA);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeDataTable(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_EMPLOYEE_DATA_TABLE);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendRemovedUserID(QString user_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_EMPLOYEE);
    out << user_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendChangedEmployeeData(QString user_id, QStringList change_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_CHANGE_EMPLOYEE_DATA);
    out << user_id;
    foreach(const QString &str, change_data)
    {
        out << str;
    }
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeRequestsDataTable(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_REQUESTS);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getRequestStatuses()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_REQUEST_STATUSES);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendCloseRequest(int ID_request, QString requestStatus, QString text)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_CLOSE_EMPLOYEE_REQUEST);
    out << ID_request << requestStatus << text;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAddAdmin(QString UpEmployeeID, QString JobTitleEmployee)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_ADD_ADMIN);
    out << UpEmployeeID << JobTitleEmployee;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAdminTableData()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_ADMIN_DATA_TABLE);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendRemovedAdminID(QString user_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_REMOVE_ADMIN);
    out << user_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendChangedAdminData(QString user_id, QStringList change_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_CHANGE_ADMIN_DATA);
    out << user_id;
    foreach(const QString &str, change_data)
    {
        out << str;
    }
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getClosedRequestsTableData()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_ALL_CLOSE_REQUESTS_DATA_TABLE);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAllProjectsAndTasksTableData(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_GET_PROJECT_TASK_DATA_TABLE);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAddProjectTableData()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_PROJECT_DATA_TABLE);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendNewProjectData(QString projectManagerID, QString projectName, QString projectDescription)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_ADD_PROJECT);
    out << projectManagerID << projectName << projectDescription;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getProjectsDataForChange()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_CHANGE_PROJECT_DATA_TABLE);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendRemovedProjectID(QString removingProjectID)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_REMOVE_PROJECT);
    out << removingProjectID;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendChangedProjectData(QString changedProjectID, QString newProjectName, QString newProjectDescription)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_CHANGE_PROJECT);
    out << changedProjectID << newProjectName << newProjectDescription;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendWorkedProjectID(QString workingProjectID)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_WORK_PROJECT);
    out << workingProjectID;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendNewProjectManagerForProjectData(QString new_admin_id, QString project_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::MAINADMIN_PROJECT_MANAGER_FOR_PROJECT);
    out << new_admin_id << project_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getTasksDataTable(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_TASK_DATA_TABLE);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getEmployeeDataTableForTask(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_TASK_EMPLOYEE_DATA_TABLE);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendAddTaskData(QStringList add_task_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_ADD_TASK);
    foreach(const QString &str, add_task_data)
    {
        out << str;
    }
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendChangedTaskData(QString changedTaskID, QString newTaskName, QString newTaskDescription)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_CHANGE_TASK);
    out << changedTaskID << newTaskName << newTaskDescription;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendRemovedTaskID(QString removingTaskID)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_REMOVE_TASK);
    out << removingTaskID;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendWorkedTaskID(QString workingTaskID)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_WORK_TASK);
    out << workingTaskID;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::sendNewEmployeeForTaskData(QString new_emp_id, QString task_id)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_EMPLOYEE_FOR_TASK);
    out << new_emp_id << task_id;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getTeam(QString type_admin)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_TEAM);
    out << type_admin;
    socket->write(Data);
    socket->flush();
}

void ServerConnection::getAllOnlineUsers()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out <<static_cast<quint8>(MessageType::ADMIN_ONLINE_USERS);
    socket->write(Data);
    socket->flush();
}

void ServerConnection::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_7);
    if (in.status() == QDataStream::Ok)
    {
        quint8 messageType;
        in >> messageType;
        switch (static_cast<MessageType>(messageType)) {
        //Ошибка на стороне сервера.
        case MessageType::ERROR:
        {
            QString error_text;
            in >> error_text;
            emit errorResult(error_text);
            break;
        }
        //Авторизация.
        case MessageType::AUTHORISATION:
        {
            bool usernameSuccess;
            bool passwordSuccess;
            QString userRole;
            in >> usernameSuccess >> passwordSuccess >> userRole;
            emit authorizationResult(usernameSuccess, passwordSuccess, userRole);
            break;
        }
        //Получение учетных данных пользователя.
        case MessageType::EMPLOYEE_CREDITALS_DATA:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> creditals_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                creditals_data.append(rowValues);
            }
            emit getEmployeeCreditalsDataResult(headerLabels, columnCount, rowCount, creditals_data);
            break;
        }
        //Получение выполенных задач сотрудником.
        case MessageType::EMPLOYEE_COMPLETE_TASKS:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> complete_tasks;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                complete_tasks.append(rowValues);
            }
            emit getEmployeeCompleteTasksResult(headerLabels, columnCount, rowCount, complete_tasks);
            break;
        }
        //Получение невыполненных задач сотрудника.
        case MessageType::EMPLOYEE_UNFINISHED_TASKS:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> unfinished_tasks;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                unfinished_tasks.append(rowValues);
            }
            emit getEmployeeUnfinishedTasksResult(headerLabels, columnCount, rowCount, unfinished_tasks);
            break;
        }
        //Получение данных времени сотрудника.
        case MessageType::EMPLOYEE_GET_TIME_DATA:
        {
            QStringList time_data;
            while(!in.atEnd()){
                QString time;
                in >> time;
                time_data.append(time);
            }
            emit getEmployeeTimeDataResult(time_data);
            break;
        }
        //Регистрация|Добавление сотрудника.
        case MessageType::REGISTRATION:
        {
            QMap<QString, bool> reg_success;
            QString key;
            bool value;
            while (!in.atEnd()) {
                in >> key >> value;
                reg_success[key] = value;
            }
            emit registrationResult(reg_success);
            break;
        }
        //Получение данных рабочего графика.
        case MessageType::EMPLOYEE_GET_WORK_GRAF:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> work_graf_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                work_graf_data.append(rowValues);
            }
            emit getEmployeeWorkGrafResult(headerLabels, columnCount, rowCount, work_graf_data);
            break;
        }
        //Получение данных искл. ситуаций для сотрудника.
        case MessageType::EMPLOYEE_GET_TIME_ANOMALIES:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> time_anomalies_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                time_anomalies_data.append(rowValues);
            }
            emit getEmployeeTableTimeAnomaliesResult(headerLabels, columnCount, rowCount, time_anomalies_data);
            break;
        }
        //Проверка входа сотрудника.
        case MessageType::TAKE_INTO_ENTRY_TIME:
        {
            bool correct;
            in >> correct;
            emit checkEntryTimeDataResult(correct);
            break;
        }
        //Учет рабочего времени сотрудника.
        case MessageType::TAKE_INTO_MAIN_TIME:
        {
            QString location;
            in >> location;
            emit readyTakeIntoMainTime(location);
            break;
        }
        //Получение категорий запросов пользователя.
        case MessageType::REQUEST_CATEGORIES:
        {
            QStringList categories;
            in >> categories;
            emit getRequestCategoriesResult(categories);
            break;
        }
        //Получение ошибки выполнения отправки запроса сотрудника.
        case MessageType::EMPLOYEE_READYTASK_REQUEST:
        {
            bool correct;
            in >> correct;
            emit getEmployeeReadyTaskRequestResult(correct);
            break;
        }
        //Получение списка проектов.
        case MessageType::EMPLOYEE_PROJECTS:
        {
            QList<QStringList> projects;
            while (!in.atEnd()){
                QStringList current_project;
                QString proj_name, proj_descr, proj_man_fullName, proj_status;
                in >> proj_name >> proj_descr >> proj_man_fullName >> proj_status;
                current_project << proj_name << proj_descr << proj_man_fullName << proj_status;
                if (!proj_name.isEmpty() && !proj_descr.isEmpty() && !proj_man_fullName.isEmpty() && !proj_status.isEmpty())
                    projects.append(current_project);
            }
            emit getEmployeeProjectsResult(projects);
            break;
        }
        //Получение списка проектных задач.
        case MessageType::EMPLOYEE_PROJECT_TASKS:
        {
            QList<QStringList> project_tasks;
            while (!in.atEnd()){
                QStringList current_task;
                QString proj_task_name, proj_task_descr, proj_task_emp_fullName, proj_task_status, proj_task_access;
                in >> proj_task_name >> proj_task_descr >> proj_task_emp_fullName >> proj_task_status >> proj_task_access;
                current_task << proj_task_name << proj_task_descr << proj_task_emp_fullName << proj_task_status << proj_task_access;
                if (!proj_task_name.isEmpty() && !proj_task_descr.isEmpty() && !proj_task_emp_fullName.isEmpty() && !proj_task_status.isEmpty() && !proj_task_access.isEmpty())
                    project_tasks.append(current_task);
            }
            emit getEmployeeProjectTasksResult(project_tasks);
            break;
        }
        //Получение заметок сотрудника к проектной задаче.
        case MessageType::EMPLOYEE_NOTES:
        {
            QStringList task_emp_notes;
            while (!in.atEnd())
            {
                QString current_emp_note;
                in >> current_emp_note;
                if (!current_emp_note.isEmpty())
                    task_emp_notes.append(current_emp_note);
            }
            emit getEmployeeTaskNotesResult(task_emp_notes);
            break;
        }
        //Сохранение заметок сотрудника к проектной задаче.
        case MessageType::EMPLOYEE_SAVE_NOTES:
        {
            emit getEmployeeSaveTaskNotesResult();
            break;
        }
        //Получение данных запросов сотрудника.
        case MessageType::EMPLOYEE_REQUESTS_DATA:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> emp_requests_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                emp_requests_data.append(rowValues);
            }
            emit getEmployeeRequestsDataResult(headerLabels, columnCount, rowCount, emp_requests_data);
            break;
        }
        //Получение списка сотрудников для сотрудника.
        case MessageType::EMPLOYEE_TABLE_EMPLOYEES_DATA:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> employees_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                employees_data.append(rowValues);
            }
            emit getEmployeeTableEmployeesDataResult(headerLabels, columnCount, rowCount, employees_data);
            break;
        }
        //Получение данных для отчета.
        case MessageType::ADMIN_SAVE_REPORT:
        {
            nextBlockSize = 0;
            QString report;
            while (true) {
                if (nextBlockSize == 0) {
                    if (socket->bytesAvailable() < sizeof(quint16)) {
                        break;
                    }
                    in >> nextBlockSize;
                }

                if (socket->bytesAvailable() < nextBlockSize) {
                    break;
                }

                QByteArray reportData;
                reportData.resize(nextBlockSize);
                in.readRawData(reportData.data(), nextBlockSize);

                report += QString::fromUtf8(reportData);

                nextBlockSize = 0;
            }
            emit getAdminSaveReportResult(report);
            break;
        }
        //Получение результата удаления аномалии времени сотрудника.
        case MessageType::ADMIN_REMOVE_ANOMALY:
        {
            bool access;
            in >> access;
            emit getAdminRemoveAnomalyResult(access);
            break;
        }
        //Получение данных аномалий времени сотрудника.
        case MessageType::ADMIN_ANOMALY_DATA:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> anomalies_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                anomalies_data.append(rowValues);
            }
            emit getAdminAnomalyDataResult(headerLabels, columnCount, rowCount, anomalies_data);
            break;
        }
        //Получение данных сотрудников для учета их аномалий.
        case MessageType::ADMIN_EMPLOYEE_ANOMALY_DATA:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> employees_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                employees_data.append(rowValues);
            }
            emit getAdminEmployeeTableForAnomalyResult(headerLabels, columnCount, rowCount, employees_data);
            break;
        }
        //Получение результата удаления отпуска сотрудника.
        case MessageType::ADMIN_REMOVE_WEEKEND:
        {
            bool access;
            in >> access;
            emit getAdminRemoveWeekendResult(access);
            break;
        }
        //Получение результата работы с отпусками сотрудников.
        case MessageType::ADMIN_WORK_WITH_WEEKEND:
        {
            bool access;
            QString action;
            in >> action >> access;
            emit getAdminWorkWithWeekendResult(action, access);
            break;
        }
        //Получение результата удаления графика сотрудника.
        case MessageType::ADMIN_REMOVE_GRAF:
        {
            bool access;
            in >> access;
            emit getAdminRemoveGrafResult(access);
            break;
        }
        //Получение результата работы с графиками сотрудников.
        case MessageType::ADMIN_WORK_WITH_GRAF:
        {
            bool access;
            QString action;
            in >> action >> access;
            emit getAdminWorkWithGrafResult(action, access);
            break;
        }
        //Получение списка отпусков сотрудников.
        case MessageType::ADMIN_GET_EMPLOYEE_WEEKENDS:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> weekends_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                weekends_data.append(rowValues);
            }
            emit getAdminEmployeeWeekendsResult(headerLabels, columnCount, rowCount, weekends_data);
            break;
        }
        //Получение списка графиков сотрудников.
        case MessageType::ADMIN_GET_EMPLOYEE_GRAFS:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> grafs_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                grafs_data.append(rowValues);
            }
            emit getAdminEmployeeGrafsResult(headerLabels, columnCount, rowCount, grafs_data);
            break;
        }
        //Получение списка сотрудников для настройки графиков.
        case MessageType::ADMIN_GET_EMPLOYEE_DATA:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> employees_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                employees_data.append(rowValues);
            }
            emit getAdminEmployeeDataResult(headerLabels, columnCount, rowCount, employees_data);
            break;
        }
        //Получение выполненных проектных задач для администратора.
        case MessageType::ADMIN_COMPLETE_TASKS:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> complete_tasls_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                complete_tasls_data.append(rowValues);
            }
            emit getAdminCompleteProjectTasksResult(headerLabels, columnCount, rowCount, complete_tasls_data);
            break;
        }
        //Получение выполненных проектов для администратора.
        case MessageType::ADMIN_COMPLETE_PROJECTS:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> complete_projs_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                complete_projs_data.append(rowValues);
            }
            emit getAdminCompleteProjectsResult(headerLabels, columnCount, rowCount, complete_projs_data);
            break;
        }
        //Получение учетных данных администратора.
        case MessageType::ADMIN_CREDENTIALS_DATA:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> credentials_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                credentials_data.append(rowValues);
            }
            emit getAdminCredentialsDataResult(headerLabels, columnCount, rowCount, credentials_data);
            break;
        }
        //Получение списка сотудников.
        case MessageType::ADMIN_EMPLOYEE_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> users_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                users_data.append(rowValues);
            }
            emit employeeTableDataResult(headerLabels, columnCount, rowCount, users_data);
            break;
        }
        //Удаление сотрудника.
        case MessageType::ADMIN_REMOVE_EMPLOYEE:
        {
            bool removing_success;
            in >> removing_success;
            emit removedEmployeeResult(removing_success);
            break;
        }
        //Изменение данных о сотруднике.
        case MessageType::ADMIN_CHANGE_EMPLOYEE_DATA:
        {
            QMap<QString, bool> change_success;
            QString key;
            bool value;
            while (!in.atEnd()) {
                in >> key >> value;
                change_success[key] = value;
            }
            emit changedEmployeeResult(change_success);
            break;
        }
        //Получение запросов сотрудников.
        case MessageType::ADMIN_GET_EMPLOYEE_REQUESTS:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> emp_requests_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                emp_requests_data.append(rowValues);
            }
            emit employeeRequestsResult(headerLabels, columnCount, rowCount, emp_requests_data);
            break;
        }
        //Получение статусов запросов.
        case MessageType::ADMIN_GET_EMPLOYEE_REQUEST_STATUSES:
        {
            QStringList requestStatuses;
            in >> requestStatuses;
            emit requestStatusesResult(requestStatuses);
            break;
        }
        //Получение списка администраторов.
        case MessageType::MAINADMIN_ADMIN_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> users_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                users_data.append(rowValues);
            }
            emit adminTableDataResult(headerLabels, columnCount, rowCount, users_data);
            break;
        }
        //Удаление администратора.
        case MessageType::MAINADMIN_REMOVE_ADMIN:
        {
            bool removing_success;
            in >> removing_success;
            emit removedAdminResult(removing_success);
            break;
        }
        //Добавление администратора.
        case MessageType::MAINADMIN_ADD_ADMIN:
        {
            bool adding_success;
            in >> adding_success;
            emit addedAdminResult(adding_success);
            break;
        }
        //Изменение данных об администраторе.
        case MessageType::MAINADMIN_CHANGE_ADMIN_DATA:
        {
            QMap<QString, bool> change_success;
            QString key;
            bool value;
            while (!in.atEnd()) {
                in >> key >> value;
                change_success[key] = value;
            }
            emit changedAdminResult(change_success);
            break;
        }
        //Получение всех закрытых запросов сотрудников.
        case MessageType::ADMIN_ALL_CLOSE_REQUESTS_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> users_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                users_data.append(rowValues);
            }
            emit allClosedRequestsResult(headerLabels, columnCount, rowCount, users_data);
            break;
        }
        //Получение всех проектов и задач.
        case MessageType::ADMIN_GET_PROJECT_TASK_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> projects_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                projects_data.append(rowValues);
            }
            emit projectsAndTasksResult(headerLabels, columnCount, rowCount, projects_data);
            break;
        }
        //Получение информации о проектах для добавления.
        case MessageType::MAINADMIN_PROJECT_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> projects_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                projects_data.append(rowValues);
            }
            emit addProjectDataResult(headerLabels, columnCount, rowCount, projects_data);
            break;
        }
        //Получение информации о проектах для удаления/изменения.
        case MessageType::MAINADMIN_CHANGE_PROJECT_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> projects_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                projects_data.append(rowValues);
            }
            emit changeProjectDataResult(headerLabels, columnCount, rowCount, projects_data);
            break;
        }
        //Получение информации о завершении операции удаления/изменения проекта.
        case MessageType::MAINADMIN_REMOVE_CHANGE_PROJECT_COMPLETE:
        {
            emit removedChangedProjectSuccess();
            break;
        }
        //Получение информации о задачах.
        case MessageType::ADMIN_GET_TASK_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> tasks_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                tasks_data.append(rowValues);
            }
            emit taskDataTableResult(headerLabels, columnCount, rowCount, tasks_data);
            break;
        }
        //Получение информации о сотрудниках для задач.
        case MessageType::ADMIN_GET_TASK_EMPLOYEE_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> emps_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                emps_data.append(rowValues);
            }
            emit empsForTaskDataTableResult(headerLabels, columnCount, rowCount, emps_data);
            break;
        }
        //Получение информации о завершении операции удаления/изменения задачи.
        case MessageType::ADMIN_REMOVE_CHANGE_TASK_COMPLETE:
        {
            emit removedChangedTaskSuccess();
            break;
        }
        //Получение информации о завершении операции закрытия запроса.
        case MessageType::ADMIN_CLOSE_REQUEST_COMPLETE:
        {
            emit adminCloseRequestSuccess();
            break;
        }
        //Получение информации о завершении операции добавления проекта.
        case MessageType::MAINADMIN_ADD_PROJECT_SUCCESS:
        {
            emit addProjectSuccess();
            break;
        }
        //Получение информации о завершении операции добавления проекта.
        case MessageType::ADMIN_ADD_TASK_SUCCESS:
        {
            bool adding_success;
            in >> adding_success;
            emit addTaskSuccess(adding_success);
            break;
        }
        //Получение информации о команде.
        case MessageType::ADMIN_TEAM_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> team_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                team_data.append(rowValues);
            }
            emit teamDataTableResult(headerLabels, columnCount, rowCount, team_data);
            break;
        }
        //Получение информации об онлайн пользователях.
        case MessageType::ADMIN_ONLINE_DATA_TABLE:
        {
            int columnCount, rowCount;
            QStringList headerLabels;
            QList<QStringList> online_data;
            in >> columnCount >> rowCount;
            for (int i= 0; i < columnCount; ++i){
                QString value;
                in >> value;
                headerLabels.append(value);
            }
            for (int i = 0; i < rowCount; ++i) {
                QStringList rowValues;
                for (int j = 0; j < columnCount; ++j) {
                    QString value;
                    in >> value;
                    rowValues.append(value);
                }
                online_data.append(rowValues);
            }
            emit onlineDataTableResult(headerLabels, columnCount, rowCount, online_data);
            break;
        }
        //Неизвестное сообщение.
        default:
        {
            qDebug() << "Ошибка! Неизвестный тип сообщения от сервера.";
            break;
        }
        }
    }
    else
    {
        qDebug() << "Ошибка DataStream! Невозможно прочитать данные из сокета.";
    }
}

void ServerConnection::slotDisconnected()
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        reconnectTimer->start(5000);
        isServerDown = true;
        emit connectionLost();
    }
}

void ServerConnection::slotConnected()
{
    if (isServerDown)
    {
        reconnectTimer->stop();
        isServerDown = false;
        emit connectionRestored();
    }
}

void ServerConnection::slotAttemptReconnect()
{
    disconnect(socket, &QTcpSocket::connected, this, &ServerConnection::slotConnected);
    this->connectToServer();
    connect(socket, &QTcpSocket::connected, this, &ServerConnection::slotConnected);
}
