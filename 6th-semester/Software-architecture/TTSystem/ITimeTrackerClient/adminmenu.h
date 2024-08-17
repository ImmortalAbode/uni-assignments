#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QMainWindow>
#include "ServerConnection.h"
#include <QTimer>

namespace Ui {
class AdminMenu;
}

class AdminMenu : public QMainWindow
{
    Q_OBJECT

private:
    Ui::AdminMenu *ui;
    ServerConnection* serverConn;
    QString type_admin;

public:
    explicit AdminMenu(ServerConnection* serverConn, QString type_admin, QWidget *parent = nullptr);
    ~AdminMenu();

protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_action_common_statistic_triggered();
    void on_action_report_triggered();
    void on_action_team_triggered();
    void on_action_add_man_triggered();
    void on_action_remove_change_man_triggered();
    void on_action_add_emp_triggered();
    void on_action_remove_change_emp_triggered();
    void on_action_grafs_triggered();
    void on_action_projects_tasks_triggered();
    void on_action_add_project_triggered();
    void on_action_remove_change_project_triggered();
    void on_action_add_task_triggered();
    void on_action_remove_change_task_triggered();
    void on_action_users_triggered();
    void on_action_unprocessed_query_triggered();
    void on_action_close_query_triggered();
    void on_action_exit_triggered();
    void on_pushButton_addNewEmployee_clicked();
    void on_pushButton_removeEmployee_clicked();
    void on_pushButton_changeEmployee_clicked();
    void on_pushButton_closeRequest_clicked();
    void on_pushButton_add_man_clicked();
    void on_pushButton_remove_man_clicked();
    void on_pushButton_change_man_clicked();
    void on_pushButton_add_project_clicked();
    void on_pushButton_remove_project_clicked();
    void on_pushButton_change_project_clicked();
    void on_pushButton_add_task_clicked();
    void on_pushButton_change_task_clicked();
    void on_pushButton_remove_task_clicked();
    void on_pushButton_project_work_clicked();
    void on_pushButton_task_work_clicked();
    void on_pushButton_newProjectMan_clicked();
    void on_pushButton_newEmployeeForTask_clicked();

    void on_pushButton_hideCredentials_clicked();

    void on_pushButton_addGraf_clicked();

    void on_pushButton_changeGraf_clicked();

    void on_pushButton_remGraf_clicked();

    void on_pushButton_addWeekend_clicked();

    void on_pushButton_remWeekend_clicked();

    void on_pushButton_changeWeekend_clicked();

    //void on_pushButton_getInfo_clicked();

    void on_pushButton_getInfo_clicked();

    void on_pushButton_remAnomaly_clicked();

    void on_pushButton_createReport_clicked();

public slots:
    void slotAdminSaveReportResult(QString report);
    void slotAdminRemoveAnomaly(bool access);
    void slotGetAdminAnomalyDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> anomalies_data);
    void slotAdminUpdateAnomalyTable(int selected_index);
    void slotAdminEmployeeTableForAnomalyResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void slotGetAdminRemoveWeekendResult(bool access);
    void slotGetAdminWorkWithWeekendResult(QString action, bool access);
    void slotGetAdminRemoveGrafResult(bool access);
    void slotGetAdminWorkWithGrafResult(QString action, bool access);
    void slotGetAdminEmployeeWeekendsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> weekends_data);
    void slotGetAdminEmployeeGrafsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> grafs_data);
    void slotGetAdminEmployeeDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void slotGetAdminCompleteProjectTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks_data);
    void slotUpdateProjectTasksTable(int selected_index);
    void slotGetAdminCompleteProjectsResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_projs_data);
    void slotGetAdminCredentialsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> credentials_data);
    void slotEmployeeTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void slotAdminTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void slotAddedEmployeeSuccess(QMap<QString, bool> reg_success);
    void slotRemovedEmployeeSuccess(bool removing_success);
    void slotChangedEmployeeResult(QMap<QString, bool> change_employee_success);
    void slotGetEmployeeRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_requests_data);
    void slotGetRequestStatuses(QStringList requestStatuses);
    void slotAdminTableDataResult_remove(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void slotRemovedAdminSuccess(bool removing_success);
    void slotAddedAdminSuccess(bool adding_success);
    void slotChangedAdminResult(QMap<QString, bool> change_employee_success);
    void slotAllClosedRequests(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> users_data);
    void slotAllProjectsAndTasks(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void slotAddProjectsDataRequest(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void slotProjectsDataForChange(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> projects_data);
    void slotRemoveChangeProjectCompleted();
    void slotTaskTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> tasks_data);
    void slotEmployeeForTaskTableDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emps_data);
    void slotRemoveChangeTaskCompleted();
    void slotCloseRequestCompleted();
    void slotAddProjectCompleted();
    void slotAddTaskCompleted(bool adding_success);
    void slotTeamDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> team_data);
    void slotOnlineDataTableResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> online_data);

signals:
    void returnToAutorization();
};
#endif // ADMINMENU_H
