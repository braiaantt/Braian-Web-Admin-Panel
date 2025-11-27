#include "portfoliopage.h"
#include "ui_portfoliopage.h"
#include "createtechnology.h"
#include "createproject.h"
#include "portfolioproject.h"
#include "technologywidget.h"
#include "utils.h"
#include "technologyhandler.h"

PortfolioPage::PortfolioPage(PortfolioService *portfolioService, TechnologyService* technologyService, QWidget *parent)
    : QWidget(parent), portfolioService(portfolioService), technologyService(technologyService)
    , ui(new Ui::PortfolioPage)
{
    ui->setupUi(this);
    connectSignalsAndSlots();
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
}

//------ UI Slots ------

void PortfolioPage::on_pushButtonAddTechnology_clicked()
{
    CreateTechnology dialog(this);
    if(dialog.exec() == QDialog::Rejected) return;

    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaTechnologyWidgetContents->layout();
    Technology technology = dialog.getTechnology();
    TechnologyWidget *technologyWidget = new TechnologyWidget(nullptr, technology);
    technologyWidget->setParent(ui->scrollAreaTechnologyWidgetContents); // to avoid memory leak warning

    if(technologyWidget && layout){
        layout->insertWidget(layout->count()-1, technologyWidget);
    }
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
    TechnologyHandler techHandler(technologyService, Mode::Delete, this);
    techHandler.exec();
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
}

void PortfolioPage::setUserPhoto(const QPixmap &pixmap)
{
    QPixmap rounded = Utils::roundedPixmap(pixmap, ui->labelPhoto->size());
    ui->labelPhoto->setPixmap(rounded);
}

void PortfolioPage::errorOcurred(const QString &message)
{
    Utils::showWarning(this, message);
}
