#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginpage.h"
#include "portfoliopage.h"
#include "projectpage.h"
#include "servicefactory.h"

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

private slots:
    void loginComplete();
    void projectClicked(const Project &project);
    void backToPortfolioPage(ProjectPage *page);

private:
    Ui::MainWindow *ui;
    ServiceFactory serviceFactory;

    //------ Pages ------
    LoginPage *loginPage;
    PortfolioPage *portfolioPage;

    //------ Initialization ------
    void init();
    void initPages();
    void connectSignalsAndSlots();
};
#endif // MAINWINDOW_H
