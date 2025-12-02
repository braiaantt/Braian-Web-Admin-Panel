#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include "authservice.h"
#include "servicefactory.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(ServiceFactory *factory, QWidget *parent = nullptr);
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
    void init(ServiceFactory *factory);
    void connectSignalsAndSlots();
};

#endif // LOGINPAGE_H
