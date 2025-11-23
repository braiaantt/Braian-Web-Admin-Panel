#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include "authservice.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(AuthService *authService, QWidget *parent = nullptr);
    ~LoginPage();

signals:
    void loginComplete();

private slots:
    //------ UI Slots ------
    void on_pushButtonLogin_clicked();

    //------ Private Slots -----
    void loginSuccess();
    void error(const QString &error);

private:
    Ui::LoginPage *ui;
    AuthService *authService;

    //------ Initialization ------
    void connectSignalsAndSlots();
};

#endif // LOGINPAGE_H
