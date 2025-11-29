#ifndef PORTFOLIOPAGE_H
#define PORTFOLIOPAGE_H

#include <QWidget>
#include "portfolioservice.h"
#include "technologyservice.h"
#include "entitytechservice.h"
#include "portfolio.h"

namespace Ui {
class PortfolioPage;
}

class PortfolioPage : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioPage(PortfolioService *portfolioService, TechnologyService *technologyService, EntityTechService *entityTechService,
                           QWidget *parent = nullptr);
    ~PortfolioPage();

    void loadPortfolio();

private slots:
    void setPortfolio(const Portfolio &portfolio);
    void setUserPhoto(const QPixmap &pixmap);
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

    //------ Initialization ------
    void connectSignalsAndSlots();
};

#endif // PORTFOLIOPAGE_H
