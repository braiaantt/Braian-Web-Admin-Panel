#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginpage.h"
#include "portfoliopage.h"
#include "apiclient.h"
#include "authservice.h"
#include "portfolioservice.h"
#include "technologyservice.h"
#include "entitytechservice.h"

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

private:
    Ui::MainWindow *ui;
    ApiClient apiClient;

    //------ Pages ------
    LoginPage *loginPage;
    PortfolioPage *portfolioPage;

    //------ Services ------
    AuthService *authService;
    PortfolioService *portfolioService;
    TechnologyService *technologyService;
    EntityTechService *entityTechService;

    //------ Initialization ------
    void initApiClient();
    void initServices();
    void initPages();
    void connectSignalsAndSlots();
};
#endif // MAINWINDOW_H
