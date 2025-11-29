#include "portfoliopage.h"
#include "ui_portfoliopage.h"
#include "createproject.h"
#include "portfolioproject.h"
#include "utils.h"
#include "technologyhandler.h"
#include "technologyrelation.h"

PortfolioPage::PortfolioPage(PortfolioService *portfolioService, TechnologyService* technologyService, EntityTechService *entityTechService, QWidget *parent)
    : QWidget(parent), portfolioService(portfolioService), technologyService(technologyService), entityTechService(entityTechService)
    , ui(new Ui::PortfolioPage)
{
    ui->setupUi(this);
    connectSignalsAndSlots();
    ui->scrollAreaTechnologies->init();
}

PortfolioPage::~PortfolioPage()
{
    delete ui;
}

//------ Initialization ------

void PortfolioPage::connectSignalsAndSlots()
{
    connect(portfolioService, &PortfolioService::portfolioReceipt, this, &PortfolioPage::setPortfolio);
    connect(portfolioService, &PortfolioService::errorOcurred, this, &PortfolioPage::errorOcurred);

    connect(technologyService, &TechnologyService::techIconReceipt, this, &PortfolioPage::techIconReceipt);

    connect(entityTechService, &EntityTechService::errorOcurred, this, &PortfolioPage::errorOcurred);
}

//------ UI Slots ------

void PortfolioPage::on_pushButtonAddTechnology_clicked()
{
    int entityId = 1;
    QString entityType = "portfolio";
    TechnologyRelation dialog(technologyService, entityTechService, entityId, entityType, this);
    dialog.exec();
}

void PortfolioPage::on_pushButtonAddProject_clicked()
{
    CreateProject dialog(this);
    if(dialog.exec() == QDialog::Rejected) return;

    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaProjectWidgetContents->layout();
    Project project = dialog.getProject();
    PortfolioProject *projectWidget = new PortfolioProject(nullptr, project);
    projectWidget->setParent(ui->scrollAreaProjectWidgetContents); // to avoid memory leak warning

    if(projectWidget && layout){
        layout->insertWidget(layout->count()-1, projectWidget);
    }
}

void PortfolioPage::on_pushButtonUpdatePhoto_clicked()
{
    QString imgPath = Utils::selectImageFile();
    QPixmap pixmap(imgPath);
    QPixmap roundedPixmap = Utils::roundedPixmap(pixmap, ui->labelPhoto->size());
    ui->labelPhoto->setPixmap(roundedPixmap);
}

void PortfolioPage::on_pushButtonHandleTechnologies_clicked()
{
    TechnologyHandler dialog(technologyService, this);
    dialog.exec();
}

//------ Public Methods------

void PortfolioPage::loadPortfolio()
{
    portfolioService->getPortfolio();
}

//------ Private Slots ------

void PortfolioPage::setPortfolio(const Portfolio &portfolio)
{
    ui->lineEditName->setText(portfolio.getUserName());
    ui->lineEditProfession->setText(portfolio.getUserProfession());
    ui->plainTextAbout->appendPlainText(portfolio.getUserAbout());
    setTechnologyWidgets(portfolio.getTechnologies());
}

void PortfolioPage::setUserPhoto(const QPixmap &pixmap)
{
    QPixmap rounded = Utils::roundedPixmap(pixmap, ui->labelPhoto->size());
    ui->labelPhoto->setPixmap(rounded);
}

void PortfolioPage::techIconReceipt(int techId, const QPixmap &pixmap)
{
    ui->scrollAreaTechnologies->setTechIcon(techId, pixmap);
}

void PortfolioPage::errorOcurred(const QString &message)
{
    Utils::showWarning(this, message);
}

//------ Helpers ------

void PortfolioPage::setTechnologyWidgets(const QVector<Technology> &techs)
{
    for(const Technology &tech : techs){
        TechnologyWidget *techWidget = new TechnologyWidget(nullptr, tech);
        technologyService->getTechIcon(tech.getId(), tech.getImgPath());
        ui->scrollAreaTechnologies->addTechnologyWidget(techWidget);
    }
}
