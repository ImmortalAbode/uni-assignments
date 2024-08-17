#ifndef EMPLOYEEMAINWINDOW_H
#define EMPLOYEEMAINWINDOW_H

#include <QMainWindow>
#include <ServerConnection.h>
#include <windows.h>

namespace Ui {
class EmployeeMainWindow;
}

class EmployeeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeMainWindow(ServerConnection* serverConn, QWidget *parent = nullptr);
    ~EmployeeMainWindow();

private:
    Ui::EmployeeMainWindow *ui;
    ServerConnection* serverConn;
    QList<QStringList> projects, proj_tasks;
    bool allowWorkControl;
    QString blockingLocation;
    // Статический метод для обработки хука клавиатуры
    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

private slots:
    void on_action_common_statistic_triggered();
    void on_action_reg_time_triggered();
    void on_action_work_graf_triggered();
    void on_action_exception_triggered();
    void on_action_work_triggered();
    void on_action_sent_queries_triggered();
    void on_action_got_queries_triggered();
    void on_action_users_triggered();
    void on_action_exit_triggered();

    void on_pushButton_send_clicked();

    void on_pushButton_updateProjData_clicked();

    void on_pushButton_BeginTask_clicked();

    void on_pushButton_EndTask_clicked();

    void on_pushButton_readyTask_clicked();

    void on_pushButton_saveEmpNote_clicked();

    void on_pushButton_updateEmpRequestsData_clicked();

    void on_pushButton_beginLunchBreak_clicked();

    void on_pushButton_finishLunchBreak_clicked();

    void on_pushButton_beginMeeting_clicked();

    void on_pushButton_finishMeeting_clicked();

    void on_pushButton_beginAbsenceDueToWork_clicked();

    void on_pushButton_finishAbsenceDueToWork_clicked();

    void on_pushButton_beginPersonalNeeded_clicked();

    void on_pushButton_finishPersonalNeeded_clicked();

    void on_pushButton_updateEmpTableData_clicked();

    void on_pushButton_hideCredentials_clicked();

public slots:
    void slotGetEmployeeCreditalsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> creditals_data);
    void slotGetEmployeeCompleteTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> complete_tasks);
    void slotGetEmployeeUnfinishedTasksResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> unfinished_tasks);
    void slotGetEmployeeTimeData(QStringList time_data);
    void slotGetEmployeeWorkGrafResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> work_graf_data);
    void slotGetEmployeeTableTimeAnomaliesResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> time_anomalies_data);
    void slotGetRequestCategories(QStringList categories);
    void slotGetReadyTaskRequestResult(bool correct);
    void slotGetEmployeeProjectsResult(QList<QStringList> projects);
    void slotGetEmployeeProjectTasksResult(QList<QStringList> proj_tasks);
    void slotGetEmployeeTaskNotesResult(QStringList emp_notes);
    void slotGetEmployeeSaveTaskNotesResult();
    void slotGetEmployeeRequestsDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> emp_requests_data);
    void slotGetEmployeeTableEmployeesDataResult(QStringList headerLabels, int columnCount, int rowCount, QList<QStringList> employees_data);
    void slotReadyTakeIntoMainTime(QString location);
    //Вспомогательные слоты.
    void slotUpdateProjectDescription(int selected_index);
    void slotUpdateProjectTaskDescription(int selected_index);
    void slotUpdateEmployeeRequestsData(int selected_index);

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void returnToAutorization();
};
#endif // EMPLOYEEMAINWINDOW_H
