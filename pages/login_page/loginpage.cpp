#include "loginpage.h"
#include "ui_loginpage.h"
#include "utils.h"

LoginPage::LoginPage(ServiceFactory *factory, QWidget *parent)
    :
    ui(new Ui::LoginPage),
    QWidget(parent)
{
    ui->setupUi(this);
    init(factory);
}

LoginPage::~LoginPage()
{
    delete ui;
}

//------ Initialization ------

void LoginPage::init(ServiceFactory *factory)
{
    authService = factory->makeAuthService(this);
    connectSignalsAndSlots();
}

void LoginPage::connectSignalsAndSlots()
{
    connect(authService, &AuthService::loginSuccess, this, &LoginPage::loginSuccess);
    connect(authService, &AuthService::error, this, &LoginPage::error);
}


//------ UI Slots ------

void LoginPage::on_pushButtonLogin_clicked()
{
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();

    authService->login(email, password);
}

//------ Private Slots ------

void LoginPage::loginSuccess()
{
    ui->lineEditEmail->setText("");
    ui->lineEditPassword->setText("");
    emit loginComplete();
}

void LoginPage::error(const QString &error)
{
    Utils::showWarning(this, error);
}
