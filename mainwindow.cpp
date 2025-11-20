#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "page_names.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPages();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//------ Initialization ------

void MainWindow::initPages(){

    QHash<QString, QWidget*> pages;

    loginPage = new LoginPage(this);
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
