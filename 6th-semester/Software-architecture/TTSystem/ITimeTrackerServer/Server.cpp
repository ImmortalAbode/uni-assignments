#include "server.h"
#include "QRegularExpression"
#include "QDateTime"
#include <QSqlRecord>

Server::Server()
{
    if (this->listen(QHostAddress::Any, 2323))
    {
        qDebug() << "Сервер был запущен...";
    }
    else
    {
        qDebug() << "Ошибка! Порт: 2323 не может быть прослушан сервером.";
    }
    //Подключение к БД ITimeTracker.
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={ODBC Driver 17 for SQL Server};DSN=ITimeTrackerDSN;UID=AdminITimeTracker;PWD=i2t0i0m3e_tracker;");
    if (db.open())
    {
        qDebug() << "Вы успешно подключились к базе данных. Параметры:" + db.databaseName();
    }
    else
    {
        qDebug() << "Ошибка подключения к базе данных: " + db.lastError().databaseText();
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket{};
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    this->socketDescriptor = socketDescriptor;
    Sockets.push_back(socket);
    qDebug() << "Клиент подключился. Дескриптор клиента: " << this->socketDescriptor;
}

void Server::slotClientDisconnected()
{
    QTcpSocket *disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    if (disconnectedSocket) {
        qDebug() << "Клиент отключился. Дескриптор клиента: " << this->socketDescriptor;
        Sockets.removeOne(disconnectedSocket);
        disconnectedSocket->deleteLater();
    }
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_7);
    if (in.status() == QDataStream::Ok)
    {
        quint8 messageType;
        in >> messageType;
        switch (static_cast<MessageType>(messageType)) {
        //Авторизация.
        case MessageType::AUTHORISATION:
        {
            additionalForAuthorizationResult(in);
            break;
        }
        //Регистрация.
        case MessageType::REGISTRATION:
        {
            additionalForRegistrationResult(in);
            break;
        }
        //Преждевременный выход из приложения.
        case MessageType::EXIT:
        {
            additionalForExitFromApp(in);
            break;
        }
        //Получение учетных данных сотрудника.
        case MessageType::EMPLOYEE_CREDITALS_DATA:
        {
            additionalForSendEmployeeCreditalsData();
            break;
        }
        //Получение выполненных задач сотрудника.
        case MessageType::EMPLOYEE_COMPLETE_TASKS:
        {
            additionalForSendEmployeeCompleteTasks();
            break;
        }
        //Получение невыполеннных задач сотрудника.
        case MessageType::EMPLOYEE_UNFINISHED_TASKS:
        {
            additionalForSendEmployeeUnfinishedTasks();
            break;
        }
        //Получение данных времени сотрудника.
        case MessageType::EMPLOYEE_GET_TIME_DATA:
        {
            additionalForSendEmployeeTimeData();
            break;
        }
        //Получение текущих рабочих графиков сотрудника и его коллег.
        case MessageType::EMPLOYEE_GET_WORK_GRAF:
        {
            additionalForSendEmployeeTableWorkGrafResult();
            break;
        }
        //Получение данных искл. ситуаций для сотрудника.
        case MessageType::EMPLOYEE_GET_TIME_ANOMALIES:
        {
            additionalForSendEmployeeTableTimeAnomaliesResult();
            break;
        }
        //Учет рабочего времени сотрудника.
        case MessageType::TAKE_INTO_ENTRY_TIME:
        {
            in >> this->manager_flag;
            additionalForTakeIntoEntryTime();
            break;
        }
        case MessageType::TAKE_INTO_MAIN_TIME:
        {
            additionalForTakeIntoMainTime(in);
            break;
        }
        case MessageType::TAKE_INTO_BEGIN_SUBMAIN_TIME:
        {
            additionalForTakeIntoBeginSubmainTime(in);
            break;
        }
        case MessageType::TAKE_INTO_END_SUBMAIN_TIME:
        {
            additionalForTakeIntoEndSubmainTime(in);
            break;
        }
        //Возврат данных о категориях запросов.
        case MessageType::REQUEST_CATEGORIES:
        {
            additionalForSendRequestCategoriesResult();
            break;
        }
        //Получение содержание запроса.
        case MessageType::EMPLOYEE_REQUEST:
        {
            additionalForEmployeeRequestResult(in);
            break;
        }
        //Получение списка проектов.
        case MessageType::EMPLOYEE_PROJECTS:
        {
            additionalForSendEmployeeProjectsResult();
            break;
        }
        //Получение списка проектных задач.
        case MessageType::EMPLOYEE_PROJECT_TASKS:
        {
            additionalForSendEmployeeProjectTasksResult(in);
            break;
        }
        //Получение результата отправки запроса сотрудника о готовности проектной задачи.
        case MessageType::EMPLOYEE_READYTASK_REQUEST:
        {
            additionalForSendEmployeeReadyTaskRequestResult(in);
            break;
        }
        //Получение списка заметок к проектной задаче сотрудника.
        case MessageType::EMPLOYEE_NOTES:
        {
            additionalForSendEmployeeTaskNotesResult(in);
            break;
        }
        //Сохранение заметок к проектной задаче сотрудника.
        case MessageType::EMPLOYEE_SAVE_NOTES:
        {
            additionalForSendEmployeeSaveTaskNotesResult(in);
            break;
        }
        case MessageType::EMPLOYEE_REQUESTS_DATA:
        {
            additionalForSendEmployeeRequestsDataResult(in);
            break;
        }
        //Получение списка сотрудников для сотрудника.
        case MessageType::EMPLOYEE_TABLE_EMPLOYEES_DATA:
        {
            additionalForSendEmployeeTableEmployeesDataResult();
            break;
        }
        //Получение данных для формирования отчета.
        case MessageType::ADMIN_SAVE_REPORT:
        {
            additionalForSendAdminSaveReportResult(in);
            break;
        }
        //Получение результата удаления аномалии времени сотрудника.
        case MessageType::ADMIN_REMOVE_ANOMALY:
        {
            additionalForSendAdminRemoveAnomalyResult(in);
            break;
        }
        //Получение списка аномалий времени сотрудника.
        case MessageType::ADMIN_ANOMALY_DATA:
        {
            additionalForSendAdminAnomalyDataResult(in);
            break;
        }
        //Получение списка сотрудников для учета аномалий.
        case MessageType::ADMIN_EMPLOYEE_ANOMALY_DATA:
        {
            additionalForSendAdminEmployeeAnomalyDataResult(in);
            break;
        }
        //Получение результата удаления отпуска сотрудника.
        case MessageType::ADMIN_REMOVE_WEEKEND:
        {
            additionalForSendAdminRemoveWeekendResult(in);
            break;
        }
        //Получение результата работы с отпусками сотрудников.
        case MessageType::ADMIN_WORK_WITH_WEEKEND:
        {
            additionalForSendAdminWorkWithWeekendResult(in);
            break;
        }
        //Получение результата удаления графика сотрудника.
        case MessageType::ADMIN_REMOVE_GRAF:
        {
            additionalForSendAdminRemoveGrafResult(in);
            break;
        }
        //Получение результата работы с графиками сотрудников.
        case MessageType::ADMIN_WORK_WITH_GRAF:
        {
            additionalForSendAdminWorkWithGrafResult(in);
            break;
        }
        //Получени списка отпусков сотрудников.
        case MessageType::ADMIN_GET_EMPLOYEE_WEEKENDS:
        {
            additionalForSendAdminGetEmployeeWeekends(in);
            break;
        }
        //Получение списка графиков сотрудников.
        case MessageType::ADMIN_GET_EMPLOYEE_GRAFS:
        {
            additionalForSendAdminGetEmployeeGrafs(in);
            break;
        }
        //Получение списка сотрудников для настройка графика.
        case MessageType::ADMIN_GET_EMPLOYEE_DATA:
        {
            additionalForSendAdminGetEmployeeData(in);
            break;
        }
        //Получение списка проектных задач выполненного проекта.
        case MessageType::ADMIN_COMPLETE_TASKS:
        {
            additionalForSendAdminCompleteProjectTasksResult(in);
            break;
        }
        //Получение списка выполненных проектов.
        case MessageType::ADMIN_COMPLETE_PROJECTS:
        {
            additionalForSendAdminCompleteProjectsResult(in);
            break;
        }
        //Получение учетных данных администратора.
        case MessageType::ADMIN_CREDENTIALS_DATA:
        {
            additionalForSendAdminCredentialsData();
            break;
        }
        //Получение сотрудников.
        case MessageType::ADMIN_EMPLOYEE_DATA_TABLE:
        {
            additionalForGetEmployeeTableData(in);
            break;
        }
        //Удаление сотрудника.
        case MessageType::ADMIN_REMOVE_EMPLOYEE:
        {
            additionalForRemovedEmployeeResult(in);
            break;
        }
        //Изменение пользователя.
        case MessageType::ADMIN_CHANGE_EMPLOYEE_DATA:
        {
            additionalForChangeEmployeeResult(in);
            break;
        }
        //Получение запросов пользователей.
        case MessageType::ADMIN_GET_EMPLOYEE_REQUESTS:
        {
            additionalForGetEmployeeRequestsTableData(in);
            break;
        }
        //Получение статусов запросов.
        case MessageType::ADMIN_GET_EMPLOYEE_REQUEST_STATUSES:
        {
            additionalForGetRequestStatusesTableData();
            break;
        }
        //Закрытие запроса.
        case MessageType::ADMIN_CLOSE_EMPLOYEE_REQUEST:
        {
            additionalForCloseRequestResult(in);
            break;
        }
        //Повышение сотрудника.
        case MessageType::MAINADMIN_ADD_ADMIN:
        {
            additionalForAddAdminResult(in);
            break;
        }
        //Получение руководителей.
        case MessageType::MAINADMIN_ADMIN_DATA_TABLE:
        {
            additionalForGetAdminTableData();
            break;
        }
        case MessageType::MAINADMIN_REMOVE_ADMIN:
        {
            additionalForRemovedAdminResult(in);
            break;
        }
        //Изменение руководителя.
        case MessageType::MAINADMIN_CHANGE_ADMIN_DATA:
        {
            additionalForChangeAdminResult(in);
            break;
        }
        //Получение всех закрытых запросов пользователей.
        case MessageType::ADMIN_ALL_CLOSE_REQUESTS_DATA_TABLE:
        {
            additionalForAllClosedRequestsTableData();
            break;
        }
        //Получение всех проектов и задач.
        case MessageType::ADMIN_GET_PROJECT_TASK_DATA_TABLE:
        {
            additionalForAllProjectsAndTasksTableData(in);
            break;
        }
        //Информация о проектах для добавления.
        case MessageType::MAINADMIN_PROJECT_DATA_TABLE:
        {
            additionalForAddProjectTableData();
            break;
        }
        //Информация о проектах для добавления.
        case MessageType::MAINADMIN_ADD_PROJECT:
        {
            additionalForAddNewProjectResult(in);
            break;
        }
        //Информация о проектах для удаления/изменения.
        case MessageType::MAINADMIN_CHANGE_PROJECT_DATA_TABLE:
        {
            additionalForProjectForChangeTableData();
            break;
        }
        //Информация об удаляемом проекте.
        case MessageType::MAINADMIN_REMOVE_PROJECT:
        {
            additionalForRemovedProjectResult(in);
            break;
        }
        //Информация об изменяемом проекте.
        case MessageType::MAINADMIN_CHANGE_PROJECT:
        {
            additionalForChangedProjectResult(in);
            break;
        }
        //Получение информации о задачах.
        case MessageType::ADMIN_GET_TASK_DATA_TABLE:
        {
            additionalForGetTaskDataTable(in);
            break;
        }
        //Получение информации о сотрудниках для задач.
        case MessageType::ADMIN_GET_TASK_EMPLOYEE_DATA_TABLE:
        {
            additionalForGetEmployeeForTaskDataTable(in);
            break;
        }
        //Добавление новой задачи.
        case MessageType::ADMIN_ADD_TASK:
        {
            additionalForAddTask(in);
            break;
        }
        case MessageType::ADMIN_CHANGE_TASK:
        {
            additionalForChangedTaskResult(in);
            break;
        }
        //Информация об удаляемой задаче.
        case MessageType::ADMIN_REMOVE_TASK:
        {
            additionalForRemovedTaskResult(in);
            break;
        }
        //Информация об выводимом в работу проекте.
        case MessageType::MAINADMIN_WORK_PROJECT:
        {
            additionalForWorkedProjectResult(in);
            break;
        }
        //Информация об выводимой в работу задаче.
        case MessageType::ADMIN_WORK_TASK:
        {
            additionalForWorkedTaskResult(in);
            break;
        }
        //Информация о переназначении проекта руководителю.
        case MessageType::MAINADMIN_PROJECT_MANAGER_FOR_PROJECT:
        {
            additionalForProjectManagerForProjectResult(in);
            break;
        }
        //Информация о переназначении задачи сотруднику.
        case MessageType::ADMIN_EMPLOYEE_FOR_TASK:
        {
            additionalForEmployeeForTaskResult(in);
            break;
        }
        //Информация о переназначении задачи сотруднику.
        case MessageType::ADMIN_TEAM:
        {
            additionalForTeamTableData(in);
            break;
        }
        //Информация о всех онлайн пользователях.
        case MessageType::ADMIN_ONLINE_USERS:
        {
            additionalForOnlineTableData();
            break;
        }
        //Неизвестное сообщение.
        default:
        {
            qDebug() << "Ошибка! Неизвестный тип сообщения от клиента.";
            break;
        }
    }
    }
    else
    {
        qDebug() << "Ошибка DataStream! Невозможно прочитать данные из сокета.";
    }
}

void Server::sendErrorMessage(QString err_text)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ERROR);
    out << err_text;
    socket->write(Data);
    socket->flush();
}

void Server::sendAuthorizationResult(bool loginSuccess, bool pswdSuccess, QString userRole)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::AUTHORISATION);
    out << loginSuccess;
    out << pswdSuccess;
    out << userRole;
    socket->write(Data);
    socket->flush();
}

void Server::sendRegistrationResult(QMap<QString, bool> reg_success)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::REGISTRATION);
    for (auto it = reg_success.constBegin(); it != reg_success.constEnd(); ++it) {
        out << it.key() << it.value();
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeCreditalsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> creditals_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_CREDITALS_DATA);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : creditals_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeCompleteTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_COMPLETE_TASKS);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : complete_tasks) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeUnfinishedTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> unfinished_tasks)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_UNFINISHED_TASKS);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : unfinished_tasks) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeTimeData(QStringList time_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_GET_TIME_DATA);
    for(const QString& time: time_data) {
        out << time;
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeTableWorkGrafResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> work_graf_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_GET_WORK_GRAF);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : work_graf_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeTableTimeAnomaliesResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> time_anomalies_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_GET_TIME_ANOMALIES);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : time_anomalies_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendCheckEntryTimeDataResult(bool correct)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::TAKE_INTO_ENTRY_TIME);
    out << correct;
    socket->write(Data);
    socket->flush();
}

void Server::sendTakeIntoMainTimeResult(QString location)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::TAKE_INTO_MAIN_TIME);
    out << location;
    socket->write(Data);
    socket->flush();
}

void Server::sendRequestCategoriesResult(QStringList categories)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::REQUEST_CATEGORIES);
    out << categories;
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeReadyTaskRequestResult(bool correct)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_READYTASK_REQUEST);
    out << correct;
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeProjectsResult(QList<QStringList> projects)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_PROJECTS);
    for (const QStringList& project: projects){
        for (const QString& projectDetail : project){
            out << projectDetail;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeProjectTasksResult(QList<QStringList> project_tasks)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_PROJECT_TASKS);
    for (const QStringList& task: project_tasks){
        for (const QString& taskDetail : task){
            out << taskDetail;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeTaskNotesResult(QStringList task_emp_notes)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_NOTES);
    for (const QString& emp_note: task_emp_notes){
        out << emp_note;
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeSaveTaskNotesResult()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_SAVE_NOTES);
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeRequestsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_requests_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_REQUESTS_DATA);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : emp_requests_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeTableEmployeesDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::EMPLOYEE_TABLE_EMPLOYEES_DATA);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : employees_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminSaveReportResult(QString report)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    // Записываем тип сообщения
    out << static_cast<quint8>(MessageType::ADMIN_SAVE_REPORT);

    // Записываем зарезервированное место для длины данных
    out << quint16(0);

    // Записываем данные отчета в формате UTF-8
    QByteArray reportData = report.toUtf8();
    out.writeRawData(reportData.data(), reportData.size());

    // Возвращаемся назад, чтобы обновить длину данных
    quint16 dataSize = static_cast<quint16>(Data.size() - sizeof(quint8) - sizeof(quint16));
    out.device()->seek(sizeof(quint8)); // Смещение на длину типа сообщения
    out << dataSize;

    // Отправка данных
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminRemoveAnomalyDataResult(bool access)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_ANOMALY);
    out << access;
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminAnomalyDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> anomalies_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_ANOMALY_DATA);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : anomalies_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminEmployeeAnomalyDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_EMPLOYEE_ANOMALY_DATA);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : employees_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminRemoveWeekendResult(bool access)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_WEEKEND);
    out << access;
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminWorkWithWeekendResult(QString action, bool access)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_WORK_WITH_WEEKEND);
    out << action << access;
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminRemoveGrafResult(bool access)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_GRAF);
    out << access;
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminWorkWithGrafResult(QString action, bool access)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_WORK_WITH_GRAF);
    out << action << access;
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminGetEmployeeWeekendsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> weekends_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_WEEKENDS);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : weekends_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminGetEmployeeGrafsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> grafs_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_GRAFS);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : grafs_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminEmployeeDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_DATA);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : employees_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminCompleteProjectTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_COMPLETE_TASKS);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : complete_tasks_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminCompleteProjectsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_projs_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_COMPLETE_PROJECTS);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : complete_projs_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAdminCredentialsData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> credentials_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_CREDENTIALS_DATA);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : credentials_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendUsersTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_EMPLOYEE_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : users_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendRemovedUserResult(bool removing_success)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_EMPLOYEE);
    out << removing_success;
    socket->write(Data);
    socket->flush();
}

void Server::sendChangedEmployeeResult(QMap<QString, bool> change_employee_success)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_CHANGE_EMPLOYEE_DATA);
    for (auto it = change_employee_success.constBegin(); it != change_employee_success.constEnd(); ++it) {
        out << it.key() << it.value();
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_request_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_REQUESTS);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : emp_request_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendRequestObjectStatuses(QStringList requestObjectStatuses)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_EMPLOYEE_REQUEST_STATUSES);
    out << requestObjectStatuses;
    socket->write(Data);
    socket->flush();
}

void Server::sendUsersManagerTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_ADMIN_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : users_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendRemovedManagerResult(bool removing_success)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_REMOVE_ADMIN);
    out << removing_success;
    socket->write(Data);
    socket->flush();
}

void Server::sendAddedManResult(bool adding_success)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_ADD_ADMIN);
    out << adding_success;
    socket->write(Data);
    socket->flush();
}

void Server::sendChangedManagerResult(QMap<QString, bool> change_manager_success)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_CHANGE_ADMIN_DATA);
    for (auto it = change_manager_success.constBegin(); it != change_manager_success.constEnd(); ++it) {
        out << it.key() << it.value();
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAllClosedRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_ALL_CLOSE_REQUESTS_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : users_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAllProjectsTasks(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_PROJECT_TASK_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : projects_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendAddProjectDataRequest(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_PROJECT_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : projects_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendProjectsDataForChange(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_CHANGE_PROJECT_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : projects_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendRemoveChangeProjectCompleted()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_REMOVE_CHANGE_PROJECT_COMPLETE);
    socket->write(Data);
    socket->flush();
}

void Server::sendTasksTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> tasks_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_TASK_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : tasks_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendEmployeeForTasksTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_GET_TASK_EMPLOYEE_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : employees_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendRemoveChangeTaskCompleted()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_REMOVE_CHANGE_TASK_COMPLETE);
    socket->write(Data);
    socket->flush();
}

void Server::sendCloseRequestCompleted()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_CLOSE_REQUEST_COMPLETE);
    socket->write(Data);
    socket->flush();
}

void Server::sendAddProjectCompleted()
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::MAINADMIN_ADD_PROJECT_SUCCESS);
    socket->write(Data);
    socket->flush();
}

void Server::sendAddTaskCompleted(bool adding_success)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_ADD_TASK_SUCCESS);
    out << adding_success;
    socket->write(Data);
    socket->flush();
}

void Server::sendTeamDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> team_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_TEAM_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : team_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

void Server::sendOnlineDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> online_data)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << static_cast<quint8>(MessageType::ADMIN_ONLINE_DATA_TABLE);
    out << columnCount << rowCount;
    for (const QString& str : headerLabels){
        out << str;
    }
    for(const QStringList& innerList : online_data) {
        for(const QString& str : innerList) {
            out << str;
        }
    }
    socket->write(Data);
    socket->flush();
}

//ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ УПРОЩЕНИЯ slotReadyRead().
void Server::additionalForAuthorizationResult(QDataStream &in)
{
    QString login;
    QString pswd;
    in >> login >> pswd;
    query = new QSqlQuery(db);
    query->prepare("SELECT UserLogin, UserPswd, UserRole FROM dbo.Users WHERE UserLogin = :user_login");
    query->bindValue(":user_login", login);

    if (query->exec())
    {
        if (query->next())
        {
            QString storedPswd = query->value("UserPswd").toString();
            if (storedPswd == pswd)
            {
                QString user_role = query->value("UserRole").toString();
                query->prepare("UPDATE dbo.Users SET UserActivityID = 2 WHERE UserLogin = :user_login AND UserPswd = :user_pswd");
                query->bindValue(":user_login", login);
                query->bindValue(":user_pswd", pswd);
                if (query->exec()){
                    int userID = getUserID(query, login);
                    socketUserIDMap[socket] = userID;
                    sendAuthorizationResult(true, true, user_role);
                }
                else{
                    additionalForSendErrorMessage(query, "0x007");
                }
            }
            else
            {
                sendAuthorizationResult(true, false, "");
            }

        }
        else
        {
            sendAuthorizationResult(false, false, "");
        }
    }
    else
    {
        additionalForSendErrorMessage(query, "0x001");
    }

    delete query;
}

void Server::additionalForRegistrationResult(QDataStream &in)
{
    QMap<QString, bool> reg_success;
    QString firstName, lastName, middleName, jobTitle, personnelNumber, contactInfo, additionalInfo, login, password;
    in >> firstName >> lastName >> middleName >> jobTitle >> personnelNumber >> contactInfo >> additionalInfo >> login >> password;

    query = new QSqlQuery(db);
    reg_success["FirstName"] = isCyrillic(firstName);
    reg_success["LastName"] = isCyrillic(lastName);
    reg_success["MiddleName"] = middleName.isEmpty() || isCyrillic(middleName);
    reg_success["JobTitle"] = isCyrillic(jobTitle);
    reg_success["PersonnelNumber"] = (isNumeric(personnelNumber) && isUniquePersonnelNumber(personnelNumber.toInt(), query));
    reg_success["Login"] = isUniqueLogin(login, query);
    reg_success["Pswd"] = true;
    reg_success["ContactInformation"] = true;
    reg_success["AdditionalInfo"] = true;

    bool allValid = std::all_of(reg_success.constBegin(), reg_success.constEnd(),
                                [](const bool &value) { return value; });
    bool ready_to_send = true;
    if (allValid)
    {
        query->prepare("INSERT INTO dbo.Users (UserLogin, UserPswd, UserRole, UserActivityID) VALUES (?, ?, 'Employee', 1)");
        query->addBindValue(login);
        query->addBindValue(password);
        if (query->exec()){
            QString new_user_login = login;
            int newEmployeeID = getUserID(query, new_user_login);
            if (newEmployeeID == -1) {
                ready_to_send = false;
            }
            else{
                query->prepare("INSERT INTO dbo.Employees (EmployeeID, EmployeeFirstName, EmployeeLastName, EmployeeMiddleName, EmployeeJobTitle, EmployeePersonnelNumber, EmployeeContactInformation, EmployeeAdditionalInfo)"
                               " VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

                query->addBindValue(newEmployeeID);
                query->addBindValue(firstName);
                query->addBindValue(lastName);
                query->addBindValue(middleName);
                query->addBindValue(jobTitle);
                query->addBindValue(personnelNumber.toInt());
                query->addBindValue(contactInfo);
                query->addBindValue(additionalInfo);
                if (!query->exec()){
                    ready_to_send = false;
                    additionalForSendErrorMessage(query, "0x002");
                }
            }
        }
        else{
            ready_to_send = false;
            additionalForSendErrorMessage(query, "0x003");
        }
    }
    if (ready_to_send){
        sendRegistrationResult(reg_success);
    }
    delete query;
}

void Server::additionalForExitFromApp(QDataStream& in)
{
    QString login;
    QString pswd;
    in >> login >> pswd;
    query = new QSqlQuery(db);
    query->prepare("UPDATE dbo.Users SET UserActivityID = 1 WHERE UserLogin = :user_login AND UserPswd = :user_pswd");
    query->bindValue(":user_login", login);
    query->bindValue(":user_pswd", pswd);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "0x008");
    }
    else{
        QString userRole;
        QString str_userID = QString::number(socketUserIDMap[socket]);
        userRole = getUserRole(query, str_userID);
        if (userRole == "Employee" || this->manager_flag)
        {
            //Избавление от NULL при выходе из системы.
            query->prepare("UPDATE dbo.WorkTimeRecords "
                           "SET WorkTimeRecordEnd = :cur_time "
                           "WHERE WorkTimeRecordID IN "
                           "(SELECT WorkTimeRecordID "
                           "FROM WorkTimeRecords AS WTR "
                           "WHERE WTR.UserID = :user_id "
                           "AND WTR.WorkTimeRecordEnd IS NULL)");
            query->bindValue(":cur_time", QDateTime::currentDateTime().toString(Qt::ISODate));
            query->bindValue(":user_id", socketUserIDMap[socket]);
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x015");
            }
            else{
                int type_time = 15;
                query->prepare("INSERT INTO dbo.WorkTimeRecords (WorkTimeRecordBegin, WorkTimeRecordEnd, WorkTimeTypeID, UserID) "
                               "VALUES (?, ?, ?, ?)");
                query->addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
                query->addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
                query->addBindValue(type_time);
                query->addBindValue(socketUserIDMap[socket]);
                if (!query->exec()){
                    additionalForSendErrorMessage(query, "0x016");
                }
            }
            //Обработка исключительных ситуаций.
            std::pair<QVariant, bool> result = getEndCurrentDateSheduleTime(query);
            std::pair<QVariant, bool> result_begin = getBeginCurrentDateSheduleTime(query);
            if (result.second && result_begin.second)
            {
                QVariant dbTimeVariant = result.first;
                QVariant dbTimeVariantBegin =result_begin.first;
                if (dbTimeVariant.isNull()) {
                    query->prepare("SELECT * FROM dbo.Vacations WHERE :current_date BETWEEN VacationBeginDate AND VacationEndDate AND UserID = :user_id");
                    query->bindValue(":current_date", QDate::currentDate());
                    query->bindValue(":user_id", socketUserIDMap[socket]);
                    if (!query->exec()){
                        additionalForSendErrorMessage(query, "0x018");
                    }
                    else{
                        if (query->next()){
                            //Отпуск.
                            query->prepare("UPDATE dbo.WorkTimeAnomalyRecords "
                                           "SET WorkTimeAnomalyRecordEnd = :cur_datetime WHERE WorkTimeAnomalyRecordEnd IS NULL AND WorkTimeAnomalyID = 2 AND UserID = :user_id ");
                            query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                            query->bindValue(":user_id", socketUserIDMap[socket]);
                            if (!query->exec()){
                                additionalForSendErrorMessage(query, "0x023");
                            }
                        }
                        else{
                            //Выходной.
                            query->prepare("UPDATE dbo.WorkTimeAnomalyRecords "
                                           "SET WorkTimeAnomalyRecordEnd = :cur_datetime WHERE WorkTimeAnomalyRecordEnd IS NULL AND WorkTimeAnomalyID = 1 AND UserID = :user_id ");
                            query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                            query->bindValue(":user_id", socketUserIDMap[socket]);
                            if (!query->exec()){
                                additionalForSendErrorMessage(query, "0x024");
                            }
                        }
                    }
                } else {
                    QString dbTime = dbTimeVariant.toString();
                    QTime currentTime = QTime::currentTime();
                    QTime dbTimeParsed = QTime::fromString(dbTime, "hh:mm:ss.zzz");
                    QDateTime combinedDateTime(QDate::currentDate(), dbTimeParsed);
                    //
                    QString dbTimeBegin = dbTimeVariantBegin.toString();
                    QTime dbTimeBeginParsed = QTime::fromString(dbTimeBegin, "hh:mm:ss.zzz");
                    //
                    int differenceMinutes = currentTime.msecsTo(dbTimeParsed) / 60000;
                    if (currentTime < dbTimeParsed && currentTime > dbTimeBeginParsed) {
                        if (differenceMinutes > 5){
                            //Недоработка.
                            query->prepare("INSERT INTO dbo.WorkTimeAnomalyRecords (WorkTimeAnomalyRecordBegin, WorkTimeAnomalyID, UserID, WorkTimeAnomalyRecordEnd) "
                                           "VALUES (:cur_datetime, 4, :user_id, :graf_datetime)");
                            query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                            query->bindValue(":user_id", socketUserIDMap[socket]);
                            query->bindValue(":graf_datetime", combinedDateTime.toString(Qt::ISODate));
                            if (!query->exec()){
                                additionalForSendErrorMessage(query, "0x025");
                            }
                        }
                    }
                    else if (currentTime <= dbTimeBeginParsed)
                    {
                        //Закрытие позиций переработок до рабочего времени.
                        query->prepare("UPDATE dbo.WorkTimeAnomalyRecords "
                                       "SET WorkTimeAnomalyRecordEnd = :cur_datetime "
                                       "WHERE WorkTimeAnomalyRecordID = ("
                                       "SELECT TOP 1 WorkTimeAnomalyRecordID "
                                       "FROM dbo.WorkTimeAnomalyRecords "
                                       "WHERE UserID = :user_id AND WorkTimeAnomalyID = 5 "
                                       "ORDER BY WorkTimeAnomalyRecordBegin DESC"
                                       ") AND UserID = :user_id");
                        query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                        query->bindValue(":user_id", socketUserIDMap[socket]);
                        if (!query->exec()) {
                            additionalForSendErrorMessage(query, "0x030");
                        }
                    }
                    else if (currentTime >= dbTimeParsed){
                        //Закрытие позиций переработок после рабочего времени.
                        //Проверка, осуществляется ли выход с наличием выходов или без.
                        query->prepare("SELECT TOP 1 WorkTimeAnomalyRecordBegin, WorkTimeAnomalyID "
                                       "FROM dbo.WorkTimeAnomalyRecords "
                                       "WHERE UserID = :user_id "
                                       "AND CAST(WorkTimeAnomalyRecordBegin AS DATE) = CAST(GETDATE() AS DATE) "
                                       "AND WorkTimeAnomalyRecordEnd IS NULL "
                                       "AND WorkTimeAnomalyID = 6 "
                                       "ORDER BY WorkTimeAnomalyRecordBegin DESC");
                        query->bindValue(":user_id", socketUserIDMap[socket]);
                        if (!query->exec()){
                            additionalForSendErrorMessage(query, "0x049");
                        }
                        else{
                            bool exitFlag = false;
                            if (query->next()){
                                exitFlag = true;
                            }
                            if (exitFlag){
                                query->prepare("UPDATE dbo.WorkTimeAnomalyRecords "
                                               "SET WorkTimeAnomalyRecordEnd = :cur_datetime "
                                               "WHERE WorkTimeAnomalyRecordID = ("
                                               "SELECT TOP 1 WorkTimeAnomalyRecordID "
                                               "FROM dbo.WorkTimeAnomalyRecords "
                                               "WHERE UserID = :user_id AND WorkTimeAnomalyID = 6 "
                                               "ORDER BY WorkTimeAnomalyRecordBegin DESC"
                                               ") AND UserID = :user_id");
                                query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                                query->bindValue(":user_id", socketUserIDMap[socket]);
                                if (!query->exec()) {
                                    additionalForSendErrorMessage(query, "0x030");
                                }
                            }
                            else{
                                if (differenceMinutes < -5)
                                {
                                    query->prepare("INSERT INTO dbo.WorkTimeAnomalyRecords (WorkTimeAnomalyRecordBegin, WorkTimeAnomalyID, UserID, WorkTimeAnomalyRecordEnd) "
                                                   "VALUES (:graf_datetime, 6, :user_id, :cur_datetime)");
                                    query->bindValue(":graf_datetime", combinedDateTime.toString(Qt::ISODate));
                                    query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                                    query->bindValue(":user_id", socketUserIDMap[socket]);
                                    if (!query->exec()) {
                                        additionalForSendErrorMessage(query, "0x050");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    delete query;
}

void Server::additionalForSendRequestCategoriesResult()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT RequestCategoryName FROM RequestCategories");
    if (!query->exec()) {
        additionalForSendErrorMessage(query, "1x001");
    }
    else
    {
        QStringList requestCategoryNames;
        while (query->next()) {
            QString categoryName = query->value("RequestCategoryName").toString();
            requestCategoryNames.append(categoryName);
        }
        sendRequestCategoriesResult(requestCategoryNames);
    }

    delete query;
}

void Server::additionalForEmployeeRequestResult(QDataStream& in)
{
    QString type_request;
    QString text;
    in >> type_request >> text;
    query = new QSqlQuery(db);
    query->prepare("SELECT RequestCategoryID FROM RequestCategories WHERE RequestCategoryName = :category_name");
    query->bindValue(":category_name", type_request);
    if (!query->exec() || !query->next()) {
        additionalForSendErrorMessage(query, "1x002");
    }
    else
    {
        int categoryID;
        categoryID = query->value(0).toInt();
        query->prepare("INSERT INTO EmployeeRequests (EmployeeRequestText, EmployeeRequestStatusID, UserID, RequestCategoryID) VALUES (?, 3, ?, ?)");
        query->addBindValue(text);
        query->addBindValue(socketUserIDMap[socket]);
        query->addBindValue(categoryID);
        if (!query->exec()){
            additionalForSendErrorMessage(query, "1x003");
        }
    }
    delete query;
}

void Server::additionalForSendEmployeeProjectsResult()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT p.ProjectName, p.ProjectDescription, a.AdminLastName, a.AdminFirstName, a.AdminMiddleName, os.ObjectStatusText "
                   "FROM dbo.Users u INNER JOIN dbo.Projects p ON u.UserID = p.ProjectManagerID INNER JOIN dbo.Administrators a ON a.AdminID = u.UserID "
                   "INNER JOIN dbo.ObjectStatuses os ON p.ProjectStatusID = os.ObjectStatusID WHERE os.ObjectStatusText != 'Завершено' AND os.ObjectStatusText != 'В разработке...'");
    if (query->exec()){
        QList<QStringList> projects;
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                if (i == 2){
                    rowValues.append(QString("%1 %2 %3").arg(query->value(2).toString(), query->value(3).toString(), query->value(4).toString()));
                } else if (i == 3 || i == 4){
                    continue;
                }
                else {
                    rowValues.append(query->value(i).toString());
                }
            }
            projects.append(rowValues);
        }
        sendEmployeeProjectsResult(projects);
    }
    else{
        additionalForSendErrorMessage(query, "1x004");
    }
    delete query;
}

void Server::additionalForSendEmployeeProjectTasksResult(QDataStream& in)
{
    QString proj_name;
    in >> proj_name;
    query = new QSqlQuery(db);
    query->prepare("SELECT pt.ProjectTaskName, pt.ProjectTaskDescription, e.EmployeeLastName, e.EmployeeFirstName, e.EmployeeMiddleName, os.ObjectStatusText "
                   "FROM ProjectTasks pt INNER JOIN Employees e ON e.EmployeeID = pt.ProjectTaskAssigneeID "
                   "INNER JOIN ObjectStatuses os ON pt.ProjectTaskStatusID = os.ObjectStatusID "
                   "INNER JOIN Projects p ON p.ProjectID = pt.ProjectID WHERE p.ProjectName = :proj_name AND os.ObjectStatusText != 'В разработке...' ");
    query->bindValue(":proj_name", proj_name);
    if (query->exec()){
        QList<QStringList> proj_tasks;
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                if (i == 2){
                    rowValues.append(QString("%1 %2 %3").arg(query->value(2).toString(), query->value(3).toString(), query->value(4).toString()));
                } else if (i == 3 || i == 4){
                    continue;
                }
                else {
                    rowValues.append(query->value(i).toString());
                }
            }
            proj_tasks.append(rowValues);
        }
        bool ready_to_send = true;
        for (int j = 0; j < proj_tasks.size(); ++j) {
            QString proj_task_name = proj_tasks[j][0];
            query->prepare("SELECT ProjectTaskAssigneeID FROM dbo.ProjectTasks WHERE ProjectTaskName = :proj_task_name");
            query->bindValue(":proj_task_name", proj_task_name);
            if (query->exec())
            {
                if (query->next()){
                    int assigneeID = query->value(0).toInt();
                    bool isAssignee = (assigneeID == socketUserIDMap[socket]);
                    proj_tasks[j].append(isAssignee ? "true" : "false");
                } else {
                    proj_tasks[j].append("false");
                }
            }
            else{
                ready_to_send = false;
                additionalForSendErrorMessage(query, "1x006");
            }
        }
        if (ready_to_send)
            sendEmployeeProjectTasksResult(proj_tasks);
    }
    else{
        additionalForSendErrorMessage(query, "1x005");
    }
    delete query;
}

void Server::additionalForSendEmployeeReadyTaskRequestResult(QDataStream &in)
{
    QString task_data;
    in >> task_data;
    query = new QSqlQuery(db);
    query->prepare("SELECT COUNT(*) AS RequestsCount FROM dbo.EmployeeRequests er "
                   "INNER JOIN dbo.ObjectStatuses os ON er.EmployeeRequestStatusID = os.ObjectStatusID "
                   "INNER JOIN dbo.RequestCategories rc ON er.RequestCategoryID = rc.RequestCategoryID "
                   "WHERE er.UserID = :userID AND er.EmployeeRequestText LIKE :text "
                   "AND  rc.RequestCategoryName = 'Выполнение проектной задачи' "
                   "AND (os.ObjectStatusText = 'Ожидание' OR os.ObjectStatusText = 'Принято')");
    query->bindValue(":userID", socketUserIDMap[socket]);
    query->bindValue(":text", task_data);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x014");
    }
    else{
        if (query->next() && query->value("RequestsCount").toInt() > 0)
            sendEmployeeReadyTaskRequestResult(false);
        else{
            query->prepare("SELECT RequestCategoryID FROM RequestCategories WHERE RequestCategoryName = 'Выполнение проектной задачи'");
            if (!query->exec() || !query->next()) {
                additionalForSendErrorMessage(query, "1x015");
            }
            else
            {
                int categoryID;
                categoryID = query->value(0).toInt();
                query->prepare("INSERT INTO EmployeeRequests (EmployeeRequestText, EmployeeRequestStatusID, UserID, RequestCategoryID) VALUES (?, 3, ?, ?)");
                query->addBindValue(task_data);
                query->addBindValue(socketUserIDMap[socket]);
                query->addBindValue(categoryID);
                if (!query->exec()){
                    additionalForSendErrorMessage(query, "1x016");
                }
                else{
                    sendEmployeeReadyTaskRequestResult(true);
                }
            }
        }
    }
    delete query;
}

void Server::additionalForSendEmployeeTaskNotesResult(QDataStream &in)
{
    QString task_name;
    in >> task_name;
    query = new QSqlQuery(db);
    query->prepare("SELECT EmployeeNoteText FROM dbo.EmployeeNotes en INNER JOIN dbo.ProjectTasks pt ON en.ProjectTaskID = pt.ProjectTaskID "
                   "WHERE pt.ProjectTaskName = ? AND en.UserID = ?");
    query->addBindValue(task_name);
    query->addBindValue(socketUserIDMap[socket]);
    if (query->exec()){
        QStringList task_emp_notes;
        while (query->next()){
            task_emp_notes.append(query->value(0).toString());
        }
        sendEmployeeTaskNotesResult(task_emp_notes);
    }
    else{
        additionalForSendErrorMessage(query, "1x007");
    }
    delete query;
}

void Server::additionalForSendEmployeeSaveTaskNotesResult(QDataStream &in)
{
    query = new QSqlQuery(db);
    QString task_name;
    in >> task_name;
    QStringList new_emp_notes;
    while(!in.atEnd()){
        QString new_emp_note;
        in >> new_emp_note;
        new_emp_notes.append(new_emp_note);
    }
    QString taskID = getProjTaskID(query, task_name);
    if (taskID.isEmpty()){
        additionalForSendErrorMessage(query, "1x010");
    }
    else
    {
        query->prepare("DELETE FROM dbo.EmployeeNotes WHERE UserID = ? AND ProjectTaskID = ?");
        query->addBindValue(socketUserIDMap[socket]);
        query->addBindValue(taskID.toInt());
        if (query->exec())
        {
            bool ready_to_send = true;
            for (const QString& new_emp_note : new_emp_notes){
                if (!new_emp_note.isEmpty())
                {
                    query->prepare("INSERT INTO dbo.EmployeeNotes (EmployeeNoteText, UserID, ProjectTaskID) VALUES (?, ?, ?)");
                    query->addBindValue(new_emp_note);
                    query->addBindValue(socketUserIDMap[socket]);
                    query->addBindValue(taskID.toInt());
                    if (!query->exec()){
                        additionalForSendErrorMessage(query, "1x011");
                        ready_to_send = false;
                        break;
                    }
                }
            }
            if (ready_to_send)
                sendEmployeeSaveTaskNotesResult();
        }
        else{
            additionalForSendErrorMessage(query, "1x008");
        }
    }
    delete query;
}

void Server::additionalForSendEmployeeRequestsDataResult(QDataStream &in)
{
    QString category_name;
    in >> category_name;
    query = new QSqlQuery(db);
    query->prepare("SELECT er.EmployeeRequestID, er.EmployeeRequestText, am.AdminMessageText, os.ObjectStatusText FROM dbo.EmployeeRequests er "
                   "LEFT JOIN dbo.AdminMessages am ON er.AdminMessageID = am.AdminMessageID "
                   "INNER JOIN dbo.RequestCategories rc ON er.RequestCategoryID = rc.RequestCategoryID "
                   "INNER JOIN dbo.ObjectStatuses os ON er.EmployeeRequestStatusID = os.ObjectStatusID "
                   "WHERE rc.RequestCategoryName = ? AND er.UserID = ?");
    query->addBindValue(category_name);
    query->addBindValue(socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x012");
    }
    else{
        QList<QStringList> emp_requests_data;
        QStringList headerLabels;
        headerLabels << "Номер вашего запроса в системе" << "Текст Вашего запроса" << "Ответ администратора" << "Статус запроса";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            emp_requests_data.append(rowValues);
        }
        sendEmployeeRequestsDataResult(headerLabels, columnCount, emp_requests_data.size(), emp_requests_data);
    }
    delete query;
}

void Server::additionalForSendEmployeeTableEmployeesDataResult()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT e.EmployeePersonnelNumber, os.ObjectStatusText, "
                   "CONCAT(e.EmployeeLastName, ' ', e.EmployeeFirstName, ' ', e.EmployeeMiddleName) AS FullName, "
                   "e.EmployeeContactInformation, p.ProjectName, pt.ProjectTaskName "
                   "FROM dbo.Employees e "
                   "INNER JOIN dbo.Users u ON e.EmployeeID = u.UserID "
                   "INNER JOIN dbo.ProjectTasks pt ON pt.ProjectTaskAssigneeID = u.UserID "
                   "INNER JOIN dbo.Projects p ON p.ProjectID = pt.ProjectID "
                   "INNER JOIN dbo.ObjectStatuses os ON os.ObjectStatusID = u.UserActivityID "
                   "WHERE e.EmployeeID IN ( "
                   "    SELECT e2.EmployeeID "
                   "    FROM dbo.Employees e2 "
                   "    INNER JOIN dbo.ProjectTasks pt2 ON pt2.ProjectTaskAssigneeID = e2.EmployeeID "
                   "    INNER JOIN dbo.Projects p2 ON p2.ProjectID = pt2.ProjectID "
                   "    WHERE p2.ProjectID IN ( "
                   "        SELECT p3.ProjectID "
                   "        FROM dbo.ProjectTasks pt3 "
                   "        INNER JOIN dbo.Projects p3 ON p3.ProjectID = pt3.ProjectID "
                   "        WHERE pt3.ProjectTaskAssigneeID = :employeeID "
                   "    ) "
                   "    AND e2.EmployeeID != :employeeID "
                   ")");
    query->bindValue(":employeeID", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x013");
    }
    else{
        QList<QStringList> employees_data;
        QStringList headerLabels;
        headerLabels << "Табельный номер сотрудника" << "Статус сотрудника" << "ФИО сотрудника" << "Контактная информация сотрудника" <<
            "Проект" << "Проектная задача";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            employees_data.append(rowValues);
        }
        sendEmployeeTableEmployeesDataResult(headerLabels, columnCount, employees_data.size(), employees_data);
    }
    delete query;
}

void Server::additionalForSendAdminSaveReportResult(QDataStream &in)
{
    QString employee_id, dateStartString, dateFinishString;
    in >> employee_id >> dateStartString >> dateFinishString;
    QDate dateStart = QDate::fromString(dateStartString, "yyyy-MM-dd");
    QDate dateFinish = QDate::fromString(dateFinishString, "yyyy-MM-dd");

    QString report;
    query = new QSqlQuery(db);

    // Получение данных сотрудника
    if (!fetchEmployeeInfo(query, employee_id, report, dateStart, dateFinish)) {
        return;
    }

    // Получение выполненных проектных задач
    if (!fetchCompletedProjectTasks(query, employee_id, report)) {
        return;
    }

    // Получение опозданий, переработок, недоработок и общего времени работы
    if (!fetchWorkTimeAnomalies(query, employee_id, dateStart, dateFinish, report)) {
        return;
    }

    // Получение исключительных ситуаций
    if (!fetchExceptionalSituations(query, employee_id, dateStart, dateFinish, report)) {
        return;
    }

    // Регистрация времени
    if (!fetchWorkTimeRecords(query, employee_id, dateStart, dateFinish, report)) {
        return;
    }

    sendAdminSaveReportResult(report);
    delete query;
}

bool Server::fetchEmployeeInfo(QSqlQuery* query, const QString &employee_id, QString &report, const QDate &dateStart, const QDate &dateFinish)
{
    query->prepare("SELECT EmployeeFirstName, EmployeeLastName, EmployeeMiddleName, EmployeeJobTitle, EmployeeContactInformation, EmployeeAdditionalInfo "
                  "FROM Employees WHERE EmployeeID = :employee_id");
    query->bindValue(":employee_id", employee_id);

    if (!query->exec() || !query->next()) {
        additionalForSendErrorMessage(query, "2x047");
        return false;
    }

    QString firstName = query->value(0).toString();
    QString lastName = query->value(1).toString();
    QString middleName = query->value(2).toString();
    QString jobTitle = query->value(3).toString();
    QString contactInfo = query->value(4).toString();
    QString additionalInfo = query->value(5).toString();

    report.append(QString("Начало формирования отчета: %1\n").arg(dateStart.toString("yyyy-MM-dd")));
    report.append(QString("Конец формирования отчета: %1\n").arg(dateFinish.toString("yyyy-MM-dd")));
    report.append(QString("Дата формирования отчета: %1\n\n").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    report.append("Информация о сотруднике:\n");
    report.append(QString("ФИО: %1 %2 %3\n").arg(lastName, firstName, middleName));
    report.append(QString("Должность: %1\n").arg(jobTitle));
    report.append(QString("Контактная информация: %1\n").arg(contactInfo));
    report.append(QString("Дополнительная информация: %1\n\n").arg(additionalInfo));

    return true;
}

bool Server::fetchCompletedProjectTasks(QSqlQuery* query, const QString &employee_id, QString &report)
{
    query->prepare("SELECT CONCAT(a.AdminLastName, ' ', a.AdminFirstName, ' ', a.AdminMiddleName), P.ProjectName, "
                  "PT.ProjectTaskName, PT.ProjectTaskDescription, os.ObjectStatusText "
                  "FROM ProjectTasks PT "
                  "JOIN Projects P ON P.ProjectID = PT.ProjectID "
                  "JOIN ObjectStatuses os ON os.ObjectStatusID = PT.ProjectTaskStatusID "
                  "JOIN Administrators a ON a.AdminID = P.ProjectManagerID "
                  "WHERE PT.ProjectTaskAssigneeID = :employee_id AND os.ObjectStatusID = 6");
    query->bindValue(":employee_id", employee_id);

    if (!query->exec()) {
        additionalForSendErrorMessage(query, "2x048");
        return false;
    }

    report.append("Выполненные проектные задачи:\n");
    while (query->next()) {
        QString managerName = query->value(0).toString();
        QString projName = query->value(1).toString();
        QString taskName = query->value(2).toString();
        QString taskDescription = query->value(3).toString();
        QString taskStatus = query->value(4).toString();

        report.append(QString("ФИО Руководителя: %1\n").arg(managerName));
        report.append(QString("Название проекта: %1\n").arg(projName));
        report.append(QString("Название задачи: %1\n").arg(taskName));
        report.append(QString("Описание задачи: %1\n").arg(taskDescription));
        report.append(QString("Статус задачи: %1\n\n").arg(taskStatus));
    }

    return true;
}

bool Server::fetchWorkTimeAnomalies(QSqlQuery* query, const QString &employee_id, const QDate &dateStart, const QDate &dateFinish, QString &report)
{
    query->prepare("SELECT "
                  "SUM(CASE WHEN WorkTimeAnomalyID = 4 THEN ABS(DATEDIFF(MINUTE, WorkTimeAnomalyRecordBegin, WorkTimeAnomalyRecordEnd)) ELSE 0 END) AS TotalMinutes_Delay, "
                  "SUM(CASE WHEN WorkTimeAnomalyID = 3 THEN ABS(DATEDIFF(MINUTE, WorkTimeAnomalyRecordEnd, WorkTimeAnomalyRecordBegin)) ELSE 0 END) AS TotalMinutes_Late, "
                  "SUM(CASE WHEN WorkTimeAnomalyID IN (1, 2) THEN ABS(DATEDIFF(MINUTE, WorkTimeAnomalyRecordEnd, WorkTimeAnomalyRecordBegin)) ELSE 0 END) AS TotalMinutes_Overtime, "
                  "COUNT(CASE WHEN WorkTimeAnomalyID = 4 THEN 1 END) AS AnomalyCount_Delay, "
                  "COUNT(CASE WHEN WorkTimeAnomalyID = 3 THEN 1 END) AS AnomalyCount_Late, "
                  "COUNT(CASE WHEN WorkTimeAnomalyID IN (1, 2) THEN 1 END) AS AnomalyCount_Overtime "
                  "FROM WorkTimeAnomalyRecords "
                  "WHERE UserID = :user_id AND "
                  "(WorkTimeAnomalyID IN (4, 3, 1, 2)) AND "
                  "WorkTimeAnomalyRecordBegin IS NOT NULL AND "
                  "WorkTimeAnomalyRecordEnd IS NOT NULL "
                  "AND CONVERT(DATE, WorkTimeAnomalyRecordBegin) >= :dateStart "
                  "AND CONVERT(DATE, WorkTimeAnomalyRecordEnd) <= :dateFinish");
    query->bindValue(":user_id", employee_id);
    query->bindValue(":dateStart", dateStart);
    query->bindValue(":dateFinish", dateFinish);

    if (!query->exec() || !query->next()) {
        additionalForSendErrorMessage(query, "2x053");
        return false;
    }

    int total_minutes_delay = query->value("TotalMinutes_Delay").toInt();
    int total_minutes_late = query->value("TotalMinutes_Late").toInt();
    int total_minutes_overtime = query->value("TotalMinutes_Overtime").toInt();
    int anomaly_count_delay = query->value("AnomalyCount_Delay").toInt();
    int anomaly_count_late = query->value("AnomalyCount_Late").toInt();
    int anomaly_count_overtime = query->value("AnomalyCount_Overtime").toInt();

    report.append(QString("Недоработки. Количество: %1 Время: %2:%3\n")
                      .arg(anomaly_count_delay)
                      .arg(total_minutes_delay / 60, 2, 10, QChar('0'))
                      .arg(total_minutes_delay % 60, 2, 10, QChar('0')));
    report.append(QString("Опоздания. Количество: %1 Время: %2:%3\n")
                      .arg(anomaly_count_late)
                      .arg(total_minutes_late / 60, 2, 10, QChar('0'))
                      .arg(total_minutes_late % 60, 2, 10, QChar('0')));
    report.append(QString("Переработки. Количество: %1 Время: %2:%3\n")
                      .arg(anomaly_count_overtime)
                      .arg(total_minutes_overtime / 60, 2, 10, QChar('0'))
                      .arg(total_minutes_overtime % 60, 2, 10, QChar('0')));

    // Общее время работы
    query->prepare("SELECT SUM(DATEDIFF(minute, WorkTimeRecordBegin, WorkTimeRecordEnd)) AS TotalWorkTime "
                  "FROM WorkTimeRecords "
                  "WHERE UserID = :user_id "
                  "    AND CONVERT(date, WorkTimeRecordBegin) >= :dateStart "
                  "    AND CONVERT(date, WorkTimeRecordEnd) <= :dateFinish "
                  "GROUP BY UserID");
    query->bindValue(":user_id", employee_id);
    query->bindValue(":dateStart", dateStart);
    query->bindValue(":dateFinish", dateFinish);

    if (!query->exec() || !query->next()) {
        additionalForSendErrorMessage(query, "2x054");
        return false;
    }

    int total_work_time = query->value("TotalWorkTime").toInt();
    int total_hours = total_work_time / 60;
    int total_minutes = total_work_time % 60;
    report.append(QString("Общее время работы: %1:%2\n\n")
                      .arg(total_hours, 2, 10, QChar('0'))
                      .arg(total_minutes, 2, 10, QChar('0')));

    return true;
}

bool Server::fetchExceptionalSituations(QSqlQuery* query, const QString &employee_id, const QDate &dateStart, const QDate &dateFinish, QString &report)
{
    query->prepare("SELECT WTAR.WorkTimeAnomalyRecordBegin, WTAR.WorkTimeAnomalyRecordEnd, WTA.WorkTimeAnomalyDescription "
                  "FROM dbo.WorkTimeAnomalyRecords WTAR "
                  "INNER JOIN dbo.WorkTimeAnomalies WTA ON WTAR.WorkTimeAnomalyID = WTA.WorkTimeAnomalyID "
                  "WHERE WTAR.UserID = :user_id "
                  "    AND CONVERT(date, WTAR.WorkTimeAnomalyRecordBegin) >= :dateStart "
                  "    AND CONVERT(date, WTAR.WorkTimeAnomalyRecordEnd) <= :dateFinish");
    query->bindValue(":user_id", employee_id);
    query->bindValue(":dateStart", dateStart);
    query->bindValue(":dateFinish", dateFinish);

    if (!query->exec()) {
        additionalForSendErrorMessage(query, "2x055");
        return false;
    }

    report.append("Исключительные ситуации:\n");
    while (query->next()) {
        QDateTime anomalyBegin = query->value(0).toDateTime();
        QDateTime anomalyEnd = query->value(1).toDateTime();
        QString anomalyDescription = query->value(2).toString();

        report.append(QString("Начало искл. ситуации: %1\n").arg(anomalyBegin.toString("dd.MM.yyyy hh:mm:ss")));
        report.append(QString("Конец искл. ситуации: %1\n").arg(anomalyEnd.toString("dd.MM.yyyy hh:mm:ss")));
        report.append(QString("Описание: %1\n\n").arg(anomalyDescription));
    }

    return true;
}

bool Server::fetchWorkTimeRecords(QSqlQuery* query, const QString &employee_id, const QDate &dateStart, const QDate &dateFinish, QString &report)
{
    query->prepare("SELECT "
                  "WTR.WorkTimeRecordID, "
                  "WTR.WorkTimeRecordBegin, "
                  "WTR.WorkTimeRecordEnd, "
                  "WTT.WorkTimeTypeDescription "
                  "FROM WorkTimeRecords WTR "
                  "JOIN WorkTimeTypes WTT ON WTR.WorkTimeTypeID = WTT.WorkTimeTypeID "
                  "WHERE WTR.UserID = :user_id "
                  "AND CONVERT(date, WTR.WorkTimeRecordBegin) >= :dateStart "
                  "AND CONVERT(date, WTR.WorkTimeRecordEnd) <= :dateFinish "
                  "ORDER BY WTR.WorkTimeRecordBegin");
    query->bindValue(":user_id", employee_id);
    query->bindValue(":dateStart", dateStart);
    query->bindValue(":dateFinish", dateFinish);

    if (!query->exec()) {
        additionalForSendErrorMessage(query, "2x056");
        return false;
    }

    report.append("Регистрация времени:\n");
    while (query->next()) {
        QString recordID = query->value(0).toString();
        QDateTime recordBegin = query->value(1).toDateTime();
        QDateTime recordEnd = query->value(2).toDateTime();
        QString description = query->value(3).toString();

        report.append(QString("ID записи: %1\n").arg(recordID));
        report.append(QString("Начало регистрации времени: %1\n").arg(recordBegin.toString("dd.MM.yyyy hh:mm:ss")));
        report.append(QString("Конец регистрации времени: %1\n").arg(recordEnd.toString("dd.MM.yyyy hh:mm:ss")));
        report.append(QString("Описание: %1\n\n").arg(description));
    }

    return true;
}

void Server::additionalForSendAdminRemoveAnomalyResult(QDataStream &in)
{
    bool access = true;
    QString anomaly_id;
    in >> anomaly_id;
    query = new QSqlQuery(db);
    //Можно добавить дополнительную обработку возможности удаления аномалии времени сотрудника.
    query->prepare("DELETE FROM WorkTimeAnomalyRecords WHERE WorkTimeAnomalyRecordID = :anomalyID");
    query->bindValue(":anomalyID", anomaly_id);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x045");
    }
    else{
        sendAdminRemoveAnomalyDataResult(access);
    }
    delete query;
}

void Server::additionalForSendAdminAnomalyDataResult(QDataStream &in)
{
    QString emp_id;
    in >> emp_id;
    query = new QSqlQuery(db);
    query->prepare("SELECT "
                   "WTA.WorkTimeAnomalyRecordID, "
                   "WTA.WorkTimeAnomalyRecordBegin, "
                   "WTA.WorkTimeAnomalyRecordEnd, "
                   "WTADesc.WorkTimeAnomalyDescription "
                   "FROM WorkTimeAnomalyRecords WTA "
                   "JOIN  WorkTimeAnomalies WTADesc ON WTA.WorkTimeAnomalyID = WTADesc.WorkTimeAnomalyID "
                   "JOIN  Users U ON WTA.UserID = U.UserID "
                   "WHERE "
                   "u.UserID = :employeeID "
                   "AND WTA.WorkTimeAnomalyRecordBegin IS NOT NULL "
                   "AND WTA.WorkTimeAnomalyRecordEnd IS NOT NULL "
                   "ORDER BY "
                   "WTA.WorkTimeAnomalyRecordBegin DESC");
    query->bindValue(":employeeID", emp_id.toInt());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x044");
    }
    else{
        QList<QStringList> anomalies_data;
        QStringList headerLabels;
        headerLabels << "ID аномалии" << "Начало регистрации" << "Конец регистрации" << "Описание аномалии";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue;
                if (i == 0 || i == 3){
                    rowValue = query->value(i).toString();
                }
                else{
                    QDateTime anomalyBeginEndTime = query->value(i).toDateTime();
                    rowValue = anomalyBeginEndTime.toString("dd.MM.yyyy hh:mm:ss");
                }
                rowValues.append(rowValue);
            }
            anomalies_data.append(rowValues);
        }
        sendAdminAnomalyDataResult(headerLabels, columnCount, anomalies_data.size(), anomalies_data);
    }
    delete query;
}

void Server::additionalForSendAdminEmployeeAnomalyDataResult(QDataStream &in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT DISTINCT E.EmployeeID, E.EmployeeLastName, E.EmployeeFirstName, E.EmployeeMiddleName, os.ObjectStatusText "
                       "FROM Employees E JOIN Users U ON E.EmployeeID = U.UserID "
                       "JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID ");
    }
    else{
        query->prepare("SELECT DISTINCT E.EmployeeID, E.EmployeeLastName, E.EmployeeFirstName, E.EmployeeMiddleName, os.ObjectStatusText "
                       "FROM Employees E JOIN Users U ON E.EmployeeID = U.UserID "
                       "JOIN ProjectTasks PT ON U.UserID = PT.ProjectTaskAssigneeID "
                       "JOIN Projects P ON PT.ProjectID = P.ProjectID "
                       "JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID "
                       "WHERE P.ProjectManagerID = :user_id");
        query->bindValue(":user_id", socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x046");
    }
    else{
        QList<QStringList> employees_data;
        QStringList headerLabels;
        headerLabels << "ID сотрудника" << "Фамилия сотрудника"
                     << "Имя сотрудника" << "Отчетсво сотрудника" << "Статус сотрудника";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            employees_data.append(rowValues);
        }
        sendAdminEmployeeAnomalyDataResult(headerLabels, columnCount, employees_data.size(), employees_data);
    }
    delete query;
}

void Server::additionalForSendAdminRemoveWeekendResult(QDataStream &in)
{
    QString Weekend_id;
    bool access = true;
    in >> Weekend_id;
    query = new QSqlQuery(db);
    //Можно добавить обработку возможности удаления отпуска сотрудника.
    query->prepare("DELETE FROM Vacations WHERE VacationID = :weekend_id");
    query->bindValue(":weekend_id", Weekend_id.toInt());

    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x043");
    }
    else{
        sendAdminRemoveWeekendResult(access);
    }

    delete query;
}

void Server::additionalForSendAdminWorkWithWeekendResult(QDataStream &in)
{
    bool ready_to_send = true, access = true;
    QString action;
    QString object_id;
    QString WeekendBegin;
    QString WeekendEnd;
    QString note;

    in >> action >> object_id >> WeekendBegin >> WeekendEnd >> note;

    query = new QSqlQuery(db);
    if (action == "Добавить"){
        //Можно добавить обработку возможности добавления отпуска сотрудника.
        query->prepare("INSERT INTO Vacations "
                       "(VacationBeginDate, VacationEndDate, VacationDescription, UserID) "
                       "VALUES "
                       "(:VacationBeginDate, :VacationEndDate, :VacationDescription, :user_id)");
        query->bindValue(":VacationBeginDate", WeekendBegin);
        query->bindValue(":VacationEndDate", WeekendEnd);
        query->bindValue(":VacationDescription", note);
        query->bindValue(":user_id", object_id.toInt());

        if (!query->exec()){
            ready_to_send = false;
            additionalForSendErrorMessage(query, "2x041");
        }
    }
    else if (action == "Изменить"){
        //Можно добавить обработку возможности изменения отпуска сотрудника.
        query->prepare("UPDATE Vacations "
                       "SET VacationBeginDate = :VacationBeginDate, "
                       "VacationEndDate = :VacationEndDate, "
                       "VacationDescription = :VacationDescription "
                       "WHERE VacationID = :vacation_id");

        query->bindValue(":VacationBeginDate", WeekendBegin);
        query->bindValue(":VacationEndDate", WeekendEnd);
        query->bindValue(":VacationDescription", note);
        query->bindValue(":vacation_id", object_id.toInt());

        if (!query->exec()){
            ready_to_send = false;
            additionalForSendErrorMessage(query, "2x042");
        }
    }

    if (ready_to_send){
        sendAdminWorkWithWeekendResult(action, access);
    }
    delete query;
}

void Server::additionalForSendAdminRemoveGrafResult(QDataStream &in)
{
    QString graf_id;
    bool access = true;
    in >> graf_id;
    query = new QSqlQuery(db);
    //Можно добавить обработку возможности удаления графика сотрудника.
    query->prepare("DELETE FROM WorkScheduleEmployee WHERE WorkScheduleEmployeeID = :graf_id");
    query->bindValue(":graf_id", graf_id.toInt());

    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x040");
    }
    else{
        sendAdminRemoveGrafResult(access);
    }

    delete query;
}

void Server::additionalForSendAdminWorkWithGrafResult(QDataStream &in)
{
    bool ready_to_send = true, access = true;
    QString action;
    QString object_id;
    QStringList workSchedule;

    in >> action >> object_id;
    while (!in.atEnd()) {
        QString day;
        in >> day;
        workSchedule << day;
    }
    query = new QSqlQuery(db);
    if (action == "Добавить"){
        //Можно добавить обработку возможности добавления графика сотрудника.
        query->prepare("INSERT INTO WorkScheduleEmployee "
                       "(MondayBegin, MondayEnd, TuesdayBegin, TuesdayEnd, "
                       "WednesdayBegin, WednesdayEnd, ThursdayBegin, ThursdayEnd, "
                       "FridayBegin, FridayEnd, SaturdayBegin, SaturdayEnd, "
                       "SundayBegin, SundayEnd, UserID) "
                       "VALUES "
                       "(:MondayBegin, :MondayEnd, :TuesdayBegin, :TuesdayEnd, "
                       ":WednesdayBegin, :WednesdayEnd, :ThursdayBegin, :ThursdayEnd, "
                       ":FridayBegin, :FridayEnd, :SaturdayBegin, :SaturdayEnd, "
                       ":SundayBegin, :SundayEnd, :UserID)");

        query->bindValue(":MondayBegin", workSchedule[0] == workSchedule[1] ? QVariant() : workSchedule[0]);
        query->bindValue(":MondayEnd", workSchedule[0] == workSchedule[1] ? QVariant() : workSchedule[1]);

        query->bindValue(":TuesdayBegin", workSchedule[2] == workSchedule[3] ? QVariant() : workSchedule[2]);
        query->bindValue(":TuesdayEnd", workSchedule[2] == workSchedule[3] ? QVariant() : workSchedule[3]);

        query->bindValue(":WednesdayBegin", workSchedule[4] == workSchedule[5] ? QVariant() : workSchedule[4]);
        query->bindValue(":WednesdayEnd", workSchedule[4] == workSchedule[5] ? QVariant() : workSchedule[5]);

        query->bindValue(":ThursdayBegin", workSchedule[6] == workSchedule[7] ? QVariant() : workSchedule[6]);
        query->bindValue(":ThursdayEnd", workSchedule[6] == workSchedule[7] ? QVariant() : workSchedule[7]);

        query->bindValue(":FridayBegin", workSchedule[8] == workSchedule[9] ? QVariant() : workSchedule[8]);
        query->bindValue(":FridayEnd", workSchedule[8] == workSchedule[9] ? QVariant() : workSchedule[9]);

        query->bindValue(":SaturdayBegin", workSchedule[10] == workSchedule[11] ? QVariant() : workSchedule[10]);
        query->bindValue(":SaturdayEnd", workSchedule[10] == workSchedule[11] ? QVariant() : workSchedule[11]);

        query->bindValue(":SundayBegin", workSchedule[12] == workSchedule[13] ? QVariant() : workSchedule[12]);
        query->bindValue(":SundayEnd", workSchedule[12] == workSchedule[13] ? QVariant() : workSchedule[13]);

        query->bindValue(":UserID", object_id.toInt());

        if (!query->exec()){
            ready_to_send = false;
            additionalForSendErrorMessage(query, "2x039");
        }
    }
    else if (action == "Изменить"){
        //Можно добавить обработку возможности изменения графика сотрудника.
        query->prepare("UPDATE WorkScheduleEmployee SET "
                       "MondayBegin = :MondayBegin, MondayEnd = :MondayEnd, "
                       "TuesdayBegin = :TuesdayBegin, TuesdayEnd = :TuesdayEnd, "
                       "WednesdayBegin = :WednesdayBegin, WednesdayEnd = :WednesdayEnd, "
                       "ThursdayBegin = :ThursdayBegin, ThursdayEnd = :ThursdayEnd, "
                       "FridayBegin = :FridayBegin, FridayEnd = :FridayEnd, "
                       "SaturdayBegin = :SaturdayBegin, SaturdayEnd = :SaturdayEnd, "
                       "SundayBegin = :SundayBegin, SundayEnd = :SundayEnd "
                       "WHERE WorkScheduleEmployeeID = :graf_id");

        query->bindValue(":MondayBegin", workSchedule[0] == workSchedule[1] ? QVariant() : workSchedule[0]);
        query->bindValue(":MondayEnd", workSchedule[0] == workSchedule[1] ? QVariant() : workSchedule[1]);

        query->bindValue(":TuesdayBegin", workSchedule[2] == workSchedule[3] ? QVariant() : workSchedule[2]);
        query->bindValue(":TuesdayEnd", workSchedule[2] == workSchedule[3] ? QVariant() : workSchedule[3]);

        query->bindValue(":WednesdayBegin", workSchedule[4] == workSchedule[5] ? QVariant() : workSchedule[4]);
        query->bindValue(":WednesdayEnd", workSchedule[4] == workSchedule[5] ? QVariant() : workSchedule[5]);

        query->bindValue(":ThursdayBegin", workSchedule[6] == workSchedule[7] ? QVariant() : workSchedule[6]);
        query->bindValue(":ThursdayEnd", workSchedule[6] == workSchedule[7] ? QVariant() : workSchedule[7]);

        query->bindValue(":FridayBegin", workSchedule[8] == workSchedule[9] ? QVariant() : workSchedule[8]);
        query->bindValue(":FridayEnd", workSchedule[8] == workSchedule[9] ? QVariant() : workSchedule[9]);

        query->bindValue(":SaturdayBegin", workSchedule[10] == workSchedule[11] ? QVariant() : workSchedule[10]);
        query->bindValue(":SaturdayEnd", workSchedule[10] == workSchedule[11] ? QVariant() : workSchedule[11]);

        query->bindValue(":SundayBegin", workSchedule[12] == workSchedule[13] ? QVariant() : workSchedule[12]);
        query->bindValue(":SundayEnd", workSchedule[12] == workSchedule[13] ? QVariant() : workSchedule[13]);

        query->bindValue(":graf_id", object_id.toInt());

        if (!query->exec()){
            ready_to_send = false;
            additionalForSendErrorMessage(query, "2x040");
        }
    }

    if (ready_to_send){
        sendAdminWorkWithGrafResult(action, access);
    }
    delete query;
}

void Server::additionalForSendAdminGetEmployeeWeekends(QDataStream &in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare(
            "SELECT DISTINCT V.VacationID, E.EmployeeLastName, E.EmployeeFirstName, "
            "E.EmployeeMiddleName, V.VacationBeginDate, V.VacationEndDate, V.VacationDescription "
            "FROM Employees E "
            "JOIN Users U ON E.EmployeeID = U.UserID "
            "JOIN ProjectTasks PT ON U.UserID = PT.ProjectTaskAssigneeID "
            "JOIN Projects P ON PT.ProjectID = P.ProjectID "
            "JOIN Vacations V ON U.UserID = V.UserID ");
    }
    else{
        query->prepare(
            "SELECT DISTINCT V.VacationID, E.EmployeeLastName, E.EmployeeFirstName, "
            "E.EmployeeMiddleName, V.VacationBeginDate, V.VacationEndDate, V.VacationDescription "
            "FROM Employees E "
            "JOIN Users U ON E.EmployeeID = U.UserID "
            "JOIN ProjectTasks PT ON U.UserID = PT.ProjectTaskAssigneeID "
            "JOIN Projects P ON PT.ProjectID = P.ProjectID "
            "JOIN Vacations V ON U.UserID = V.UserID "
            "WHERE P.ProjectManagerID = :user_id");
        query->bindValue(":user_id", socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x038");
    }
    else{
        QList<QStringList> weekends_data;
        QStringList headerLabels;
        headerLabels << "ID отпуска" << "Фамилия сотрудника"
                     << "Имя сотрудника" << "Отчество сотрудника"
                     << "Начало отпуска" << "Конец отпуска"
                     << "Заметка к отпуску";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            weekends_data.append(rowValues);
        }
        sendAdminGetEmployeeWeekendsResult(headerLabels, columnCount, weekends_data.size(), weekends_data);
    }
    delete query;
}

void Server::additionalForSendAdminGetEmployeeGrafs(QDataStream &in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare(
            "SELECT DISTINCT "
            "WSE.WorkScheduleEmployeeID, "
            "E.EmployeeLastName, "
            "E.EmployeeFirstName, "
            "E.EmployeeMiddleName, "
            "WSE.MondayBegin, "
            "WSE.MondayEnd, "
            "WSE.TuesdayBegin, "
            "WSE.TuesdayEnd, "
            "WSE.WednesdayBegin, "
            "WSE.WednesdayEnd, "
            "WSE.ThursdayBegin, "
            "WSE.ThursdayEnd, "
            "WSE.FridayBegin, "
            "WSE.FridayEnd, "
            "WSE.SaturdayBegin, "
            "WSE.SaturdayEnd, "
            "WSE.SundayBegin, "
            "WSE.SundayEnd "
            "FROM "
            "Employees E "
            "JOIN "
            "Users U ON E.EmployeeID = U.UserID "
            "JOIN "
            "WorkScheduleEmployee WSE ON U.UserID = WSE.UserID ");
    }
    else{
        query->prepare(
            "SELECT DISTINCT "
            "WSE.WorkScheduleEmployeeID, "
            "E.EmployeeLastName, "
            "E.EmployeeFirstName, "
            "E.EmployeeMiddleName, "
            "WSE.MondayBegin, "
            "WSE.MondayEnd, "
            "WSE.TuesdayBegin, "
            "WSE.TuesdayEnd, "
            "WSE.WednesdayBegin, "
            "WSE.WednesdayEnd, "
            "WSE.ThursdayBegin, "
            "WSE.ThursdayEnd, "
            "WSE.FridayBegin, "
            "WSE.FridayEnd, "
            "WSE.SaturdayBegin, "
            "WSE.SaturdayEnd, "
            "WSE.SundayBegin, "
            "WSE.SundayEnd "
            "FROM "
            "Employees E "
            "JOIN "
            "Users U ON E.EmployeeID = U.UserID "
            "JOIN "
            "ProjectTasks PT ON U.UserID = PT.ProjectTaskAssigneeID "
            "JOIN "
            "Projects P ON PT.ProjectID = P.ProjectID "
            "JOIN "
            "WorkScheduleEmployee WSE ON U.UserID = WSE.UserID "
            "WHERE "
            "P.ProjectManagerID = :user_id");
        query->bindValue(":user_id", socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x034");
    }
    else{
        QList<QStringList> grafs_data;
        QStringList headerLabels;
        headerLabels << "ID графика" << "Фамилия сотрудника"
                     << "Имя сотрудника" << "Отчество сотрудника"
                     << "ПН Начало" << "ПН Конец"
                     << "ВТ Начало" << "ВТ Конец"
                     << "СР Начало" << "СР Конец"
                     << "ЧТ Начало" << "ЧТ Конец"
                     << "ПТ Начало" << "ПТ Конец"
                     << "СБ Начало" << "СБ Конец"
                     << "ВС Начало" << "ВС Конец";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue;
                if (i >= 0 && i <= 3){
                    rowValue = query->value(i).toString();
                }
                else{
                    QDateTime workGrafBeginEndTime = query->value(i).toDateTime();
                    rowValue = workGrafBeginEndTime.toString("dd.MM.yyyy hh:mm:ss");
                }
                rowValues.append(rowValue);
            }
            grafs_data.append(rowValues);
        }
        sendAdminGetEmployeeGrafsResult(headerLabels, columnCount, grafs_data.size(), grafs_data);
    }
    delete query;
}

void Server::additionalForSendAdminGetEmployeeData(QDataStream &in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT DISTINCT E.EmployeeID, E.EmployeeLastName, E.EmployeeFirstName, E.EmployeeMiddleName, os.ObjectStatusText "
                       "FROM Employees E JOIN Users U ON E.EmployeeID = U.UserID "
                       "JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID ");
    }
    else{
        query->prepare("SELECT DISTINCT E.EmployeeID, E.EmployeeLastName, E.EmployeeFirstName, E.EmployeeMiddleName, os.ObjectStatusText "
                       "FROM Employees E JOIN Users U ON E.EmployeeID = U.UserID "
                       "JOIN ProjectTasks PT ON U.UserID = PT.ProjectTaskAssigneeID "
                       "JOIN Projects P ON PT.ProjectID = P.ProjectID "
                       "JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID "
                       "WHERE P.ProjectManagerID = :user_id");
        query->bindValue(":user_id", socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x033");
    }
    else{
        QList<QStringList> employees_data;
        QStringList headerLabels;
        headerLabels << "ID сотрудника" << "Фамилия сотрудника"
                     << "Имя сотрудника" << "Отчетсво сотрудника" << "Статус сотрудника";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            employees_data.append(rowValues);
        }
        sendAdminEmployeeDataResult(headerLabels, columnCount, employees_data.size(), employees_data);
    }
    delete query;
}

void Server::additionalForSendAdminCompleteProjectTasksResult(QDataStream &in)
{
    QString projID;
    in >> projID;
    query = new QSqlQuery(db);
    query->prepare("SELECT "
                   "PT.ProjectTaskID, "
                   "PT.ProjectTaskName, "
                   "PT.ProjectTaskDescription, "
                   "OS.ObjectStatusText AS TaskStatus, "
                   "E.EmployeeLastName AS AssigneeLastName, "
                   "E.EmployeeFirstName AS AssigneeFirstName, "
                   "E.EmployeeMiddleName AS AssigneeMiddleName "
                   "FROM "
                   "ProjectTasks PT "
                   "JOIN Projects P ON PT.ProjectID = P.ProjectID "
                   "JOIN ObjectStatuses OS ON PT.ProjectTaskStatusID = OS.ObjectStatusID "
                   "JOIN Employees E ON PT.ProjectTaskAssigneeID = E.EmployeeID "
                   "WHERE P.ProjectID = :proj_ID");
    query->bindValue(":proj_ID", projID);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x032");
    }
    else{
        QList<QStringList> complete_tasks_data;
        QStringList headerLabels;
        headerLabels << "ID проектной задачи" << "Название проектной задачи" << "Описание проектной задчи" << "Статус проектной задачи"
                     << "Фамилия сотрудника" << "Имя сотрудника" << "Отчество сотрудника";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            complete_tasks_data.append(rowValues);
        }
        sendAdminCompleteProjectTasksResult(headerLabels, columnCount, complete_tasks_data.size(), complete_tasks_data);
    }
    delete query;
}

void Server::additionalForSendAdminCompleteProjectsResult(QDataStream &in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT "
                       "P.ProjectID, "
                       "P.ProjectName, "
                       "P.ProjectDescription, "
                       "OS.ObjectStatusText AS ProjectStatus, "
                       "a.AdminLastName AS ProjectManagerLastName, "
                       "a.AdminFirstName AS ProjectManagerFirstName, "
                       "a.AdminMiddleName AS ProjectManagerMiddleName "
                       "FROM "
                       "Projects P "
                       "JOIN "
                       "ObjectStatuses OS ON P.ProjectStatusID = OS.ObjectStatusID "
                       "JOIN "
                       "Users U ON P.ProjectManagerID = U.UserID "
                       "JOIN "
                       "Administrators a ON U.UserID = a.AdminID ");
    }
    else{
        query->prepare("SELECT "
                       "P.ProjectID, "
                       "P.ProjectName, "
                       "P.ProjectDescription, "
                       "OS.ObjectStatusText AS ProjectStatus "
                       "FROM "
                       "Projects P "
                       "JOIN "
                       "ObjectStatuses OS ON P.ProjectStatusID = OS.ObjectStatusID "
                       "JOIN "
                       "Users U ON P.ProjectManagerID = U.UserID "
                       "JOIN "
                       "Administrators a ON U.UserID = a.AdminID "
                       "WHERE "
                       "u.UserID = :user_id");
        query->bindValue(":user_id", socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x031");
    }
    else{
        QList<QStringList> complete_projs_data;
        QStringList headerLabels;
        if (type_admin == "Admin")
        {
            headerLabels << "ID проекта" << "Название проекта" << "Описание проекта"
                         << "Статус проекта" << "Фамилия руководителя"
                         << "Имя руководителя" << "Отчетсво руководителя";
        }
        else{
            headerLabels << "ID проекта" << "Название проекта" << "Описание проекта"
                         << "Статус проекта";
        }
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            complete_projs_data.append(rowValues);
        }
        sendAdminCompleteProjectsResult(headerLabels, columnCount, complete_projs_data.size(), complete_projs_data);
    }
    delete query;
}

void Server::additionalForSendAdminCredentialsData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT "
                   "a.AdminLastName, "
                   "a.AdminFirstName, "
                   "a.AdminMiddleName, "
                   "a.AdminJobTitle, "
                   "a.AdminContactInformation, "
                   "u.UserLogin, "
                   "u.UserPswd "
                   "FROM Administrators a "
                   "JOIN Users u ON a.AdminID = u.UserID "
                   "WHERE a.AdminID = :admin_id");
    query->bindValue(":admin_id", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x015");
    }
    else{
        QList<QStringList> credentials_data;
        QStringList headerLabels;
        headerLabels << "Фамилия" << "Имя" << "Отчество" << "Должность"
                     << "Контактная информация" << "Логин" << "Пароль";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            credentials_data.append(rowValues);
        }
        sendAdminCredentialsData(headerLabels, columnCount, credentials_data.size(), credentials_data);
    }
    delete query;
}

void Server::additionalForGetEmployeeTableData(QDataStream& in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT u.UserID, u.UserLogin, u.UserPswd, u.UserRole, os.ObjectStatusText, e.EmployeeLastName, "
                       "e.EmployeeFirstName, e.EmployeeMiddleName, e.EmployeeJobTitle, e.EmployeePersonnelNumber, "
                       "e.EmployeeContactInformation, e.EmployeeAdditionalInfo "
                       "FROM dbo.Users u INNER JOIN dbo.ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID AND u.UserRole != 'Admin' AND u.UserRole != 'Manager' "
                       "INNER JOIN dbo.Employees e ON u.UserID = e.EmployeeID");
    }
    else{
        query->prepare("SELECT DISTINCT u.UserID, u.UserLogin, u.UserPswd, u.UserRole, os.ObjectStatusText, e.EmployeeLastName, "
                       "e.EmployeeFirstName, e.EmployeeMiddleName, e.EmployeeJobTitle, e.EmployeePersonnelNumber, "
                       "e.EmployeeContactInformation, e.EmployeeAdditionalInfo "
                       "FROM dbo.Users u INNER JOIN dbo.ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID AND u.UserRole != 'Admin' AND u.UserRole != 'Manager' "
                       "INNER JOIN dbo.Employees e ON u.UserID = e.EmployeeID "
                       "LEFT JOIN dbo.ProjectTasks pt ON e.EmployeeID = pt.ProjectTaskAssigneeID "
                       "LEFT JOIN dbo.Projects p ON pt.ProjectID = p.ProjectID "
                       "WHERE "
                       "(p.ProjectManagerID = ? OR p.ProjectManagerID IS NULL) "
                       "AND e.EmployeeID NOT IN ( "
                       "SELECT pt2.ProjectTaskAssigneeID FROM dbo.ProjectTasks pt2 "
                       "INNER JOIN dbo.Projects p2 ON pt2.ProjectID = p2.ProjectID "
                       "WHERE p2.ProjectManagerID != ?)");
        query->addBindValue(socketUserIDMap[socket]);
        query->addBindValue(socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x001");
    }
    else{
        QList<QStringList> users_data;
        QStringList headerLabels;
        headerLabels << "ID пользователя" << "Логин" << "Пароль" << "Роль в системе"
                     << "Статус активности" << "Фамилия" << "Имя"
                     << "Отчество" << "Должность" << "Табельный номер"
                     << "Контактная информация" << "Дополнительная информация";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            users_data.append(rowValues);
        }
        sendUsersTableData(headerLabels, columnCount, users_data.size(), users_data);
    }
    delete query;
}

void Server::additionalForRemovedEmployeeResult(QDataStream &in)
{
    QString user_id;
    in >> user_id;
    query = new QSqlQuery(db);
    if (isNumeric(user_id)){
        if (!getUserLogin(query, user_id).isEmpty() && isUserOffline(query, user_id)){
            QString removed_userID = user_id;
            QString userRole = getUserRole(query, removed_userID),
                tableName, idFieldName;

            if (userRole == "Employee") {
                tableName = "dbo.Employees";
                idFieldName = "EmployeeID";
            } else if (userRole == "Administrator"){
                tableName = "dbo.Administrators";
                idFieldName = "AdminID";
            } else{
                additionalForSendErrorMessage(query, "2x010");
                return;
            }

            query->prepare(QString("DELETE FROM %1 WHERE %2 = :user_id").arg(tableName, idFieldName));
            query->bindValue(":user_id", user_id.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "2x003");
            }
            else{
                query->prepare("DELETE FROM dbo.Users WHERE Users.UserID = :user_id");
                query->bindValue(":user_id", user_id.toInt());
                if (!query->exec()){
                    additionalForSendErrorMessage(query, "2x009");
                }
                else{
                    int rowsAffected = query->numRowsAffected();
                    if (rowsAffected > 0) {
                        sendRemovedUserResult(true);
                    }
                    else{
                        sendRemovedUserResult(false);
                    }
                }
            }
        }
        else{
            sendRemovedUserResult(false);
        }
    }
    else{
        sendRemovedUserResult(false);
    }
    delete query;
}

void Server::additionalForChangeEmployeeResult(QDataStream &in)
{
    QMap<QString, bool> change_employee_success;
    QString employeeID, firstName, lastName, middleName, jobTitle, personnelNumber, contactInfo, additionalInfo, login, password;
    in >> employeeID >> firstName >> lastName >> middleName >> jobTitle >> personnelNumber >> contactInfo >> additionalInfo >> login >> password;

    query = new QSqlQuery(db);
    change_employee_success["EmployeeID"] = isNumeric(employeeID);
    change_employee_success["FirstName"] = isCyrillic(firstName);
    change_employee_success["LastName"] = isCyrillic(lastName);
    change_employee_success["MiddleName"] = middleName.isEmpty() || isCyrillic(middleName);
    change_employee_success["JobTitle"] = isCyrillic(jobTitle);
    change_employee_success["PersonnelNumber"] =
        (isNumeric(personnelNumber) && ((isUniquePersonnelNumber(personnelNumber.toInt(), query))
        || (isNumeric(employeeID) && (personnelNumber.toInt() == getEmployeePersonnelNumber(query, employeeID)))));
    change_employee_success["Login"] = (isUniqueLogin(login, query) || (isNumeric(employeeID) && login == getUserLogin(query, employeeID)));
    change_employee_success["Pswd"] = true;
    change_employee_success["ContactInformation"] = true;
    change_employee_success["AdditionalInfo"] = true;

    bool allValid = std::all_of(change_employee_success.constBegin(), change_employee_success.constEnd(),
                                [](const bool &value) { return value; });
    bool ready_to_send = true;
    if (allValid && !getUserLogin(query, employeeID).isEmpty() && isUserOffline(query, employeeID))
    {
        query->prepare("UPDATE dbo.Users SET UserLogin = ?, UserPswd = ? WHERE UserID = ?");
        query->addBindValue(login);
        query->addBindValue(password);
        query->addBindValue(employeeID.toInt());
        if (query->exec()){
            query->prepare("UPDATE dbo.Employees SET EmployeeFirstName = ?, EmployeeLastName = ?, EmployeeMiddleName = ?, "
                           "EmployeeJobTitle = ?, EmployeePersonnelNumber = ?, EmployeeAdditionalInfo = ?, EmployeeContactInformation = ? "
                           "WHERE EmployeeID = ?");
            query->addBindValue(firstName);
            query->addBindValue(lastName);
            query->addBindValue(middleName);
            query->addBindValue(jobTitle);
            query->addBindValue(personnelNumber.toInt());
            query->addBindValue(additionalInfo);
            query->addBindValue(contactInfo);
            query->addBindValue(employeeID.toInt());
            if (!query->exec()){
                ready_to_send = false;
                additionalForSendErrorMessage(query, "2x005");
            }
        }
        else{
            ready_to_send = false;
            additionalForSendErrorMessage(query, "2x004");
        }
    }
    if (ready_to_send){
        sendChangedEmployeeResult(change_employee_success);
    }
    delete query;
}

void Server::additionalForGetEmployeeRequestsTableData(QDataStream& in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT er.EmployeeRequestID, "
                       "rc.RequestCategoryName, "
                       "u.UserLogin, "
                       "e.EmployeeFirstName, "
                       "e.EmployeeLastName, "
                       "e.EmployeeMiddleName, "
                       "os.ObjectStatusText, "
                       "er.EmployeeRequestText "
                       "FROM dbo.EmployeeRequests er "
                       "INNER JOIN dbo.RequestCategories rc ON er.RequestCategoryID = rc.RequestCategoryID "
                       "INNER JOIN dbo.Users u ON er.UserID = u.UserID "
                       "INNER JOIN dbo.Employees e ON u.UserID = e.EmployeeID "
                       "INNER JOIN dbo.ObjectStatuses os ON er.EmployeeRequestStatusID = os.ObjectStatusID "
                       "WHERE os.ObjectStatusText = 'Ожидание'");
    } else {
        query->prepare("SELECT DISTINCT er.EmployeeRequestID, "
                       "rc.RequestCategoryName, "
                       "u.UserLogin, "
                       "e.EmployeeFirstName, "
                       "e.EmployeeLastName, "
                       "e.EmployeeMiddleName, "
                       "os.ObjectStatusText, "
                       "er.EmployeeRequestText "
                       "FROM dbo.EmployeeRequests er "
                       "INNER JOIN dbo.RequestCategories rc ON er.RequestCategoryID = rc.RequestCategoryID "
                       "INNER JOIN dbo.Users u ON er.UserID = u.UserID "
                       "INNER JOIN dbo.Employees e ON u.UserID = e.EmployeeID "
                       "INNER JOIN dbo.ObjectStatuses os ON er.EmployeeRequestStatusID = os.ObjectStatusID "
                       "WHERE "
                       "os.ObjectStatusText = 'Ожидание' AND EXISTS ( "
                       "SELECT 1 FROM dbo.Projects p "
                       "INNER JOIN dbo.ProjectTasks pt ON p.ProjectID = pt.ProjectID "
                       "WHERE pt.ProjectTaskAssigneeID = e.EmployeeID AND p.ProjectManagerID = ?)");
        query->addBindValue(socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x011");
    }
    else{
        QList<QStringList> users_data;
        QStringList headerLabels;
        headerLabels << "ID запроса" << "Категория запроса" << "Логин отправителя" << "Имя отправителя" << "Фамилия отправителя" << "Отчество отправителя"
                     << "Статус запроса" << "Содержание запроса";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            users_data.append(rowValues);
        }
        sendEmployeeRequests(headerLabels, columnCount, users_data.size(), users_data);
    }
    delete query;
}

void Server::additionalForGetRequestStatusesTableData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT ObjectStatusText FROM dbo.ObjectStatuses WHERE ObjectStatusID NOT IN (1, 2, 3, 6, 7, 8)");
    if (!query->exec()) {
        additionalForSendErrorMessage(query, "2x012");
    }
    else
    {
        QStringList requestObjectStatuses;
        while (query->next()) {
            QString requestObjectStatus = query->value(0).toString();
            requestObjectStatuses.append(requestObjectStatus);
        }
        sendRequestObjectStatuses(requestObjectStatuses);
    }

    delete query;
}

void Server::additionalForCloseRequestResult(QDataStream &in)
{
    int requestID;
    QString requestStatus;
    QString text;
    int recepientID;
    in >> requestID >> requestStatus >> text;
    query = new QSqlQuery(db);
    query->prepare("SELECT UserID FROM dbo.EmployeeRequests WHERE EmployeeRequestID = :request_id");
    query->bindValue(":request_id", requestID);
    if (!query->exec() || !query->next()) {
        additionalForSendErrorMessage(query, "2x013");
        delete query;
        return;
    }
    else
    {
        recepientID = query->value(0).toInt();
        query->clear();
        int adminMessageID;
        query->prepare("INSERT INTO dbo.AdminMessages (AdminMessageText, AdminMessageRecipientID, UserID) VALUES (?, ?, ?) SELECT SCOPE_IDENTITY()");
        query->addBindValue(text);
        query->addBindValue(recepientID);
        query->addBindValue(socketUserIDMap[socket]);
        if (!query->exec() || !query->next()){
            additionalForSendErrorMessage(query, "2x014");
            delete query;
            return;
        }
        else
        {
            adminMessageID = query->value(0).toInt();
            int requestStatusID;
            query->prepare("SELECT ObjectStatusID FROM dbo.ObjectStatuses WHERE ObjectStatusText = ?");
            query->addBindValue(requestStatus);
            if (!query->exec() || !query->next()){
                additionalForSendErrorMessage(query, "2x016");
                return;
            }
            requestStatusID = query->value(0).toInt();
            query->clear();
            query->prepare("UPDATE dbo.EmployeeRequests SET EmployeeRequestStatusID = :status_id, AdminMessageID = :message_id WHERE EmployeeRequestID = :request_id");
            query->addBindValue(requestStatusID);
            query->addBindValue(adminMessageID);
            query->addBindValue(requestID);
            if (!query->exec()){
                additionalForSendErrorMessage(query, "2x017");
                delete query;
                return;
            }
            //Проверка закрытия запроса категории "Выполнение проектной задачи".
            query->clear();
            query->prepare("SELECT EmployeeRequestText, RequestCategoryID FROM dbo.EmployeeRequests WHERE EmployeeRequestID = :request_id");
            query->bindValue(":request_id", requestID);
            if (!query->exec() || !query->next()){
                additionalForSendErrorMessage(query, "2x024");
                delete query;
                return;
            }else{
                QString proj_task_names = query->value(0).toString();
                int request_categoryID = query->value(1).toInt();
                if (request_categoryID == 6){
                    static const QRegularExpression re("Задача: (.+)$");
                    QRegularExpressionMatch match = re.match(proj_task_names);
                    if (match.hasMatch()) {
                        QString taskName = match.captured(1);
                        requestStatus == "Принято" ? request_categoryID = 6 : request_categoryID = 7;
                        query->prepare("UPDATE dbo.ProjectTasks SET ProjectTaskStatusID = :categoryID WHERE ProjectTaskName = :proj_task_name");
                        query->bindValue(":categoryID", request_categoryID);
                        query->bindValue(":proj_task_name", taskName);
                        if (!query->exec()){
                            additionalForSendErrorMessage(query, "2x025");
                            delete query;
                            return;
                        }
                    }
                }
            }
            //Авоматическое завершение проекта, если все задачи завершены.
            query->prepare("UPDATE Projects SET ProjectStatusID = 6 "
                           "WHERE ProjectID IN (SELECT p.ProjectID FROM Projects p "
                           "INNER JOIN ProjectTasks pt ON p.ProjectID = pt.ProjectID "
                           "GROUP BY p.ProjectID "
                           "HAVING COUNT(*) = SUM(CASE WHEN pt.ProjectTaskStatusID = 6 THEN 1 ELSE 0 END))");
            if (!query->exec()){
                additionalForSendErrorMessage(query, "2x051");
                delete query;
                return;
            }
        }
    }
    sendCloseRequestCompleted();
}

void Server::additionalForGetTaskDataTable(QDataStream& in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT a.AdminLastName, a.AdminFirstName, a.AdminMiddleName, p.ProjectID, p.ProjectName, os_p.ObjectStatusText, pt.ProjectTaskID, "
                       "pt.ProjectTaskName, os_t.ObjectStatusText, emp.EmployeeID, emp.EmployeeLastName, emp.EmployeeFirstName, emp.EmployeeMiddleName "
                       "FROM Projects p "
                       "LEFT JOIN Users u ON p.ProjectManagerID = u.UserID "
                       "LEFT JOIN Administrators a ON u.UserID = a.AdminID "
                       "LEFT JOIN Employees e ON u.UserID = e.EmployeeID "
                       "LEFT JOIN ProjectTasks pt ON pt.ProjectID = p.ProjectID "
                       "LEFT JOIN Users emp_u ON pt.ProjectTaskAssigneeID = emp_u.UserID "
                       "LEFT JOIN Employees emp ON emp_u.UserID = emp.EmployeeID "
                       "LEFT JOIN ObjectStatuses os_p ON p.ProjectStatusID = os_p.ObjectStatusID "
                       "LEFT JOIN ObjectStatuses os_t ON pt.ProjectTaskStatusID = os_t.ObjectStatusID "
                       "WHERE p.ProjectStatusID IN (7, 8)");
    } else {
        query->prepare("SELECT a.AdminLastName, a.AdminFirstName, a.AdminMiddleName, p.ProjectID, p.ProjectName, os_p.ObjectStatusText, pt.ProjectTaskID, "
                       "pt.ProjectTaskName, os_t.ObjectStatusText, emp.EmployeeID, emp.EmployeeLastName, emp.EmployeeFirstName, emp.EmployeeMiddleName "
                       "FROM Projects p "
                       "LEFT JOIN Users u ON p.ProjectManagerID = u.UserID "
                       "LEFT JOIN Administrators a ON u.UserID = a.AdminID "
                       "LEFT JOIN Employees e ON u.UserID = e.EmployeeID "
                       "LEFT JOIN ProjectTasks pt ON pt.ProjectID = p.ProjectID "
                       "LEFT JOIN Users emp_u ON pt.ProjectTaskAssigneeID = emp_u.UserID "
                       "LEFT JOIN Employees emp ON emp_u.UserID = emp.EmployeeID "
                       "LEFT JOIN ObjectStatuses os_p ON p.ProjectStatusID = os_p.ObjectStatusID "
                       "LEFT JOIN ObjectStatuses os_t ON pt.ProjectTaskStatusID = os_t.ObjectStatusID "
                       "WHERE p.ProjectManagerID = ? AND p.ProjectStatusID IN (7, 8)");
        query->addBindValue(socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x035");
    }
    else{
        QList<QStringList> tasks_data;
        QStringList headerLabels;
        headerLabels << "Фамилия руководителя" << "Имя руководителя" << "Отчество руководителя" << "ID проекта"
                     << "Название проекта" << "Статус проекта" << "ID задачи" << "Название задачи" << "Статус задачи" << "ID сотрудника"
                     << "Фамилия сотрудника" << "Имя сотрудника" << "Отчество сотрудника";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            tasks_data.append(rowValues);
        }
        delete query;
        sendTasksTableData(headerLabels, columnCount, tasks_data.size(), tasks_data);
    }
}

void Server::additionalForGetEmployeeForTaskDataTable(QDataStream& in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT e.EmployeeID, e.EmployeeLastName, e.EmployeeFirstName, e.EmployeeMiddleName "
                       "FROM Users u "
                       "INNER JOIN Employees e ON u.UserID = e.EmployeeID "
                       "WHERE u.UserRole = 'Employee' OR u.UserRole = 'Manager'");
    }
    else{
        query->prepare("SELECT DISTINCT e.EmployeeID, e.EmployeeLastName, e.EmployeeFirstName, e.EmployeeMiddleName "
                       "FROM Users u "
                       "INNER JOIN Employees e ON u.UserID = e.EmployeeID "
                       "LEFT JOIN ProjectTasks pt ON e.EmployeeID = pt.ProjectTaskAssigneeID "
                       "LEFT JOIN Projects p ON pt.ProjectID = p.ProjectID "
                       "WHERE u.UserRole = 'Employee' AND (p.ProjectManagerID = ? OR p.ProjectID IS NULL) OR u.UserID = ?");
        query->addBindValue(socketUserIDMap[socket]);
        query->addBindValue(socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x036");
    }
    else{
        QList<QStringList> emps_data;
        QStringList headerLabels;
        headerLabels << "ID сотрудника"
                     << "Фамилия сотрудника" << "Имя сотрудника" << "Отчество сотрудника";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            emps_data.append(rowValues);
        }
        delete query;
        sendEmployeeForTasksTableData(headerLabels, columnCount, emps_data.size(), emps_data);
    }
}

void Server::additionalForAddTask(QDataStream &in)
{
    QString projecID, employeeID, taskName, taskDescription;
    in >> projecID >> employeeID >> taskName >> taskDescription;
    query = new QSqlQuery(db);
    query->prepare("SELECT * FROM dbo.ProjectTasks WHERE ProjectTaskName = ?");
    query->addBindValue(taskName);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x037_1");
    }
    else{
        if (query->next()){
            sendAddTaskCompleted(false);
        }
        else{
            query->prepare("INSERT INTO dbo.ProjectTasks (ProjectTaskName, ProjectTaskDescription, ProjectTaskStatusID, ProjectID, ProjectTaskAssigneeID) VALUES (?, ?, 8, ?, ?)");
            query->addBindValue(taskName);
            query->addBindValue(taskDescription);
            query->addBindValue(projecID.toInt());
            query->addBindValue(employeeID.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "2x037");
            }
            sendAddTaskCompleted(true);
        }
    }
    delete query;
}

void Server::additionalForChangedTaskResult(QDataStream &in)
{
    QString taskID, taskName, taskDescription;
    in >> taskID >> taskName >> taskDescription;
    query = new QSqlQuery(db);
    query->prepare("UPDATE dbo.ProjectTasks SET ProjectTaskName = ?, ProjectTaskDescription = ? WHERE ProjectTaskID = ?");
    query->addBindValue(taskName);
    query->addBindValue(taskDescription);
    query->addBindValue(taskID.toInt());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "0x038");
    }
    sendRemoveChangeTaskCompleted();
    delete query;
}

void Server::additionalForRemovedTaskResult(QDataStream &in)
{
    QString task_id;
    in >> task_id;
    query = new QSqlQuery(db);
    query->prepare("SELECT ProjectTaskStatusID FROM dbo.ProjectTasks WHERE ProjectTaskID = :task_id");
    query->bindValue(":task_id", task_id.toInt());
    if (!query->exec() || !query->next()){
        additionalForSendErrorMessage(query, "0x039");
    }
    else{
        QString projectTaskStatusID = query->value(0).toString();
        if (projectTaskStatusID == "8"){
            query->prepare("DELETE FROM dbo.ProjectTasks WHERE ProjectTaskID = ?");
            query->addBindValue(task_id.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x040");
            }
        }
    }
    sendRemoveChangeTaskCompleted();
    delete query;
}

void Server::additionalForWorkedTaskResult(QDataStream &in)
{
    QString task_id;
    in >> task_id;
    query = new QSqlQuery(db);
    query->prepare("SELECT ProjectTaskStatusID, ProjectID FROM dbo.ProjectTasks WHERE ProjectTaskID = :task_id");
    query->bindValue(":task_id", task_id.toInt());
    if (!query->exec() || !query->next()){
        additionalForSendErrorMessage(query, "0x045");
    }
    else{
        QString projectTaskStatusID = query->value(0).toString();
        QString projectID = query->value(1).toString();
        if (projectTaskStatusID == "8"){
            query->prepare("UPDATE dbo.ProjectTasks SET ProjectTaskStatusID = 7 WHERE ProjectTaskID = ?");
            query->addBindValue(task_id.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x046");
            }
            else{
                query->prepare("SELECT ProjectStatusID FROM dbo.Projects WHERE ProjectID = :project_id");
                query->bindValue(":project_id", projectID.toInt());
                if (!query->exec() || !query->next()){
                    additionalForSendErrorMessage(query, "0x047");
                }
                else{
                    QString projectStatusID = query->value(0).toString();
                    if (projectStatusID == "8"){
                        query->prepare("UPDATE dbo.Projects SET ProjectStatusID = 7 WHERE ProjectID = ?");
                        query->addBindValue(projectID.toInt());
                        if (!query->exec()){
                            additionalForSendErrorMessage(query, "0x048");
                        }
                    }
                }
            }
        }
    }
    sendRemoveChangeTaskCompleted();
    delete query;
}

void Server::additionalForEmployeeForTaskResult(QDataStream &in)
{
    QString employeeID, taskID;
    in >> employeeID >> taskID;
    query = new QSqlQuery(db);
    query->prepare("UPDATE dbo.ProjectTasks SET ProjectTaskAssigneeID = ? WHERE ProjectTaskID = ?");
    query->addBindValue(employeeID.toInt());
    query->addBindValue(taskID.toInt());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x050");
    }
    sendAddTaskCompleted(true);
    delete query;
}

void Server::additionalForTeamTableData(QDataStream& in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin")
    {
        query->prepare("SELECT u.UserID, e.EmployeeFirstName, e.EmployeeLastName, e.EmployeeMiddleName, "
                       "e.EmployeeJobTitle, u.UserRole, e.EmployeeContactInformation, e.EmployeeAdditionalInfo, "
                       "os.ObjectStatusText "
                       "FROM Users u "
                       "INNER JOIN Employees e ON u.UserID = e.EmployeeID "
                       "INNER JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID "
                       "WHERE u.UserRole = 'Employee' "
                       "UNION "
                       "SELECT u.UserID, a.AdminFirstName, a.AdminLastName, a.AdminMiddleName, "
                       "a.AdminJobTitle, u.UserRole, a.AdminContactInformation,'', os.ObjectStatusText "
                       "FROM Users u "
                       "INNER JOIN Administrators a ON u.UserID = a.AdminID "
                       "INNER JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID "
                       "WHERE u.UserRole = 'Manager'");
    } else {
        query->prepare("SELECT DISTINCT e.EmployeeID, e.EmployeeFirstName, e.EmployeeLastName, e.EmployeeMiddleName, e.EmployeeJobTitle, "
                       "u.UserRole, e.EmployeeContactInformation, e.EmployeeAdditionalInfo, os.ObjectStatusText "
                       "FROM Users u "
                       "INNER JOIN Employees e ON u.UserID = e.EmployeeID "
                       "INNER JOIN ProjectTasks pt ON e.EmployeeID = pt.ProjectTaskAssigneeID "
                       "INNER JOIN Projects p ON pt.ProjectID = p.ProjectID "
                       "INNER JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID "
                       "WHERE p.ProjectManagerID = ?");
        query->addBindValue(socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x051");
    }
    else {
        QList<QStringList> team_data;
        QStringList headerLabels;
        headerLabels << "ID пользователя" << "Фамилия пользователя" << "Имя пользователя" << "Отчество пользователя"
                     << "Должность пользователя" << "Роль пользователя" << "Контактная информация" << "Дополнительная информация" << "Статус активности";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            team_data.append(rowValues);
        }
        sendTeamDataTableResult(headerLabels, columnCount, team_data.size(), team_data);
    }
    delete query;
}

void Server::additionalForOnlineTableData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT u.UserID, e.EmployeeFirstName, e.EmployeeLastName, e.EmployeeMiddleName, "
                   "e.EmployeeJobTitle, u.UserRole, "
                   "os.ObjectStatusText "
                   "FROM Users u "
                   "INNER JOIN Employees e ON u.UserID = e.EmployeeID "
                   "INNER JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID "
                   "WHERE u.UserRole = 'Employee' AND os.ObjectStatusText = 'Онлайн' "
                   "UNION "
                   "SELECT u.UserID, a.AdminFirstName, a.AdminLastName, a.AdminMiddleName, "
                   "a.AdminJobTitle, u.UserRole, os.ObjectStatusText "
                   "FROM Users u "
                   "INNER JOIN Administrators a ON u.UserID = a.AdminID "
                   "INNER JOIN ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID "
                   "WHERE (u.UserRole = 'Manager' OR u.UserRole = 'Admin') AND os.ObjectStatusText = 'Онлайн'");
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x052");
    }
    else {
        QList<QStringList> online_data;
        QStringList headerLabels;
        headerLabels << "ID пользователя" << "Фамилия пользователя" << "Имя пользователя" << "Отчество пользователя"
                     << "Должность пользователя" << "Роль пользователя" << "Статус активности";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            online_data.append(rowValues);
        }
        sendOnlineDataTableResult(headerLabels, columnCount, online_data.size(), online_data);
    }
    delete query;
}

void Server::additionalForAddAdminResult(QDataStream &in)
{
    QString EmpID;
    QString EmpJobTitle;
    in >> EmpID >> EmpJobTitle;
    query = new QSqlQuery(db);
    if (isNumeric(EmpID)){
        if (!getUserLogin(query, EmpID).isEmpty() && isUserOffline(query, EmpID)){
            query->prepare("UPDATE dbo.Users SET UserRole = 'Manager' WHERE UserID = :user_id");
            query->bindValue(":user_id", EmpID.toInt());
            if (!query->exec()) {
                additionalForSendErrorMessage(query, "2x018");
                delete query;
                return;
            }
            query->clear();
            query->prepare("INSERT INTO dbo.Administrators (AdminID, AdminFirstName, AdminLastName, AdminMiddleName, AdminJobTitle, AdminContactInformation) SELECT "
                           ":man_id, EmployeeFirstName, EmployeeLastName, EmployeeMiddleName, :man_jt, EmployeeContactInformation FROM "
                           "dbo.Employees WHERE EmployeeID = :emp_id");
            query->bindValue(":man_id", EmpID.toInt());
            query->bindValue(":man_jt", EmpJobTitle);
            query->bindValue(":emp_id", EmpID.toInt());
            if (!query->exec()) {
                query->clear();
                query->prepare("SELECT AdminID FROM dbo.Administrators WHERE AdminID = :admin_id");
                query->bindValue(":admin_id", EmpID);
                if (!query->exec()){
                    additionalForSendErrorMessage(query, "2x019");
                    delete query;
                    return;
                }
                query->clear();
                query->prepare("UPDATE dbo.Administrators SET AdminJobTitle = :admin_jt WHERE AdminID = :admin_id");
                query->bindValue(":admin_jt", EmpJobTitle);
                query->bindValue(":admin_id", EmpID);
                if (!query->exec()){
                    additionalForSendErrorMessage(query, "0x022");
                    delete query;
                    return;
                }
                sendAddedManResult(true);
            }
        }
        else{
            sendAddedManResult(false);
        }
    }
    else{
        sendAddedManResult(false);
    }
    delete query;
}

void Server::additionalForGetAdminTableData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT u.UserID, u.UserLogin, u.UserPswd, u.UserRole, os.ObjectStatusText, a.AdminLastName, "
                   "a.AdminFirstName, a.AdminMiddleName, a.AdminJobTitle, a.AdminContactInformation "
                   "FROM dbo.Users u INNER JOIN dbo.ObjectStatuses os ON u.UserActivityID = os.ObjectStatusID AND u.UserRole != 'Employee' AND u.UserRole != 'Admin' "
                   "INNER JOIN dbo.Administrators a ON u.UserID = a.AdminID");
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x020");
    }
    else{
        QList<QStringList> users_data;
        QStringList headerLabels;
        headerLabels << "ID пользователя" << "Логин" << "Пароль" << "Роль в системе"
                     << "Статус активности" << "Фамилия" << "Имя"
                     << "Отчество" << "Должность" << "Контактная информация";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            users_data.append(rowValues);
        }
        sendUsersManagerTableData(headerLabels, columnCount, users_data.size(), users_data);
    }
    delete query;
}

void Server::additionalForRemovedAdminResult(QDataStream &in)
{
    QString user_id;
    in >> user_id;
    query = new QSqlQuery(db);
    if (isNumeric(user_id)){
        if (!getUserLogin(query, user_id).isEmpty() && isUserOffline(query, user_id)){
            QString removed_userID = user_id;
            query->prepare("UPDATE dbo.Users SET UserRole = 'Employee' WHERE UserID = :user_id");
            query->bindValue(":user_id", removed_userID);
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x021");
                delete query;
                return;
            }
            sendRemovedManagerResult(true);
        }
        else{
            sendRemovedManagerResult(false);
        }
    }
    else{
        sendRemovedManagerResult(false);
    }
    delete query;
}

void Server::additionalForChangeAdminResult(QDataStream &in)
{
    QMap<QString, bool> change_manager_success;
    QString managerID, jobTitle, contactInformation;
    in >> managerID >> jobTitle >> contactInformation;

    query = new QSqlQuery(db);
    change_manager_success["ManagerID"] = isNumeric(managerID);
    change_manager_success["JobTitle"] = isCyrillic(jobTitle);
    change_manager_success["ContactInformation"] = true;

    bool allValid = std::all_of(change_manager_success.constBegin(), change_manager_success.constEnd(),
                                [](const bool &value) { return value; });
    bool ready_to_send = true;
    if (allValid && !getUserLogin(query, managerID).isEmpty() && isUserOffline(query, managerID))
    {
        query->prepare("UPDATE dbo.Administrators SET AdminJobTitle = ?, AdminContactInformation = ? WHERE AdminID = ?");
        query->addBindValue(jobTitle);
        query->addBindValue(contactInformation);
        query->addBindValue(managerID.toInt());
        if (!query->exec()){
            ready_to_send = false;
            additionalForSendErrorMessage(query, "2x023");
        }
    }
    if (ready_to_send){
        sendChangedManagerResult(change_manager_success);
    }
    delete query;
}

void Server::additionalForAllClosedRequestsTableData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT er.EmployeeRequestID, rc.RequestCategoryName, u.UserLogin, e.EmployeeFirstName, e.EmployeeLastName, "
                   "e.EmployeeMiddleName, os.ObjectStatusText, er.EmployeeRequestText, u_admin.UserLogin, a.AdminFirstName, "
                   "a.AdminLastName, a.AdminMiddleName, am.AdminMessageText "
                   "FROM dbo.EmployeeRequests er "
                   "INNER JOIN RequestCategories rc ON er.RequestCategoryID = rc.RequestCategoryID "
                   "INNER JOIN dbo.Users u ON er.UserID = u.UserID JOIN dbo.Employees e ON u.UserID = e.EmployeeID "
                   "INNER JOIN dbo.ObjectStatuses os ON er.EmployeeRequestStatusID = os.ObjectStatusID "
                   "LEFT JOIN dbo.AdminMessages am ON er.AdminMessageID = am.AdminMessageID "
                   "LEFT JOIN dbo.Users u_admin ON am.UserID = u_admin.UserID "
                   "LEFT JOIN dbo.Administrators a ON u_admin.UserID = a.AdminID "
                   "WHERE os.ObjectStatusText IN ('Принято', 'Отклонено')");
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x026");
    }
    else{
        QList<QStringList> users_data;
        QStringList headerLabels;
        headerLabels << "ID запроса" << "Категория запроса" << "Логин отправителя" << "Имя отправителя" << "Фамилия отправителя" << "Отчество отправителя"
                     << "Статус запроса" << "Содержание запроса" << "Логин закрывшего" << "Имя закрывшего" << "Фамилия закрывшего" << "Отчество закрывшего"
                     << "Ответ закрывшего";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            users_data.append(rowValues);
        }
        sendAllClosedRequests(headerLabels, columnCount, users_data.size(), users_data);
    }
    delete query;
}

void Server::additionalForAllProjectsAndTasksTableData(QDataStream& in)
{
    QString type_admin;
    in >> type_admin;
    query = new QSqlQuery(db);
    if (type_admin == "Admin"){
        query->prepare("SELECT P.ProjectName, P.ProjectDescription, PS.ObjectStatusText, A.AdminLastName, A.AdminFirstName, "
                       "A.AdminMiddleName, PT.ProjectTaskName, PT.ProjectTaskDescription, PTS.ObjectStatusText, "
                       "E.EmployeePersonnelNumber, E.EmployeeLastName, E.EmployeeFirstName, E.EmployeeMiddleName "
                       "FROM dbo.Projects P "
                       "INNER JOIN dbo.ObjectStatuses PS ON P.ProjectStatusID = PS.ObjectStatusID "
                       "INNER JOIN dbo.Administrators A ON P.ProjectManagerID = A.AdminID "
                       "LEFT JOIN dbo.ProjectTasks PT ON P.ProjectID = PT.ProjectID "
                       "LEFT JOIN dbo.ObjectStatuses PTS ON PT.ProjectTaskStatusID = PTS.ObjectStatusID "
                       "LEFT JOIN dbo.Employees E ON PT.ProjectTaskAssigneeID = E.EmployeeID "
                       "ORDER BY P.ProjectID, PT.ProjectTaskID");
    }
    else {
        query->prepare("SELECT P.ProjectName, P.ProjectDescription, PS.ObjectStatusText, A.AdminLastName, A.AdminFirstName, "
                       "A.AdminMiddleName, PT.ProjectTaskName, PT.ProjectTaskDescription, PTS.ObjectStatusText, "
                       "E.EmployeePersonnelNumber, E.EmployeeLastName, E.EmployeeFirstName, E.EmployeeMiddleName "
                       "FROM dbo.Projects P "
                       "INNER JOIN dbo.ObjectStatuses PS ON P.ProjectStatusID = PS.ObjectStatusID "
                       "INNER JOIN dbo.Administrators A ON P.ProjectManagerID = A.AdminID "
                       "LEFT JOIN dbo.ProjectTasks PT ON P.ProjectID = PT.ProjectID "
                       "LEFT JOIN dbo.ObjectStatuses PTS ON PT.ProjectTaskStatusID = PTS.ObjectStatusID "
                       "LEFT JOIN dbo.Employees E ON PT.ProjectTaskAssigneeID = E.EmployeeID "
                       "WHERE P.ProjectManagerID = ? "
                       "ORDER BY P.ProjectID, PT.ProjectTaskID");
        query->addBindValue(socketUserIDMap[socket]);
    }
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x027");
    }
    else{
        QList<QStringList> projects_data;
        QStringList headerLabels;
        headerLabels << "Название проекта" << "Описание проекта" << "Статус проекта" << "Фамилия руководителя" << "Имя руководителя" << "Отчество руководителя"
                     << "Название задачи" << "Описание задачи" << "Статус задачи" << "Табельный номер сотрудника" << "Фамилия сотрудника" << "Имя сотрудника"
                     << "Отчество сотрудника";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            projects_data.append(rowValues);
        }
        sendAllProjectsTasks(headerLabels, columnCount, projects_data.size(), projects_data);
    }
    delete query;
}

void Server::additionalForAddProjectTableData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT A.AdminID, A.AdminLastName, A.AdminFirstName, A.AdminMiddleName, P.ProjectID, "
                   "P.ProjectName, P.ProjectDescription, PS.ObjectStatusText "
                   "FROM dbo.Projects P "
                   "INNER JOIN dbo.ObjectStatuses PS ON P.ProjectStatusID = PS.ObjectStatusID "
                   "RIGHT JOIN dbo.Administrators A ON P.ProjectManagerID = A.AdminID "
                   "INNER JOIN dbo.Users U ON A.AdminID = U.UserID "
                   "WHERE U.UserRole IN ('Admin', 'Manager') "
                   "ORDER BY P.ProjectID");
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x028");
    }
    else{
        QList<QStringList> projects_data;
        QStringList headerLabels;
        headerLabels << "ID руководителя" << "Фамилия руководителя" << "Имя руководителя" << "Отчество руководителя"
                     << "ID проекта" << "Название проекта" << "Описание проекта" << "Статус проекта";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            projects_data.append(rowValues);
        }
        sendAddProjectDataRequest(headerLabels, columnCount, projects_data.size(), projects_data);
    }
    delete query;
}

void Server::additionalForAddNewProjectResult(QDataStream &in)
{
    QString projectManagerID, projectName, projectDescription;
    in >> projectManagerID >> projectName >> projectDescription;
    query = new QSqlQuery(db);
    query->prepare("INSERT INTO dbo.Projects (ProjectName, ProjectDescription, ProjectStatusID, ProjectManagerID) VALUES (?, ?, 8, ?)");
    query->addBindValue(projectName);
    query->addBindValue(projectDescription);
    query->addBindValue(projectManagerID.toInt());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x029");
    }
    sendAddProjectCompleted();
    delete query;
}

void Server::additionalForProjectForChangeTableData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT P.ProjectID, P.ProjectName, P.ProjectDescription, PS.ObjectStatusText, A.AdminLastName, A.AdminFirstName, "
                   "A.AdminMiddleName, PT.ProjectTaskName, PT.ProjectTaskDescription, PTS.ObjectStatusText, "
                   "E.EmployeePersonnelNumber, E.EmployeeLastName, E.EmployeeFirstName, E.EmployeeMiddleName "
                   "FROM dbo.Projects P "
                   "INNER JOIN dbo.ObjectStatuses PS ON P.ProjectStatusID = PS.ObjectStatusID "
                   "INNER JOIN dbo.Administrators A ON P.ProjectManagerID = A.AdminID "
                   "LEFT JOIN dbo.ProjectTasks PT ON P.ProjectID = PT.ProjectID "
                   "LEFT JOIN dbo.ObjectStatuses PTS ON PT.ProjectTaskStatusID = PTS.ObjectStatusID "
                   "LEFT JOIN dbo.Employees E ON PT.ProjectTaskAssigneeID = E.EmployeeID "
                   "ORDER BY P.ProjectID, PT.ProjectTaskID");
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x030");
    }
    else{
        QList<QStringList> projects_data;
        QStringList headerLabels;
        headerLabels << "ID проекта" << "Название проекта" << "Описание проекта" << "Статус проекта" << "Фамилия руководителя" << "Имя руководителя" << "Отчество руководителя"
                     << "Название задачи" << "Описание задачи" << "Статус задачи" << "Табельный номер сотрудника" << "Фамилия сотрудника" << "Имя сотрудника"
                     << "Отчество сотрудника";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            projects_data.append(rowValues);
        }
        sendProjectsDataForChange(headerLabels, columnCount, projects_data.size(), projects_data);
    }
    delete query;
}

void Server::additionalForRemovedProjectResult(QDataStream &in)
{
    QString project_id;
    in >> project_id;
    query = new QSqlQuery(db);
    query->prepare("SELECT ProjectStatusID FROM dbo.Projects WHERE ProjectID = :project_id");
    query->bindValue(":project_id", project_id.toInt());
    if (!query->exec() || !query->next()){
        additionalForSendErrorMessage(query, "0x031");
    }
    else{
        QString projectStatusID = query->value(0).toString();
        if (projectStatusID == "8"){
            query->prepare("SELECT ProjectTaskID FROM dbo.ProjectTasks WHERE ProjectID = ?");
            query->addBindValue(project_id.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x032");
            }
            if (query->next()){
                query->prepare("DELETE FROM dbo.ProjectTasks WHERE ProjectID = ?");
                query->addBindValue(project_id.toInt());
                if (!query->exec()){
                    additionalForSendErrorMessage(query, "0x033");
                }
            }
            query->prepare("DELETE FROM dbo.Projects WHERE ProjectID = ?");
            query->addBindValue(project_id.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x034");
            }
        }
    }
    sendRemoveChangeProjectCompleted();
    delete query;
}

void Server::additionalForChangedProjectResult(QDataStream &in)
{
    QString projectID, projectName, projectDescription;
    in >> projectID >> projectName >> projectDescription;
    query = new QSqlQuery(db);
    query->prepare("UPDATE dbo.Projects SET ProjectName = ?, ProjectDescription = ? WHERE ProjectID = ?");
    query->addBindValue(projectName);
    query->addBindValue(projectDescription);
    query->addBindValue(projectID.toInt());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "0x035");
    }
    sendRemoveChangeProjectCompleted();
    delete query;
}

void Server::additionalForWorkedProjectResult(QDataStream &in)
{
    QString project_id;
    in >> project_id;
    query = new QSqlQuery(db);
    query->prepare("SELECT ProjectStatusID FROM dbo.Projects WHERE ProjectID = :project_id");
    query->bindValue(":project_id", project_id.toInt());
    if (!query->exec() || !query->next()){
        additionalForSendErrorMessage(query, "0x041");
    }
    else{
        QString projectStatusID = query->value(0).toString();
        if (projectStatusID == "8"){
            query->prepare("SELECT ProjectTaskID FROM dbo.ProjectTasks WHERE ProjectID = ?");
            query->addBindValue(project_id.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x042");
            }
            if (query->next()){
                query->prepare("UPDATE dbo.ProjectTasks SET ProjectTaskStatusID = 7 WHERE ProjectID = ?");
                query->addBindValue(project_id.toInt());
                if (!query->exec()){
                    additionalForSendErrorMessage(query, "0x043");
                }
            }
            query->prepare("UPDATE dbo.Projects SET ProjectStatusID = 7 WHERE ProjectID = ?");
            query->addBindValue(project_id.toInt());
            if (!query->exec()){
                additionalForSendErrorMessage(query, "0x044");
            }
        }
    }
    sendRemoveChangeProjectCompleted();
    delete query;
}

void Server::additionalForProjectManagerForProjectResult(QDataStream &in)
{
    QString projectManagerID, projectID;
    in >> projectManagerID >> projectID;
    query = new QSqlQuery(db);
    query->prepare("UPDATE dbo.Projects SET ProjectManagerID = ? WHERE ProjectID = ?");
    query->addBindValue(projectManagerID.toInt());
    query->addBindValue(projectID.toInt());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x049");
    }
    sendAddProjectCompleted();
    delete query;
}

void Server::additionalForSendErrorMessage(QSqlQuery *query, QString error_code)
{
    qDebug() << "Ошибка выполнения запроса: " << query->lastQuery() << "\nСведения об ошибке:" << query->lastError().text();
    sendErrorMessage("Код: " + error_code + ". На стороне сервера произошла ошибка. Приносим свои извинения. Сообщите администратору о проблеме.");
}

void Server::additionalForSendEmployeeCreditalsData()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT "
                   "e.EmployeeLastName, "
                   "e.EmployeeFirstName, "
                   "e.EmployeeMiddleName, "
                   "e.EmployeeJobTitle, "
                   "e.EmployeePersonnelNumber, "
                   "e.EmployeeContactInformation, "
                   "e.EmployeeAdditionalInfo, "
                   "u.UserLogin, "
                   "u.UserPswd "
                   "FROM Employees e "
                   "JOIN Users u ON e.EmployeeID = u.UserID "
                   "WHERE e.EmployeeID = :user_id");
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x022");
    }
    else{
        QList<QStringList> users_data;
        QStringList headerLabels;
        headerLabels << "Фамилия" << "Имя" << "Отчество" << "Должность"
                     << "Табельный номер" << "Контактная информация" << "Дополнительная информация"
                     << "Логин" << "Пароль";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            users_data.append(rowValues);
        }
        sendEmployeeCreditalsDataResult(headerLabels, columnCount, users_data.size(), users_data);
    }
    delete query;
}

void Server::additionalForSendEmployeeCompleteTasks()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT p.ProjectName, pt.ProjectTaskName, pt.ProjectTaskDescription, os.ObjectStatusText "
                   "FROM dbo.ProjectTasks pt "
                   "INNER JOIN dbo.Projects p ON p.ProjectID = pt.ProjectID "
                   "INNER JOIN dbo.Users u ON pt.ProjectTaskAssigneeID = u.UserID "
                   "INNER JOIN dbo.ObjectStatuses os ON os.ObjectStatusID = pt.ProjectTaskStatusID  "
                   "WHERE u.UserID = :user_id AND os.ObjectStatusText = 'Завершено'");
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x021");
    }
    else{
        QList<QStringList> complete_tasks;
        QStringList headerLabels;
        headerLabels << "Проект" << "Проектная задача" << "Описание задачи" << "Статус выполнения задачи";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            complete_tasks.append(rowValues);
        }
        sendEmployeeCompleteTasksResult(headerLabels, columnCount, complete_tasks.size(), complete_tasks);
    }
    delete query;
}

void Server::additionalForSendEmployeeUnfinishedTasks()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT p.ProjectName, pt.ProjectTaskName, pt.ProjectTaskDescription, os.ObjectStatusText "
                   "FROM dbo.ProjectTasks pt "
                   "INNER JOIN dbo.Projects p ON p.ProjectID = pt.ProjectID "
                   "INNER JOIN dbo.Users u ON pt.ProjectTaskAssigneeID = u.UserID "
                   "INNER JOIN dbo.ObjectStatuses os ON os.ObjectStatusID = pt.ProjectTaskStatusID  "
                   "WHERE u.UserID = :user_id AND os.ObjectStatusText = 'Не завершено'");
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x023");
    }
    else{
        QList<QStringList> unfinished_tasks;
        QStringList headerLabels;
        headerLabels << "Проект" << "Проектная задача" << "Описание задачи" << "Статус выполнения задачи";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue = query->value(i).toString();
                rowValues.append(rowValue);
            }
            unfinished_tasks.append(rowValues);
        }
        sendEmployeeUnfinishedTasksResult(headerLabels, columnCount, unfinished_tasks.size(), unfinished_tasks);
    }
    delete query;
}

void Server::additionalForSendEmployeeTimeData()
{
    QStringList time_data;
    query = new QSqlQuery(db);
    query->prepare("SELECT "
                   "SUM(CASE WHEN WorkTimeAnomalyID = 4 THEN ABS(DATEDIFF(MINUTE, WorkTimeAnomalyRecordBegin, WorkTimeAnomalyRecordEnd)) ELSE 0 END) AS TotalMinutes_Delay, "
                   "SUM(CASE WHEN WorkTimeAnomalyID = 3 THEN ABS(DATEDIFF(MINUTE, WorkTimeAnomalyRecordEnd, WorkTimeAnomalyRecordBegin)) ELSE 0 END) AS TotalMinutes_Late, "
                   "SUM(CASE WHEN WorkTimeAnomalyID IN (1, 2, 5, 6) THEN ABS(DATEDIFF(MINUTE, WorkTimeAnomalyRecordEnd, WorkTimeAnomalyRecordBegin)) ELSE 0 END) AS TotalMinutes_Overtime, "
                   "COUNT(CASE WHEN WorkTimeAnomalyID = 4 THEN 1 END) AS AnomalyCount_Delay, "
                   "COUNT(CASE WHEN WorkTimeAnomalyID = 3 THEN 1 END) AS AnomalyCount_Late, "
                   "COUNT(CASE WHEN WorkTimeAnomalyID IN (1, 2, 5, 6) THEN 1 END) AS AnomalyCount_Overtime "
                   "FROM WorkTimeAnomalyRecords "
                   "WHERE UserID = :user_id AND "
                   "(WorkTimeAnomalyID IN (4, 3, 1, 2, 5, 6)) AND "
                   "WorkTimeAnomalyRecordBegin IS NOT NULL AND "
                   "WorkTimeAnomalyRecordEnd IS NOT NULL");
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x019");
    } else{
        if (query->next()){
            int total_minutes_delay = query->value("TotalMinutes_Delay").toInt();
            int total_minutes_late = query->value("TotalMinutes_Late").toInt();
            int total_minutes_overtime = query->value("TotalMinutes_Overtime").toInt();
            int anomaly_count_delay = query->value("AnomalyCount_Delay").toInt();
            int anomaly_count_late = query->value("AnomalyCount_Late").toInt();
            int anomaly_count_overtime = query->value("AnomalyCount_Overtime").toInt();

            time_data.append(QString("Количество: %1 Время: %2:%3")
                                 .arg(anomaly_count_delay)
                                 .arg(total_minutes_delay / 60, 2, 10, QChar('0'))
                                 .arg(total_minutes_delay % 60, 2, 10, QChar('0')));

            time_data.append(QString("Количество: %1 Время: %2:%3")
                                 .arg(anomaly_count_late)
                                 .arg(total_minutes_late / 60, 2, 10, QChar('0'))
                                 .arg(total_minutes_late % 60, 2, 10, QChar('0')));

            time_data.append(QString("Количество: %1 Время: %2:%3")
                                 .arg(anomaly_count_overtime)
                                 .arg(total_minutes_overtime / 60, 2, 10, QChar('0'))
                                 .arg(total_minutes_overtime % 60, 2, 10, QChar('0')));
            query->prepare("SELECT SUM(DATEDIFF(minute, WorkTimeRecordBegin, WorkTimeRecordEnd)) AS TotalWorkTime "
                           "FROM WorkTimeRecords "
                           "WHERE UserID = :user_id "
                           "GROUP BY UserID;");
            query->bindValue(":user_id", socketUserIDMap[socket]);
            if (!query->exec()){
                additionalForSendErrorMessage(query, "1x020");
            }
            else{
                if (query->next()) {
                    int total_work_time = query->value("TotalWorkTime").toInt();
                    int total_hours = total_work_time / 60;
                    int total_minutes = total_work_time % 60;
                    time_data.append(QString("Общее время работы: %1:%2")
                                         .arg(total_hours, 2, 10, QChar('0'))
                                         .arg(total_minutes, 2, 10, QChar('0')));
                    sendEmployeeTimeData(time_data);
                }
            }
        }
    }
    delete query;
}

/*СОТРУДНИК*/
void Server::additionalForSendEmployeeTableWorkGrafResult()
{
    query = new QSqlQuery(db);
    query->prepare("WITH EmployeeProjects AS ("
                   "    SELECT DISTINCT PT.ProjectID "
                   "    FROM ProjectTasks PT "
                   "    WHERE PT.ProjectTaskAssigneeID = :emp_id "
                   "), "
                   "Colleagues AS ( "
                   "    SELECT DISTINCT PT.ProjectTaskAssigneeID AS UserID "
                   "    FROM ProjectTasks PT "
                   "    INNER JOIN EmployeeProjects EP ON PT.ProjectID = EP.ProjectID "
                   "), "
                   "CurrentWorkSchedules AS ( "
                   "    SELECT "
                   "        WSE.UserID, "
                   "        WSE.MondayBegin, WSE.MondayEnd, "
                   "        WSE.TuesdayBegin, WSE.TuesdayEnd, "
                   "        WSE.WednesdayBegin, WSE.WednesdayEnd, "
                   "        WSE.ThursdayBegin, WSE.ThursdayEnd, "
                   "        WSE.FridayBegin, WSE.FridayEnd, "
                   "        WSE.SaturdayBegin, WSE.SaturdayEnd, "
                   "        WSE.SundayBegin, WSE.SundayEnd "
                   "    FROM WorkScheduleEmployee WSE "
                   "    INNER JOIN Colleagues C ON WSE.UserID = C.UserID "
                   "    WHERE "
                   "    CONVERT(date, COALESCE(WSE.MondayBegin, WSE.TuesdayBegin, WSE.WednesdayBegin, WSE.ThursdayBegin, WSE.FridayBegin, WSE.SaturdayBegin, WSE.SundayBegin)) <= :current_date "
                   "    AND CONVERT(date, COALESCE(WSE.SundayBegin, WSE.SaturdayBegin, WSE.FridayBegin, WSE.ThursdayBegin, WSE.WednesdayBegin, WSE.TuesdayBegin, WSE.MondayBegin)) >= :current_date "
                   ") "
                   "SELECT "
                   "    CONCAT(E.EmployeeLastName, ' ', E.EmployeeFirstName,' ', E.EmployeeMiddleName) AS EmployeeFullName, "
                   "    CWSE.MondayBegin, CWSE.MondayEnd, "
                   "    CWSE.TuesdayBegin, CWSE.TuesdayEnd, "
                   "    CWSE.WednesdayBegin, CWSE.WednesdayEnd, "
                   "    CWSE.ThursdayBegin, CWSE.ThursdayEnd, "
                   "    CWSE.FridayBegin, CWSE.FridayEnd, "
                   "    CWSE.SaturdayBegin, CWSE.SaturdayEnd, "
                   "    CWSE.SundayBegin, CWSE.SundayEnd "
                   "FROM CurrentWorkSchedules CWSE "
                   "INNER JOIN Employees E ON E.EmployeeID = CWSE.UserID "
                   "ORDER BY CWSE.UserID;");
    query->bindValue(":emp_id", socketUserIDMap[socket]);
    query->bindValue(":current_date", QDate::currentDate());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x018");
    }
    else{
        QList<QStringList> work_graf_data;
        QStringList headerLabels;
        headerLabels << "ФИО сотрудника"
                     << "Понедельник. Начало" << "Понедельник. Конец"
                     << "Вторник. Начало" << "Вторник. Конец"
                     << "Среда. Начало" << "Среда. Конец"
                     << "Четверг. Начало" << "Четверг. Конец"
                     << "Пятница. Начало" << "Пятница. Конец"
                     << "Суббота. Начало" << "Суббота. Конец"
                     << "Воскресенье. Начало" << "Воскресенье. Конец";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue;
                if (i == 0){
                    rowValue = query->value(i).toString();
                }
                else{
                    QDateTime workGrafBeginEndTime = query->value(i).toDateTime();
                    rowValue = workGrafBeginEndTime.toString("dd.MM.yyyy hh:mm:ss");
                }
                rowValues.append(rowValue);
            }
            work_graf_data.append(rowValues);
        }
        sendEmployeeTableWorkGrafResult(headerLabels, columnCount, work_graf_data.size(), work_graf_data);
    }
    delete query;
}

void Server::additionalForSendEmployeeTableTimeAnomaliesResult()
{
    query = new QSqlQuery(db);
    query->prepare("SELECT WTAR.WorkTimeAnomalyRecordID, WTAR.WorkTimeAnomalyRecordBegin, WTAR.WorkTimeAnomalyRecordEnd, WTA.WorkTimeAnomalyDescription "
                   "FROM dbo.WorkTimeAnomalyRecords WTAR "
                   "INNER JOIN dbo.WorkTimeAnomalies WTA "
                   "ON WTAR.WorkTimeAnomalyID = WTA.WorkTimeAnomalyID "
                   "WHERE WTAR.UserID = :user_id");
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "1x017");
    }
    else{
        QList<QStringList> time_anomalies_data;
        QStringList headerLabels;
        headerLabels << "Номер записи в системе" << "Дата и время регистрации исключительной ситуации" <<
            "Дата и время окончания регистрации исключительной ситуации/по Вашему рабочему графику" << "Описание исключительной ситуации";
        int columnCount = query->record().count();
        while (query->next()){
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i){
                QString rowValue;
                if (i != 1 && i != 2){
                    rowValue = query->value(i).toString();
                }
                else{
                    QDateTime workTimeAnomalyRecordBegin = query->value(i).toDateTime();
                    rowValue = workTimeAnomalyRecordBegin.toString("dd.MM.yyyy hh:mm:ss");
                }
                rowValues.append(rowValue);
            }
            time_anomalies_data.append(rowValues);
        }
        sendEmployeeTableTimeAnomaliesResult(headerLabels, columnCount, time_anomalies_data.size(), time_anomalies_data);
    }
    delete query;
}

void Server::additionalForTakeIntoEntryTime()
{
    query = new QSqlQuery(db);
    std::pair<QVariant, bool> result = getBeginCurrentDateSheduleTime(query);
    std::pair<QVariant, bool> result_for_notEnough = getEndCurrentDateSheduleTime(query);
    if (result.second && result_for_notEnough.second){
        QVariant dbTimeVariant = result.first;
        QVariant dbTimeEndVariant = result_for_notEnough.first;
        bool ready_to_send = true;
        if (dbTimeVariant.isNull()) {
            //Проверка на отпуск.
            query->prepare("SELECT * FROM dbo.Vacations WHERE :current_date BETWEEN VacationBeginDate AND VacationEndDate AND UserID = :user_id");
            query->bindValue(":current_date", QDate::currentDate());
            query->bindValue(":user_id", socketUserIDMap[socket]);
            if (!query->exec()){
                ready_to_send = false;
                additionalForSendErrorMessage(query, "0x018");
            }
            else{
                if (query->next()){
                    //Отпуск.
                    query->prepare("INSERT INTO dbo.WorkTimeAnomalyRecords (WorkTimeAnomalyRecordBegin, WorkTimeAnomalyRecordEnd, WorkTimeAnomalyID, UserID) "
                                   "VALUES (:cur_datetime_begin, NULL, 2, :user_id)");
                    query->bindValue(":cur_datetime_begin", QDateTime::currentDateTime().toString(Qt::ISODate));
                    query->bindValue(":user_id", socketUserIDMap[socket]);
                    if (!query->exec()){
                        ready_to_send = false;
                        additionalForSendErrorMessage(query, "0x019");
                    }
                }
                else{
                    //Выходной
                    query->prepare("INSERT INTO dbo.WorkTimeAnomalyRecords (WorkTimeAnomalyRecordBegin, WorkTimeAnomalyRecordEnd, WorkTimeAnomalyID, UserID) "
                                   "VALUES (:cur_datetime_begin, NULL, 1, :user_id)");
                    query->bindValue(":cur_datetime_begin", QDateTime::currentDateTime().toString(Qt::ISODate));
                    query->bindValue(":user_id", socketUserIDMap[socket]);
                    if (!query->exec()){
                        ready_to_send = false;
                        additionalForSendErrorMessage(query, "0x020");
                    }
                }
            }
        } else {
            QString dbTime = dbTimeVariant.toString();
            QTime currentTime = QTime::currentTime();
            QTime dbTimeParsed = QTime::fromString(dbTime, "hh:mm:ss.zzz");
            QDateTime combinedDateTime(QDate::currentDate(), dbTimeParsed);
            //
            QString dbTimeEnd = dbTimeEndVariant.toString();
            QTime dbTimeEndParsed = QTime::fromString(dbTimeEnd, "hh:mm:ss.zzz");
            QDateTime combinedDateTimeEnd(QDate::currentDate(), dbTimeEndParsed);
            //
            int differenceMinutes = currentTime.msecsTo(dbTimeParsed) / 60000;
            int differenceMinutesForEnd = currentTime.msecsTo(dbTimeEndParsed) / 60000;
            //
            bool late = true, notEnough = false, overWorking = false;
            query->prepare("SELECT TOP 1 WorkTimeAnomalyRecordBegin, WorkTimeAnomalyID "
                           "FROM dbo.WorkTimeAnomalyRecords "
                           "WHERE UserID = :user_id "
                           "AND CAST(WorkTimeAnomalyRecordBegin AS DATE) = CAST(GETDATE() AS DATE) "
                           "ORDER BY WorkTimeAnomalyRecordBegin DESC");
            query->bindValue(":user_id", socketUserIDMap[socket]);
            if (!query->exec()){
                ready_to_send = false;
                additionalForSendErrorMessage(query, "0x027");
            } else{
                if (query->next()) {
                    QDateTime lastAnomalyDateTime = query->value("WorkTimeAnomalyRecordBegin").toDateTime();
                    int lastAnomalyID = query->value("WorkTimeAnomalyID").toInt();
                    if (lastAnomalyID == 4 || lastAnomalyID == 3) {
                        if (lastAnomalyDateTime.time() >= combinedDateTime.time() && lastAnomalyDateTime.time() <= combinedDateTimeEnd.time()) {
                            late = false;
                        }
                    }
                    if (lastAnomalyID == 4 ){
                        if (lastAnomalyDateTime.time() >= combinedDateTime.time() && lastAnomalyDateTime.time() <= combinedDateTimeEnd.time()){
                            notEnough = true;
                        }
                    }
                    if (lastAnomalyID == 5 || lastAnomalyID == 6){
                        if (lastAnomalyDateTime.time() < combinedDateTime.time() && lastAnomalyDateTime.time() > combinedDateTimeEnd.time()){
                            overWorking = true;
                        }
                    }
                }
                if (currentTime > dbTimeParsed && currentTime < dbTimeEndParsed){
                        if (late){
                            if (differenceMinutes < -5){
                                query->prepare("INSERT INTO dbo.WorkTimeAnomalyRecords (WorkTimeAnomalyRecordBegin, WorkTimeAnomalyID, UserID, WorkTimeAnomalyRecordEnd) "
                                               "VALUES (:cur_datetime, 3, :user_id, :graf_datetime)");
                                query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                                query->bindValue(":user_id", socketUserIDMap[socket]);
                                query->bindValue(":graf_datetime", combinedDateTime.toString(Qt::ISODate));
                                if (!query->exec()){
                                    ready_to_send = false;
                                    additionalForSendErrorMessage(query, "0x022");
                                }
                            }
                        }
                        if (notEnough){
                            if (differenceMinutes < -5)
                            {
                                query->prepare("UPDATE dbo.WorkTimeAnomalyRecords "
                                               "SET WorkTimeAnomalyRecordEnd = :cur_datetime "
                                               "WHERE WorkTimeAnomalyRecordID = ("
                                               "SELECT TOP 1 WorkTimeAnomalyRecordID "
                                               "FROM dbo.WorkTimeAnomalyRecords "
                                               "WHERE UserID = :user_id AND WorkTimeAnomalyID = 4 "
                                               "ORDER BY WorkTimeAnomalyRecordBegin DESC"
                                               ") AND UserID = :user_id");
                                query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                                query->bindValue(":user_id", socketUserIDMap[socket]);
                                if (!query->exec()) {
                                    ready_to_send = false;
                                    additionalForSendErrorMessage(query, "0x028");
                                }
                            }
                        }
                }
                else if (currentTime <= dbTimeParsed)
                {
                    if (differenceMinutes > 5 || overWorking){
                        query->prepare("INSERT INTO dbo.WorkTimeAnomalyRecords (WorkTimeAnomalyRecordBegin, WorkTimeAnomalyID, UserID, WorkTimeAnomalyRecordEnd) "
                                       "VALUES (:cur_datetime, 5, :user_id, :graf_datetime)");
                        query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                        query->bindValue(":user_id", socketUserIDMap[socket]);
                        query->bindValue(":graf_datetime", combinedDateTime.toString(Qt::ISODate));
                        if (!query->exec()){
                            ready_to_send = false;
                            additionalForSendErrorMessage(query, "0x036");
                        }
                    }
                }
                else if (currentTime >= dbTimeEndParsed){
                    if (differenceMinutesForEnd < -5){
                        query->prepare("INSERT INTO dbo.WorkTimeAnomalyRecords (WorkTimeAnomalyRecordBegin, WorkTimeAnomalyID, UserID, WorkTimeAnomalyRecordEnd) "
                                       "VALUES (:cur_datetime, 6, :user_id, NULL)");
                        query->bindValue(":user_id", socketUserIDMap[socket]);
                        query->bindValue(":cur_datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
                        if (!query->exec()){
                            ready_to_send = false;
                            additionalForSendErrorMessage(query, "0x037");
                        }
                    }
                }
            }
        }
        if (ready_to_send){
            query->prepare("INSERT INTO dbo.WorkTimeRecords (WorkTimeRecordBegin, WorkTimeTypeID, UserID) VALUES (?, 1, ?)");
            query->addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
            query->addBindValue(socketUserIDMap[socket]);
            if (query->exec()){
                sendCheckEntryTimeDataResult(true);
            }
            else{
                additionalForSendErrorMessage(query, "0x009");
            }
        }
    }
    else{
        sendCheckEntryTimeDataResult(false);
    }
    delete query;
}

void Server::additionalForTakeIntoMainTime(QDataStream &in)
{
    QString location;
    int type_time = 0;
    in >> location;
    query = new QSqlQuery(db);
    if (location == "Раздел Общая статистика"){
        type_time = 2;
    }
    else if (location == "Раздел Регистрация времени"){
        type_time = 3;
    }
    else if (location == "Раздел Рабочий график"){
        type_time = 8;
    }
    else if (location == "Раздел Исключительные ситуации"){
        type_time = 9;
    }
    else if (location == "Раздел Начать работу над проектами и задачами"){
        type_time = 10;
    }
    else if (location == "Раздел Отправить запрос"){
        type_time = 12;
    }
    else if (location == "Раздел Просмотр запросов"){
        type_time = 13;
    }
    else if (location == "Раздел Просмотр активных пользователей"){
        type_time = 14;
    }
    query->prepare("UPDATE dbo.WorkTimeRecords SET WorkTimeRecordEnd = :cur_time WHERE WorkTimeRecordID = "
                   "(SELECT TOP 1 WorkTimeRecordID FROM WorkTimeRecords AS WTR "
                   "JOIN WorkTimeTypes AS WTT ON WTR.WorkTimeTypeID = WTT.WorkTimeTypeID "
                   "WHERE WTR.UserID = :user_id "
                   "AND WTR.WorkTimeRecordEnd IS NULL "
                   "AND WTT.WorkTimeTypeDescription NOT LIKE 'Раздел %[.]%' "
                   "ORDER BY WTR.WorkTimeRecordBegin DESC)");
    query->bindValue(":cur_time", QDateTime::currentDateTime().toString(Qt::ISODate));
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "0x011");
    }
    else{
        query->prepare("INSERT INTO dbo.WorkTimeRecords (WorkTimeRecordBegin, WorkTimeRecordEnd, WorkTimeTypeID, UserID) "
                       "VALUES (?, ?, ?, ?)");
        query->addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
        query->addBindValue(QVariant::fromValue<QDateTime>(QDateTime()));
        query->addBindValue(type_time);
        query->addBindValue(socketUserIDMap[socket]);
        if (!query->exec()){
            additionalForSendErrorMessage(query, "0x012");
        }
        else{
            sendTakeIntoMainTimeResult(location);
        }
    }
    delete query;
}

void Server::additionalForTakeIntoBeginSubmainTime(QDataStream &in)
{
    QString action;
    int type_time = 0;
    in >> action;
    query = new QSqlQuery(db);
    if (action == "Начать Обеденный перерыв"){
        type_time = 4;
    }
    else if (action == "Начать Совещание"){
        type_time = 5;
    }
    else if (action == "Начать Отсутствие по работе"){
        type_time = 6;
    }
    else if (action == "Начать Отсутствие по личной нужде"){
        type_time = 7;
    }
    else if (action == "Начать Выполнение проектной задачи"){
        type_time = 11;
    }
    query->prepare("INSERT INTO dbo.WorkTimeRecords (WorkTimeRecordBegin, WorkTimeRecordEnd, WorkTimeTypeID, UserID) "
                   "VALUES (?, ?, ?, ?)");
    query->addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
    query->addBindValue(QVariant::fromValue<QDateTime>(QDateTime()));
    query->addBindValue(type_time);
    query->addBindValue(socketUserIDMap[socket]);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "0x013");
    }
    delete query;
}

void Server::additionalForTakeIntoEndSubmainTime(QDataStream &in)
{
    QString action;
    int type_time = 0;
    in >> action;
    query = new QSqlQuery(db);
    if (action == "Закончить Обеденный перерыв"){
        type_time = 4;
    }
    else if (action == "Закончить Совещание"){
        type_time = 5;
    }
    else if (action == "Закончить Отсутствие по работе"){
        type_time = 6;
    }
    else if (action == "Закончить Отсутствие по личной нужде"){
        type_time = 7;
    }
    else if (action == "Закончить Выполнение проектной задачи"){
        type_time = 11;
    }
    query->prepare("UPDATE dbo.WorkTimeRecords "
                   "SET WorkTimeRecordEnd = :cur_time "
                   "WHERE UserID = :user_id "
                   "AND WorkTimeRecordEnd IS NULL "
                   "AND WorkTimeTypeID = :type_time");
    query->bindValue(":cur_time", QDateTime::currentDateTime().toString(Qt::ISODate));
    query->bindValue(":user_id", socketUserIDMap[socket]);
    query->bindValue(":type_time", type_time);
    if (!query->exec()){
        additionalForSendErrorMessage(query, "0x014");
    }
    delete query;
}

//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ.
bool Server::isCyrillic(const QString &str)
{
    static QRegularExpression cyrillicRegex("^[а-яА-ЯёЁ]+$");
    return cyrillicRegex.match(str).hasMatch();
}

bool Server::isNumeric(const QString &str)
{
    static QRegularExpression numericRegex("^[1-9]\\d*$");
    return numericRegex.match(str).hasMatch();
}

bool Server::isUniqueLogin(const QString &login, QSqlQuery *query)
{
    query->prepare("SELECT UserLogin FROM dbo.Users WHERE UserLogin = :user_login");
    query->bindValue(":user_login", login);
    if (query->exec()){
        return !query->next();
    }
    else{
        additionalForSendErrorMessage(query, "0x004");
        return false;
    }
}

bool Server::isUniquePersonnelNumber(const int& personnelNumber, QSqlQuery *query)
{
    query->prepare("SELECT EmployeePersonnelNumber FROM dbo.Employees WHERE EmployeePersonnelNumber = :pers_number");
    query->bindValue(":pers_number", personnelNumber);
    if (query->exec()){
        return !query->next();
    }
    else{
        additionalForSendErrorMessage(query, "0x005");
        return false;
    }
}

int Server::getUserID(QSqlQuery *query, QString& user_login)
{
    query->prepare("SELECT UserID FROM dbo.Users WHERE UserLogin = ?");
    query->addBindValue(user_login);
    if (query->exec())
    {
        if (query->next()){
            return query->value(0).toInt();
        }
        else{
            return -1;
        }
    }
    else
    {
        additionalForSendErrorMessage(query, "0x006");
        return -1;
    }
}

QString Server::getUserLogin(QSqlQuery *query, QString &user_id)
{
    query->prepare("SELECT UserLogin FROM dbo.Users WHERE UserID = ?");
    query->addBindValue(user_id.toInt());
    if (query->exec())
    {
        if (query->next()){
            return query->value(0).toString();
        }
        else{
            return "";
        }
    }
    else
    {
        additionalForSendErrorMessage(query, "2x006");
        return "";
    }
}

int Server::getEmployeePersonnelNumber(QSqlQuery *query, QString& employee_id)
{
    query->prepare("SELECT EmployeePersonnelNumber FROM dbo.Employees WHERE EmployeeID = ?");
    query->addBindValue(employee_id.toInt());
    if (query->exec())
    {
        if (query->next()){
            return query->value(0).toInt();
        }
        else{
            return -1;
        }
    }
    else
    {
        additionalForSendErrorMessage(query, "2x007");
        return -1;
    }
}

QString Server::getUserRole(QSqlQuery *query, QString &user_id)
{
    query->prepare("SELECT UserRole FROM dbo.Users WHERE Users.UserID = ?");
    query->addBindValue(user_id.toInt());
    if (query->exec()){
        if (query->next()){
            QString user_role = query->value(0).toString();
            return  user_role;
        }
        else{
            return "";
        }
    }
    else{
        additionalForSendErrorMessage(query, "2x008");
        return "";
    }
}

bool Server::isUserOffline(QSqlQuery *query, QString &user_id)
{
    query->prepare("SELECT * FROM dbo.Users WHERE Users.UserID = ? AND Users.UserActivityID = 1");
    query->addBindValue(user_id.toInt());
    if (!query->exec()){
        additionalForSendErrorMessage(query, "2x002");
        return false;
    }
    else{
        return query->next();
    }
}

QString Server::getProjTaskID(QSqlQuery *query, QString &task_name)
{
    query->prepare("SELECT ProjectTaskID FROM dbo.ProjectTasks WHERE ProjectTaskName = :proj_task_name");
    query->bindValue(":proj_task_name", task_name);
    if (query->exec() && query->next())
    {
        return query->value(0).toString();
    }
    else{
        additionalForSendErrorMessage(query, "1x009");
        return "";
    }
}

std::pair<QVariant, bool> Server::getBeginCurrentDateSheduleTime(QSqlQuery *query)
{
    query->prepare(
        "SELECT 1 "
        "FROM dbo.WorkScheduleEmployee "
        "WHERE UserID = :user_id "
        "AND ("
        "    (MondayBegin IS NOT NULL AND DATEPART(week, MondayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, MondayBegin) = DATEPART(year, GETDATE())) "
        " OR (TuesdayBegin IS NOT NULL AND DATEPART(week, TuesdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, TuesdayBegin) = DATEPART(year, GETDATE())) "
        " OR (WednesdayBegin IS NOT NULL AND DATEPART(week, WednesdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, WednesdayBegin) = DATEPART(year, GETDATE())) "
        " OR (ThursdayBegin IS NOT NULL AND DATEPART(week, ThursdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, ThursdayBegin) = DATEPART(year, GETDATE())) "
        " OR (FridayBegin IS NOT NULL AND DATEPART(week, FridayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, FridayBegin) = DATEPART(year, GETDATE())) "
        " OR (SaturdayBegin IS NOT NULL AND DATEPART(week, SaturdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, SaturdayBegin) = DATEPART(year, GETDATE())) "
        " OR (SundayBegin IS NOT NULL AND DATEPART(week, SundayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, SundayBegin) = DATEPART(year, GETDATE())) "
        ")");
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()) {
        additionalForSendErrorMessage(query, "0x017");
        return std::make_pair(QVariant(), false);
    }
    else{
        if (!query->next()) {
            return std::make_pair(QVariant(), false);
        }
        query->prepare(
            "SELECT "
            "    CASE DATEPART(WEEKDAY, GETDATE()) "
            "        WHEN 1 THEN CONVERT(time, MondayBegin) "
            "        WHEN 2 THEN CONVERT(time, TuesdayBegin) "
            "        WHEN 3 THEN CONVERT(time, WednesdayBegin) "
            "        WHEN 4 THEN CONVERT(time, ThursdayBegin) "
            "        WHEN 5 THEN CONVERT(time, FridayBegin) "
            "        WHEN 6 THEN CONVERT(time, SaturdayBegin) "
            "        WHEN 7 THEN CONVERT(time, SundayBegin) "
            "    END AS CurrentTime "
            "FROM dbo.WorkScheduleEmployee "
            "WHERE UserID = :user_id "
            "AND ("
            "    (MondayBegin IS NOT NULL AND DATEPART(week, MondayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, MondayBegin) = DATEPART(year, GETDATE())) "
            " OR (TuesdayBegin IS NOT NULL AND DATEPART(week, TuesdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, TuesdayBegin) = DATEPART(year, GETDATE())) "
            " OR (WednesdayBegin IS NOT NULL AND DATEPART(week, WednesdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, WednesdayBegin) = DATEPART(year, GETDATE())) "
            " OR (ThursdayBegin IS NOT NULL AND DATEPART(week, ThursdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, ThursdayBegin) = DATEPART(year, GETDATE())) "
            " OR (FridayBegin IS NOT NULL AND DATEPART(week, FridayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, FridayBegin) = DATEPART(year, GETDATE())) "
            " OR (SaturdayBegin IS NOT NULL AND DATEPART(week, SaturdayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, SaturdayBegin) = DATEPART(year, GETDATE())) "
            " OR (SundayBegin IS NOT NULL AND DATEPART(week, SundayBegin) = DATEPART(week, GETDATE()) AND DATEPART(year, SundayBegin) = DATEPART(year, GETDATE())) "
            ")");
        query->bindValue(":user_id", socketUserIDMap[socket]);
        if (!query->exec()){
            additionalForSendErrorMessage(query, "0x026");
            return std::make_pair(QVariant(), false);
        }
        else{
            if (query->next())
                return std::make_pair(query->value("CurrentTime"), true);
            else
                return std::make_pair(QVariant(), false);
        }
    }
}

std::pair<QVariant, bool> Server::getEndCurrentDateSheduleTime(QSqlQuery *query)
{
    query->prepare(
        "SELECT 1 "
        "FROM dbo.WorkScheduleEmployee "
        "WHERE UserID = :user_id "
        "AND ("
        "    (MondayEnd IS NOT NULL AND DATEPART(week, MondayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, MondayEnd) = DATEPART(year, GETDATE())) "
        " OR (TuesdayEnd IS NOT NULL AND DATEPART(week, TuesdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, TuesdayEnd) = DATEPART(year, GETDATE())) "
        " OR (WednesdayEnd IS NOT NULL AND DATEPART(week, WednesdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, WednesdayEnd) = DATEPART(year, GETDATE())) "
        " OR (ThursdayEnd IS NOT NULL AND DATEPART(week, ThursdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, ThursdayEnd) = DATEPART(year, GETDATE())) "
        " OR (FridayEnd IS NOT NULL AND DATEPART(week, FridayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, FridayEnd) = DATEPART(year, GETDATE())) "
        " OR (SaturdayEnd IS NOT NULL AND DATEPART(week, SaturdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, SaturdayEnd) = DATEPART(year, GETDATE())) "
        " OR (SundayEnd IS NOT NULL AND DATEPART(week, SundayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, SundayEnd) = DATEPART(year, GETDATE())) "
        ")");
    query->bindValue(":user_id", socketUserIDMap[socket]);
    if (!query->exec()) {
        additionalForSendErrorMessage(query, "0x010");
        return std::make_pair(QVariant(), false);
    }
    else {
        if (!query->next()) {
            return std::make_pair(QVariant(), false);
        }
        query->prepare(
            "SELECT "
            "    CASE DATEPART(WEEKDAY, GETDATE()) "
            "        WHEN 1 THEN CONVERT(time, MondayEnd) "
            "        WHEN 2 THEN CONVERT(time, TuesdayEnd) "
            "        WHEN 3 THEN CONVERT(time, WednesdayEnd) "
            "        WHEN 4 THEN CONVERT(time, ThursdayEnd) "
            "        WHEN 5 THEN CONVERT(time, FridayEnd) "
            "        WHEN 6 THEN CONVERT(time, SaturdayEnd) "
            "        WHEN 7 THEN CONVERT(time, SundayEnd) "
            "    END AS CurrentTime "
            "FROM dbo.WorkScheduleEmployee "
            "WHERE UserID = :user_id "
            "AND ("
            "    (MondayEnd IS NOT NULL AND DATEPART(week, MondayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, MondayEnd) = DATEPART(year, GETDATE())) "
            " OR (TuesdayEnd IS NOT NULL AND DATEPART(week, TuesdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, TuesdayEnd) = DATEPART(year, GETDATE())) "
            " OR (WednesdayEnd IS NOT NULL AND DATEPART(week, WednesdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, WednesdayEnd) = DATEPART(year, GETDATE())) "
            " OR (ThursdayEnd IS NOT NULL AND DATEPART(week, ThursdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, ThursdayEnd) = DATEPART(year, GETDATE())) "
            " OR (FridayEnd IS NOT NULL AND DATEPART(week, FridayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, FridayEnd) = DATEPART(year, GETDATE())) "
            " OR (SaturdayEnd IS NOT NULL AND DATEPART(week, SaturdayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, SaturdayEnd) = DATEPART(year, GETDATE())) "
            " OR (SundayEnd IS NOT NULL AND DATEPART(week, SundayEnd) = DATEPART(week, GETDATE()) AND DATEPART(year, SundayEnd) = DATEPART(year, GETDATE())) "
            ")");
        query->bindValue(":user_id", socketUserIDMap[socket]);
        if (!query->exec()){
            additionalForSendErrorMessage(query, "0x029");
            return std::make_pair(QVariant(), false);
        }
        else {
            if (query->next())
                return std::make_pair(query->value("CurrentTime"), true);
            else
                return std::make_pair(QVariant(), false);
        }
    }
}
