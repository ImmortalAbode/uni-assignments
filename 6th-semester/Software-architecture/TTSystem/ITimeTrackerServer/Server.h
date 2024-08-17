#ifndef SERVER_H_
#define SERVER_H_

#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qvector.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

enum class MessageType
{
    /*СЕРВЕР*/
    ERROR,
    AUTHORISATION,
    REGISTRATION,
    EXIT,
    /*СОТРУДНИК*/
    EMPLOYEE_CREDITALS_DATA,
    EMPLOYEE_COMPLETE_TASKS,
    EMPLOYEE_UNFINISHED_TASKS,
    EMPLOYEE_GET_TIME_DATA,
    EMPLOYEE_GET_WORK_GRAF,
    EMPLOYEE_GET_TIME_ANOMALIES,
    TAKE_INTO_ENTRY_TIME,
    TAKE_INTO_MAIN_TIME,
    TAKE_INTO_BEGIN_SUBMAIN_TIME,
    TAKE_INTO_END_SUBMAIN_TIME,
    REQUEST_CATEGORIES,
    EMPLOYEE_REQUEST,
    EMPLOYEE_PROJECTS,
    EMPLOYEE_PROJECT_TASKS,
    EMPLOYEE_READYTASK_REQUEST,
    EMPLOYEE_NOTES,
    EMPLOYEE_SAVE_NOTES,
    EMPLOYEE_REQUESTS_DATA,
    EMPLOYEE_TABLE_EMPLOYEES_DATA,
    /*АДМИН*/
    ADMIN_SAVE_REPORT,
    ADMIN_REMOVE_ANOMALY,
    ADMIN_ANOMALY_DATA,
    ADMIN_EMPLOYEE_ANOMALY_DATA,
    ADMIN_REMOVE_WEEKEND,
    ADMIN_WORK_WITH_WEEKEND,
    ADMIN_REMOVE_GRAF,
    ADMIN_WORK_WITH_GRAF,
    ADMIN_GET_EMPLOYEE_WEEKENDS,
    ADMIN_GET_EMPLOYEE_GRAFS,
    ADMIN_GET_EMPLOYEE_DATA,
    ADMIN_COMPLETE_TASKS,
    ADMIN_COMPLETE_PROJECTS,
    ADMIN_CREDENTIALS_DATA,
    ADMIN_EMPLOYEE_DATA_TABLE,
    ADMIN_REMOVE_EMPLOYEE,
    ADMIN_CHANGE_EMPLOYEE_DATA,
    ADMIN_GET_EMPLOYEE_REQUESTS,
    ADMIN_GET_EMPLOYEE_REQUEST_STATUSES,
    ADMIN_CLOSE_EMPLOYEE_REQUEST,
    ADMIN_ALL_CLOSE_REQUESTS_DATA_TABLE,
    ADMIN_GET_PROJECT_TASK_DATA_TABLE,
    ADMIN_GET_TASK_DATA_TABLE,
    ADMIN_GET_TASK_EMPLOYEE_DATA_TABLE,
    ADMIN_ADD_TASK,
    ADMIN_CHANGE_TASK,
    ADMIN_REMOVE_CHANGE_TASK_COMPLETE,
    ADMIN_REMOVE_TASK,
    ADMIN_WORK_TASK,
    ADMIN_CLOSE_REQUEST_COMPLETE,
    ADMIN_ADD_TASK_SUCCESS,
    ADMIN_EMPLOYEE_FOR_TASK,
    ADMIN_TEAM,
    ADMIN_TEAM_DATA_TABLE,
    ADMIN_ONLINE_USERS,
    ADMIN_ONLINE_DATA_TABLE,
    /*ГЛАВНЫЙ АДМИН*/
    MAINADMIN_ADD_ADMIN,
    MAINADMIN_ADMIN_DATA_TABLE,
    MAINADMIN_REMOVE_ADMIN,
    MAINADMIN_CHANGE_ADMIN_DATA,
    MAINADMIN_PROJECT_DATA_TABLE,
    MAINADMIN_ADD_PROJECT,
    MAINADMIN_CHANGE_PROJECT_DATA_TABLE,
    MAINADMIN_REMOVE_PROJECT,
    MAINADMIN_CHANGE_PROJECT,
    MAINADMIN_REMOVE_CHANGE_PROJECT_COMPLETE,
    MAINADMIN_WORK_PROJECT,
    MAINADMIN_ADD_PROJECT_SUCCESS,
    MAINADMIN_PROJECT_MANAGER_FOR_PROJECT,
};

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server();
    QTcpSocket* socket;

private:
    QVector <QTcpSocket*> Sockets;
    QHash<QTcpSocket*, int> socketUserIDMap;
    QByteArray Data;
    QSqlDatabase db;
    QSqlQuery *query;
    qintptr socketDescriptor;
    bool manager_flag = false;
    //Основные фунции для отправки результатов обращений клиенту.
    /*КЛИЕНТ*/
    void sendErrorMessage(QString err_text);
    void sendAuthorizationResult(bool loginSuccess, bool pswdSuccess, QString userRole);
    void sendRegistrationResult(QMap<QString, bool> reg_success);
    /*СОТРУДНИК*/
    void sendEmployeeCreditalsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> creditals_data);
    void sendEmployeeCompleteTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks);
    void sendEmployeeUnfinishedTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> unfinished_tasks);
    void sendEmployeeTimeData(QStringList time_data);
    void sendEmployeeTableWorkGrafResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> work_graf_data);
    void sendEmployeeTableTimeAnomaliesResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> time_anomalies_data);
    void sendCheckEntryTimeDataResult(bool correct);
    void sendTakeIntoMainTimeResult(QString location);
    void sendRequestCategoriesResult(QStringList categories);
    void sendEmployeeProjectsResult(QList<QStringList> projects);
    void sendEmployeeProjectTasksResult(QList<QStringList> project_tasks);
    void sendEmployeeReadyTaskRequestResult(bool correct);
    void sendEmployeeTaskNotesResult(QStringList task_emp_notes);
    void sendEmployeeSaveTaskNotesResult();
    void sendEmployeeRequestsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_requests_data);
    void sendEmployeeTableEmployeesDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    /*АДМИН и ГЛАВНЫЙ АДМИН*/
    void sendAdminSaveReportResult(QString report);
    void sendAdminRemoveAnomalyDataResult(bool access);
    void sendAdminAnomalyDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> anomalies_data);
    void sendAdminEmployeeAnomalyDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void sendAdminRemoveWeekendResult(bool access);
    void sendAdminWorkWithWeekendResult(QString action, bool access);
    void sendAdminRemoveGrafResult(bool access);
    void sendAdminWorkWithGrafResult(QString action, bool access);
    void sendAdminGetEmployeeWeekendsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> weekends_data);
    void sendAdminGetEmployeeGrafsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> grafs_data);
    void sendAdminEmployeeDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void sendAdminCompleteProjectTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks_data);
    void sendAdminCompleteProjectsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_projs_data);
    void sendAdminCredentialsData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> credentials_data);
    void sendUsersTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void sendRemovedUserResult(bool removing_success);
    void sendChangedEmployeeResult(QMap<QString, bool> change_employee_success);
    void sendEmployeeRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void sendRequestObjectStatuses(QStringList categories);
    void sendUsersManagerTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void sendRemovedManagerResult(bool removing_success);
    void sendAddedManResult(bool adding_success);
    void sendChangedManagerResult(QMap<QString, bool> change_employee_success);
    void sendAllClosedRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void sendAllProjectsTasks(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void sendAddProjectDataRequest(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void sendProjectsDataForChange(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void sendRemoveChangeProjectCompleted();
    void sendTasksTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> tasks_data);
    void sendEmployeeForTasksTableData(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void sendRemoveChangeTaskCompleted();
    void sendCloseRequestCompleted();
    void sendAddProjectCompleted();
    void sendAddTaskCompleted(bool adding_Success);
    void sendTeamDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> team_data);
    void sendOnlineDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> online_data);
    //Вспомогательные функции для обработки получаемых данных.
    bool isCyrillic(const QString& str);
    bool isNumeric(const QString& str);
    bool isUniqueLogin(const QString& login, QSqlQuery* query);
    bool isUniquePersonnelNumber(const int& personnelNumber, QSqlQuery* query);
    int getUserID(QSqlQuery* query, QString& user_login);
    QString getUserLogin(QSqlQuery* query, QString& user_id);
    int getEmployeePersonnelNumber(QSqlQuery* query, QString& employee_id);
    QString getUserRole(QSqlQuery* query, QString& user_id);
    bool isUserOffline(QSqlQuery* query, QString& user_id);
    QString getProjTaskID(QSqlQuery* query, QString& task_name);
    std::pair<QVariant, bool> getBeginCurrentDateSheduleTime(QSqlQuery* query);
    std::pair<QVariant, bool> getEndCurrentDateSheduleTime(QSqlQuery* query);
    bool fetchEmployeeInfo(QSqlQuery* query, const QString &employee_id, QString &report, const QDate &dateStart, const QDate &dateFinish);
    bool fetchCompletedProjectTasks(QSqlQuery* query, const QString &employee_id, QString &report);
    bool fetchWorkTimeAnomalies(QSqlQuery* query, const QString &employee_id, const QDate &dateStart, const QDate &dateFinish, QString &report);
    bool fetchExceptionalSituations(QSqlQuery* query, const QString &employee_id, const QDate &dateStart, const QDate &dateFinish, QString &report);
    bool fetchWorkTimeRecords(QSqlQuery* query, const QString &employee_id, const QDate &dateStart, const QDate &dateFinish, QString &report);
    //Отделенные функции для упрощения slotReadyRead().
    /*КЛИЕНТ*/
    void additionalForAuthorizationResult(QDataStream& in);
    void additionalForRegistrationResult(QDataStream& in);
    void additionalForExitFromApp(QDataStream& in);
    void additionalForSendErrorMessage(QSqlQuery *query, QString error_code);
    /*СОТРУДНИК*/
    void additionalForSendEmployeeCreditalsData();
    void additionalForSendEmployeeCompleteTasks();
    void additionalForSendEmployeeUnfinishedTasks();
    void additionalForSendEmployeeTimeData();
    void additionalForSendEmployeeTableWorkGrafResult();
    void additionalForSendEmployeeTableTimeAnomaliesResult();
    void additionalForTakeIntoEntryTime();
    void additionalForTakeIntoMainTime(QDataStream& in);
    void additionalForTakeIntoBeginSubmainTime(QDataStream& in);
    void additionalForTakeIntoEndSubmainTime(QDataStream& in);
    void additionalForSendRequestCategoriesResult();
    void additionalForEmployeeRequestResult(QDataStream& in);
    void additionalForSendEmployeeProjectsResult();
    void additionalForSendEmployeeProjectTasksResult(QDataStream& in);
    void additionalForSendEmployeeReadyTaskRequestResult(QDataStream& in);
    void additionalForSendEmployeeTaskNotesResult(QDataStream& in);
    void additionalForSendEmployeeSaveTaskNotesResult(QDataStream& in);
    void additionalForSendEmployeeRequestsDataResult(QDataStream& in);
    void additionalForSendEmployeeTableEmployeesDataResult();
    /*АДМИН*/
    void additionalForSendAdminSaveReportResult(QDataStream& in);
    void additionalForSendAdminRemoveAnomalyResult(QDataStream& in);
    void additionalForSendAdminAnomalyDataResult(QDataStream& in);
    void additionalForSendAdminEmployeeAnomalyDataResult(QDataStream& in);
    void additionalForSendAdminRemoveWeekendResult(QDataStream& in);
    void additionalForSendAdminWorkWithWeekendResult(QDataStream& in);
    void additionalForSendAdminRemoveGrafResult(QDataStream& in);
    void additionalForSendAdminWorkWithGrafResult(QDataStream& in);
    void additionalForSendAdminGetEmployeeWeekends(QDataStream& in);
    void additionalForSendAdminGetEmployeeGrafs(QDataStream& in);
    void additionalForSendAdminGetEmployeeData(QDataStream& in);
    void additionalForSendAdminCompleteProjectTasksResult(QDataStream& in);
    void additionalForSendAdminCompleteProjectsResult(QDataStream& in);
    void additionalForSendAdminCredentialsData();
    void additionalForGetEmployeeTableData(QDataStream& in);
    void additionalForRemovedEmployeeResult(QDataStream& in);
    void additionalForChangeEmployeeResult(QDataStream& in);
    void additionalForGetEmployeeRequestsTableData(QDataStream& in);
    void additionalForGetRequestStatusesTableData();
    void additionalForCloseRequestResult(QDataStream& in);
    void additionalForGetTaskDataTable(QDataStream& in);
    void additionalForGetEmployeeForTaskDataTable(QDataStream& in);
    void additionalForAddTask(QDataStream& in);
    void additionalForChangedTaskResult(QDataStream& in);
    void additionalForRemovedTaskResult(QDataStream& in);
    void additionalForWorkedTaskResult(QDataStream& in);
    void additionalForEmployeeForTaskResult(QDataStream& in);
    void additionalForTeamTableData(QDataStream& in);
    void additionalForOnlineTableData();
    /*ГЛАВНЫЙ АДМИН*/
    void additionalForAddAdminResult(QDataStream &in);
    void additionalForGetAdminTableData();
    void additionalForRemovedAdminResult(QDataStream& in);
    void additionalForChangeAdminResult(QDataStream& in);
    void additionalForAllClosedRequestsTableData();
    void additionalForAllProjectsAndTasksTableData(QDataStream& in);
    void additionalForAddProjectTableData();
    void additionalForAddNewProjectResult(QDataStream& in);
    void additionalForProjectForChangeTableData();
    void additionalForRemovedProjectResult(QDataStream& in);
    void additionalForChangedProjectResult(QDataStream& in);
    void additionalForWorkedProjectResult(QDataStream& in);
    void additionalForProjectManagerForProjectResult(QDataStream& in);
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotClientDisconnected();
    void slotReadyRead();

};

#endif /*SERVER_H*/
