#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include <QCloseEvent>

SignUp::SignUp(ServerConnection *serverConn, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
    this->serverConn = serverConn;
    connect(this->serverConn, &ServerConnection::registrationResult, this, &SignUp::slotRegistrationSuccess);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::slotRegistrationSuccess(QMap<QString, bool> reg_success)
{

    if (!reg_success["FirstName"] || !reg_success["LastName"] || !reg_success["MiddleName"] || !reg_success["JobTitle"])
    {
        QMessageBox::warning(this, "Регистрация", "Ошибка! Поля 'Имя', 'Фамилия', 'Отчество', 'Должность' не должны содержать символов, отличных от кириллицы."
                                                  "Поле 'Отчество' может быть пустым.");
    }
    else if (!reg_success["PersonnelNumber"])
    {
        QMessageBox::warning(this, "Регистрация", "Ошибка! Ваш табельный номер должен быть уникальным и представлять собой целое положительное число."
                                                  " Проверьте корректность ввода или обратитесь к администратору.");
    }
    else if (!reg_success["Login"])
    {
        QMessageBox::warning(this, "Регистрация", "Ошибка! Ваш логин должен быть уникальным. Придумайте новый логин и попробуйте заново.");
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Регистрация");
        msgBox.setText("Вы успешно зарегистрировались! Не забудьте записать свои логин и пароль или обратитесь к администратору "
                       " в случае их потери.\n\nАвторизуйтесь для дальнейшей работы в системе.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
        {
            ui->pushButton_BackToLogIn->click();
        }
    }
}

void SignUp::on_pushButton_BackToLogIn_clicked()
{
    emit returnToLogIn();
    disconnect(serverConn, &ServerConnection::registrationResult, this, &SignUp::slotRegistrationSuccess);
    this->close();
}

void SignUp::on_pushButton_logIn_clicked()
{
    QLineEdit* lineEdits[] = {
        ui->lineEdit_FirstName,
        ui->lineEdit_LastName,
        ui->lineEdit_MiddleName,
        ui->lineEdit_JobTitle,
        ui->lineEdit_PersonnelNimber,
        ui->lineEdit_ContactInformation,
        ui->lineEdit_AdditionalInfo,
        ui->lineEdit_login,
        ui->lineEdit_pswd
    };

    QStringList reg_data;
    bool allFieldsFilled = true;

    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text().isEmpty() && lineEdit != lineEdits[2] && lineEdit != lineEdits[6]) {
            allFieldsFilled = false;
            break;
        }
    }

    if (allFieldsFilled) {
        for (QLineEdit* lineEdit : lineEdits) {
            reg_data << lineEdit->text();
        }
        serverConn->sendRegistrationData(reg_data);
    } else {
        QMessageBox::warning(this, "Регистрация", "Ошибка! Заполните все выделенные цветом поля, необходимые для регистрации.");
    }
}

void SignUp::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous()) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Закрыть приложение?",
                                                                   tr("Вы уверены, что хотите закрыть приложение?\n"),
                                                                   QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
            return;
        } else {
            disconnect(serverConn, &ServerConnection::connectionLost, nullptr, nullptr);
            disconnect(serverConn, &ServerConnection::connectionRestored, nullptr, nullptr);
            delete serverConn;
        }
    }
    event->accept();
}
