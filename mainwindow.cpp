#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "page_names.h"
#include "utils.h"
#include "configmanager.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(50, this, [this]{
        initApiClient();
        initServices();
        initPages();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//------ Initialization ------

void MainWindow::initApiClient()
{
    ConfigManager config;
    if(!config.load()){
        Utils::showWarning(this, "Error al leer archivo de configuracion!");
        return;
    }

    apiClient.setHostName(config.host());
    apiClient.setLoginRoute(config.routeLogin());
}

void MainWindow::initServices()
{
    authService = new AuthService(&apiClient);
}

void MainWindow::initPages()
{
    QHash<QString, QWidget*> pages;

    loginPage = new LoginPage(authService, this);
    portfolioPage = new PortfolioPage(this);

    pages.insert(PageName::LOGIN, loginPage);
    pages.insert(PageName::PORTFOLIO, portfolioPage);

    for(auto it = pages.cbegin(); it != pages.cend(); ++it){

        QWidget* stackedWidgetPage = ui->stackedWidgetPages->findChild<QWidget*>(it.key());
        if(stackedWidgetPage && stackedWidgetPage->layout()){
            stackedWidgetPage->layout()->addWidget(it.value());
        } else {
            qDebug()<<"Null: "<<it.key()<<" or layout";
        }
    }
}
