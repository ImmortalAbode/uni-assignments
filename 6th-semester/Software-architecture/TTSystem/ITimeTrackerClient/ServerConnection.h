#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <QObject>
#include <QTcpSocket>
#include <QTimer>

//Идентификация получаемых и отправляемых сообщений.
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

class ServerConnection : public QObject
{
    Q_OBJECT

public:
    explicit ServerConnection(QString host, quint16 port, QObject* parent = nullptr);
    ~ServerConnection();
    void connectToServer();
    //Отправка данных на сервер.
    /*КЛИЕНТ*/
    void sendAuthorizationData(QString user_login, QString user_pswd);
    void sendRegistrationData(QStringList reg_data);
    /*СОТРУДНИК*/
    void getEmployeeCreditalsData();
    void getEmployeeCompleteTasks();
    void getEmployeeUnfinishedTasks();
    void getEmployeeTimeData();
    void getEmployeeWorkGraf();
    void getEmployeeTableTimeAnomalies();
    void sendEntryTimeData(bool manager_flag);
    void sendMainTimeData(QString location);
    void sendBeginSubmainTimeData(QString action);
    void sendEndSubmainTimeData(QString action);
    void getRequestCategories();
    void sendEmployeeRequest(QString type_request, QString text);
    void getEmployeeProjects();
    void getEmployeeProjectTasks(QString proj_name);
    void sendEmployeeReadyTaskRequest(QString task_data);
    void getEmployeeTaskNotes(QString proj_task_name);
    void sendEmployeeTaskNotesForSave(QStringList new_task_emp_notes, QString task_name);
    void getEmployeeRequestsData(QString category_name);
    void getEmployeeTableEmployeesData();
    /*АДМИН*/
    void sendAdminSaveReport(QString EmployeeID, QString dateStart, QString dateFinish);
    void sendAdminRemoveAnomaly(QString anomaly_id);
    void sendAdminAnomalyData(QString emp_id);
    void getAdminEmployeeTableForAnomaly(QString type_admin);
    void sendAdminRemoveWeekend(QString weekend_id);
    void sendAdminWorkWithWeekend(QString action, QString object_id, QString weekend_begin, QString weekend_end, QString note);
    void sendAdminRemoveGraf(QString graf_id);
    void sendAdminWorkWithGraf(QString action, QString object_id, QStringList workSchedule);
    void getAdminEmployeeWeekends(QString type_admin);
    void getAdminEmployeeGrafs(QString type_admin);
    void getAdminEmployeeData(QString type_admin);
    void getAdminCompleteProjTasks(QString projID);
    void getAdminCompleteProjects(QString type_admin);
    void getAdminCredentialsData();
    void getEmployeeDataTable(QString type_admin);
    void sendRemovedUserID(QString user_id);
    void sendChangedEmployeeData(QString user_id, QStringList change_data);
    void getEmployeeRequestsDataTable(QString type_admin);
    void getRequestStatuses();
    void sendCloseRequest(int ID_request, QString requestStatus, QString text);
    void getClosedRequestsTableData();
    void getTasksDataTable(QString type_admin);
    void getEmployeeDataTableForTask(QString type_admin);
    void sendAddTaskData(QStringList add_task_data);
    void sendChangedTaskData(QString changedTaskID, QString newTaskName, QString newTaskDescription);
    void sendRemovedTaskID(QString removingTaskID);
    void sendWorkedTaskID(QString workingTaskID);
    void sendNewEmployeeForTaskData(QString new_emp_id, QString task_id);
    void getTeam(QString type_admin);
    void getAllOnlineUsers();
    /*ГЛАВНЫЙ АДМИН*/
    void sendAddAdmin(QString UpEmployeeID, QString JobTitleEmployee);
    void getAdminTableData();
    void sendRemovedAdminID(QString user_id);
    void sendChangedAdminData(QString user_id, QStringList change_data);
    void getAllProjectsAndTasksTableData(QString type_admin);
    void getAddProjectTableData();
    void sendNewProjectData(QString projectManagerID, QString projectName, QString projectDescription);
    void getProjectsDataForChange();
    void sendRemovedProjectID(QString removingProjectID);
    void sendChangedProjectData(QString changedProjectID, QString newProjectName, QString newProjectDescription);
    void sendWorkedProjectID(QString workingProjectID);
    void sendNewProjectManagerForProjectData(QString new_admin_id, QString project_id);
    //Оповещение сервера о выходе из системы.
    void sendExitFromApp(QString user_login, QString user_pswd);

private:
    QTcpSocket* socket;
    QByteArray Data;
    QTimer* reconnectTimer;
    QString host;
    quint16 port;
    bool isServerDown;
    quint16 nextBlockSize;

signals:
    //Сигналы получения данных с сервера.
    /*КЛИЕНТ*/
    void authorizationResult(bool usernameSuccess, bool passwordSuccess, QString userRole);
    void registrationResult(QMap<QString, bool> reg_success);
    void errorResult(QString error_text);
    /*СОТРУДНИК*/
    void getEmployeeCreditalsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> creditals_data);
    void getEmployeeCompleteTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks);
    void getEmployeeUnfinishedTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> unfinished_tasks);
    void getEmployeeTimeDataResult(QStringList time_data);
    void getEmployeeWorkGrafResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> work_graf_data);
    void getEmployeeTableTimeAnomaliesResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> time_anomalies_data);
    void checkEntryTimeDataResult(bool correct);
    void readyTakeIntoMainTime(QString location);
    void getRequestCategoriesResult(QStringList categories);
    void getEmployeeProjectsResult(QList<QStringList> projects);
    void getEmployeeProjectTasksResult(QList<QStringList> projectTasks);
    void getEmployeeReadyTaskRequestResult(bool correct);
    void getEmployeeTaskNotesResult(QStringList emp_notes);
    void getEmployeeSaveTaskNotesResult();
    void getEmployeeRequestsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_requests_data);
    void getEmployeeTableEmployeesDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    /*АДМИН И ГЛАВНЫЙ АДМИН*/
    void getAdminSaveReportResult(QString report);
    void getAdminRemoveAnomalyResult(bool access);
    void getAdminAnomalyDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> anomalies_data);
    void getAdminEmployeeTableForAnomalyResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void getAdminRemoveWeekendResult(bool access);
    void getAdminWorkWithWeekendResult(QString action, bool access);
    void getAdminRemoveGrafResult(bool access);
    void getAdminWorkWithGrafResult(QString action, bool access);
    void getAdminEmployeeWeekendsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> weekends_data);
    void getAdminEmployeeGrafsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> grafs_data);
    void getAdminEmployeeDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void getAdminCompleteProjectTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks_data);
    void getAdminCompleteProjectsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_projs_data);
    void getAdminCredentialsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> credentials_data);
    void employeeTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void removedEmployeeResult(bool removing_success);
    void changedEmployeeResult(QMap<QString, bool> reg_success);
    void employeeRequestsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void requestStatusesResult(QStringList requestObjectStatuses);
    void adminTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void removedAdminResult(bool removing_success);
    void addedAdminResult(bool adding_success);
    void changedAdminResult(QMap<QString, bool> reg_success);
    void allClosedRequestsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void projectsAndTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void addProjectDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void changeProjectDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void removedChangedProjectSuccess();
    void taskDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> tasks_data);
    void empsForTaskDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void removedChangedTaskSuccess();
    void adminCloseRequestSuccess();
    void addProjectSuccess();
    void addTaskSuccess(bool adding_success);
    void teamDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> team_data);
    void onlineDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> online_data);
    //Сигналы для обработки связи с сервером.
    void connectionLost();
    void connectionRestored();

private slots:
    void slotReadyRead();
    void slotDisconnected();
    void slotConnected();
    void slotAttemptReconnect();
};
#endif // SERVERCONNECTION_H
