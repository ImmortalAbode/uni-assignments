#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <ServerConnection.h>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(ServerConnection *serverConn, QWidget *parent = nullptr);
    ~SignUp();

private:
    Ui::SignUp *ui;
    ServerConnection* serverConn;

public slots:
    void slotRegistrationSuccess(QMap<QString, bool> reg_success);

private slots:
    void on_pushButton_BackToLogIn_clicked();
    void on_pushButton_logIn_clicked();

signals:
    void returnToLogIn();

protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // SIGNUP_H
