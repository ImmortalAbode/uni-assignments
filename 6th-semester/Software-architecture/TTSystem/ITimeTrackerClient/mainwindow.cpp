#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sign_up_window(nullptr)
    , emp_menu_window(nullptr)
    , admin_menu_window(nullptr)
    , serverConn(nullptr)
    , isExplicitlyDisconnected(false)
{
    ui->setupUi(this);
    serverConn = new ServerConnection("127.0.0.1", 2323, this);

    connect(serverConn, &ServerConnection::connectionLost, this, &MainWindow::slotConnectionLost);
    connect(serverConn, &ServerConnection::connectionRestored, this, &MainWindow::slotConnectionResotred);
    connect(serverConn, &ServerConnection::authorizationResult, this, &MainWindow::slotAuthorisationSuccess);
    connect(serverConn, &ServerConnection::errorResult, this, &MainWindow::slotErrorMessage);
    connect(serverConn, &ServerConnection::checkEntryTimeDataResult, this, &MainWindow::slotCheckEntryTimeData);
    serverConn->connectToServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_logIn_clicked()
{
    serverConn->sendAuthorizationData(ui->lineEdit_login->text(), ui->lineEdit_pswd->text());
}

void MainWindow::on_pushButton_clearLogin_clicked()
{
    ui->lineEdit_login->setText("");
}

void MainWindow::on_pushButton_clearPswd_clicked()
{
     ui->lineEdit_pswd->setText("");
}

void MainWindow::on_pushButton_hide_seek_clicked()
{
    QLineEdit::EchoMode currentEchoMode = ui->lineEdit_pswd->echoMode();
    if (currentEchoMode == QLineEdit::Password) {
        ui->lineEdit_pswd->setEchoMode(QLineEdit::Normal);
        QIcon icon(":/resources/images/sign_up/eye-seek.png");
        ui->pushButton_hide_seek->setIcon(icon);
    } else {
        ui->lineEdit_pswd->setEchoMode(QLineEdit::Password);
        QIcon icon(":/resources/images/sign_up/eye-hide.png");
        ui->pushButton_hide_seek->setIcon(icon);
    }
}

void MainWindow::on_pushButton_signUp_clicked()
{
    sign_up_window = new SignUp(serverConn);
    sign_up_window->resize(size());
    sign_up_window->show();
    this->hide();
    connect(sign_up_window, &SignUp::returnToLogIn, this, &MainWindow::show);
}

void MainWindow::slotCheckEntryTimeData(bool correct)
{
    if (correct){
        if (!emp_menu_window){
            emp_menu_window = new EmployeeMainWindow(serverConn);
            emp_menu_window->show();
            this->hide();
            connect(emp_menu_window, &EmployeeMainWindow::returnToAutorization, this, &MainWindow::slotReturnFromWork);
        }
    }
    else{
        QMessageBox::information(this, "Рабочий график", "Система определила Вас как пользователя-сотрудника без рабочего графика в приложении ITimeTracker.\n\n"
                                                         "Для того, чтобы иметь возможность использования системы, Вам необходимо договориться с администратором "
                                                         "о внесении Вашего актуального рабочего графика в систему. Вы можете обратиться к любому свободному администратору "
                                                         "либо к Вашему наставнику, если он есть, для проведения данной процедуры.\n\n"
                                                         "Данное действие необходимо, чтобы учитывать Ваш личный график при расчете рабочего времени.\n"
                                                         "Желаем успехов и продуктивной работы!\n\n"
                                                         "C уважением, команда ITimeTracker.");
        serverConn->sendExitFromApp(ui->lineEdit_login->text(), ui->lineEdit_pswd->text());
        emp_menu_window = nullptr;
        admin_menu_window = nullptr;
    }
}

void MainWindow::slotAuthorisationSuccess(bool usernameSuccess, bool passwordSuccess, QString userRole)
{
    if (usernameSuccess && passwordSuccess)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Начало работы");
        msgBox.setText("Вы успешно авторизовались!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
        {
            if (userRole == "Employee")
            {
                serverConn->sendEntryTimeData(false);
            }
            else if (userRole == "Manager"){
                QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Роль в системе",
                                                                           tr("Вы хотите авторизоваться как Администратор (Да/Yes) или Сотрудник (Нет/No)?"),
                                                                           QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
                if (resBtn == QMessageBox::Yes) {
                    if (!admin_menu_window){
                        admin_menu_window = new AdminMenu(serverConn, userRole);
                        admin_menu_window->show();
                        this->hide();
                        connect(admin_menu_window, &AdminMenu::returnToAutorization, this, &MainWindow::slotReturnFromWork);
                    }
                }
                else if (resBtn == QMessageBox::No){
                    serverConn->sendEntryTimeData(true);
                }
            }
            else if (userRole == "Admin")
            {
                if (!admin_menu_window){
                    admin_menu_window = new AdminMenu(serverConn, userRole);
                    admin_menu_window->show();
                    this->hide();
                    connect(admin_menu_window, &AdminMenu::returnToAutorization, this, &MainWindow::slotReturnFromWork);
                }
            }
        }
    }
    else if (usernameSuccess && !passwordSuccess)
    {
        QMessageBox::warning(this, "Авторизация", "Пароль введён неверно!");
    }
    else
    {
        QMessageBox::warning(this, "Авторизация", "Ошибка авторизации! Указанного пользователя не существует.");
    }
}

void MainWindow::slotErrorMessage(QString err_text)
{
    QMessageBox::warning(this, "Непредвиденная ошибка", err_text);
}

void MainWindow::slotConnectionLost()
{
    if (!this->isExplicitlyDisconnected){
        QMessageBox::warning(this, "Соединение с сервером", "Сервер отключен или соединение с ним было потеряно. Приносим свои извинения.\n\n"
                                                            "Не переживайте, дождитесь восстановления соединения или сообщите администратору о проблеме.");
    }
}

void MainWindow::slotConnectionResotred()
{
    QMessageBox::warning(this, "Соединение с сервером", "Соединение с сервером было восстановлено. Спасибо за Ваше терпение.\n\n"
                                                        "Сообщите администратору, если данная ситуация повторится вновь.\n\n"
                                                        "Удачного рабочего дня!");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Закрыть приложение?",
                                                               tr("Вы уверены, что хотите закрыть приложение?\n"),
                                                               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        this->isExplicitlyDisconnected = true;
        disconnect(serverConn, &ServerConnection::connectionLost, this, &MainWindow::slotConnectionLost);
        disconnect(serverConn, &ServerConnection::connectionRestored, this, &MainWindow::slotConnectionResotred);
        disconnect(serverConn, &ServerConnection::authorizationResult, this, &MainWindow::slotAuthorisationSuccess);
        disconnect(serverConn, &ServerConnection::errorResult, this, &MainWindow::slotErrorMessage);
        disconnect(serverConn, &ServerConnection::checkEntryTimeDataResult, this, &MainWindow::slotCheckEntryTimeData);
        delete serverConn;
        serverConn = nullptr;
    }
}

void MainWindow::slotReturnFromWork()
{
    this->show();
    serverConn->sendExitFromApp(ui->lineEdit_login->text(), ui->lineEdit_pswd->text());
    ui->lineEdit_login->setText("");
    ui->lineEdit_pswd->setText("");
    emp_menu_window = nullptr;
    admin_menu_window = nullptr;
}
