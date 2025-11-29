#ifndef PORTFOLIOPAGE_H
#define PORTFOLIOPAGE_H

#include <QWidget>
#include "portfolioservice.h"
#include "technologyservice.h"
#include "entitytechservice.h"
#include "projectservice.h"
#include "portfolio.h"

namespace Ui {
class PortfolioPage;
}

class PortfolioPage : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioPage(PortfolioService *portfolioService, TechnologyService *technologyService,
                           EntityTechService *entityTechService, ProjectService *projectService,
                           QWidget *parent = nullptr);
    ~PortfolioPage();

    void loadPortfolio();

private slots:
    void setPortfolio(const Portfolio &portfolio);
    void setUserPhoto(const QPixmap &pixmap);
    void techIconReceipt(int techId, const QPixmap &pixmap);
    void refreshTechnologies();
    void projectCoverReceipt(int projectId, const QPixmap &pixmap);
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButtonAddTechnology_clicked();

    void on_pushButtonAddProject_clicked();

    void on_pushButtonUpdatePhoto_clicked();

    void on_pushButtonHandleTechnologies_clicked();

private:
    Ui::PortfolioPage *ui;
    PortfolioService *portfolioService;
    TechnologyService *technologyService;
    EntityTechService *entityTechService;
    ProjectService *projectService;

    //------ Initialization ------
    void connectSignalsAndSlots();

    //------ Helpers ------
    void setTechnologyWidgets(const QVector<Technology> &techs);
    void setProjectWidgets(const QVector<Project> &projects);
};

#endif // PORTFOLIOPAGE_H
