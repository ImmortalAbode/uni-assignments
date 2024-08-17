#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signup.h"
#include "employeemainwindow.h"
#include "adminmenu.h"
#include "ServerConnection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SignUp *sign_up_window;
    EmployeeMainWindow *emp_menu_window;
    AdminMenu* admin_menu_window;

    ServerConnection* serverConn;
    bool isExplicitlyDisconnected;

private slots:
    void on_pushButton_logIn_clicked();
    void on_pushButton_clearPswd_clicked();
    void on_pushButton_clearLogin_clicked();
    void on_pushButton_hide_seek_clicked();
    void on_pushButton_signUp_clicked();

public slots:
    void slotCheckEntryTimeData(bool correct);
    void slotAuthorisationSuccess(bool usernameSuccess, bool passwordSuccess, QString userRole);
    void slotErrorMessage(QString err_text);
    void slotConnectionLost();
    void slotConnectionResotred();
    void slotReturnFromWork();

protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
