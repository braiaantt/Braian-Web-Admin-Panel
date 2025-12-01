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
        connectSignalsAndSlots();
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
    apiClient.setLoginEndpoint(config.endpointLogin());
    apiClient.setPortfolioEndpoint(config.endpointPortfolio());
    apiClient.setTechnologyEndpoint(config.endpointTechnology());
    apiClient.setEntityTechnologyEndpoint(config.endpointEntityTechnology());
    apiClient.setEntityImageEndpoint(config.endpointEntityImage());
    apiClient.setProjectEndpoint(config.endpointProject());
}

void MainWindow::initServices()
{
    authService = new AuthService(&apiClient, this);
    portfolioService = new PortfolioService(&apiClient, this);
    technologyService = new TechnologyService(&apiClient, this);
    entityTechService = new EntityTechService(&apiClient, this);
    projectService = new ProjectService(&apiClient, this);
    entityImageService = new EntityImageService(&apiClient, this);
}

void MainWindow::initPages()
{
    QHash<QString, QWidget*> pages;

    loginPage = new LoginPage(authService, this);
    portfolioPage = new PortfolioPage(portfolioService, technologyService, entityTechService, projectService, this);

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

void MainWindow::connectSignalsAndSlots()
{
    connect(loginPage, &LoginPage::loginComplete, this, &MainWindow::loginComplete);

    connect(portfolioPage, &PortfolioPage::projectClicked, this, &MainWindow::projectClicked);
}

//------ Private Slots ------

void MainWindow::loginComplete()
{
    QWidget* page = ui->stackedWidgetPages->findChild<QWidget*>(PageName::PORTFOLIO);
    if(!page){
        qDebug()<<"Page '"<<PageName::PORTFOLIO<<"' Not Found";
        return;
    }

    portfolioPage->loadPortfolio();
    ui->stackedWidgetPages->setCurrentWidget(page);
}

void MainWindow::projectClicked(const Project &project)
{
    ProjectPage *projectPage = new ProjectPage(technologyService, entityTechService, entityImageService, project, this);

    QWidget* stackedWidgetPage = ui->stackedWidgetPages->findChild<QWidget*>(PageName::PROJECT);
    if(stackedWidgetPage && stackedWidgetPage->layout()){
        connect(projectPage, &ProjectPage::backToPortfolio, this, &MainWindow::backToPortfolioPage);
        stackedWidgetPage->layout()->addWidget(projectPage);
        ui->stackedWidgetPages->setCurrentWidget(stackedWidgetPage);
    } else {
        projectPage->deleteLater();
    }
}

void MainWindow::backToPortfolioPage(ProjectPage *page)
{
    QWidget *stackedWidgetPage = ui->stackedWidgetPages->findChild<QWidget*>(PageName::PROJECT);
    QLayout *layout = stackedWidgetPage->layout();
    if(!layout) return;

    layout->removeWidget(page);
    page->deleteLater();

    QWidget *widgetPortfolio= ui->stackedWidgetPages->findChild<QWidget*>(PageName::PORTFOLIO);
    ui->stackedWidgetPages->setCurrentWidget(widgetPortfolio);
}
