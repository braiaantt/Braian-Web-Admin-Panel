#include "portfoliopage.h"
#include "ui_portfoliopage.h"
#include "createproject.h"
#include "portfolioproject.h"
#include "utils.h"
#include "technologyhandler.h"
#include "technologyrelation.h"
#include "portfolioproject.h"

PortfolioPage::PortfolioPage(PortfolioService *portfolioService, TechnologyService* technologyService,
                             EntityTechService *entityTechService, ProjectService *projectService, QWidget *parent)
    : QWidget(parent), portfolioService(portfolioService), technologyService(technologyService),
    entityTechService(entityTechService), projectService(projectService)
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

    connect(projectService, &ProjectService::projectCoverReceipt, this, &PortfolioPage::projectCoverReceipt);
}

//------ UI Slots ------

void PortfolioPage::on_pushButtonAddTechnology_clicked()
{
    int entityId = 1;
    QString entityType = "portfolio";
    TechnologyRelation dialog(technologyService, entityTechService, entityId, entityType, this);
    connect(&dialog, &TechnologyRelation::technologiesChanged, this, &PortfolioPage::refreshTechnologies);
    dialog.exec();
}

void PortfolioPage::on_pushButtonAddProject_clicked()
{
    CreateProject dialog(projectService, this);
    if(dialog.exec() == QDialog::Rejected) return;

    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaProjectWidgetContents->layout();
    Project project = dialog.getProject();
    PortfolioProject *projectWidget = new PortfolioProject(nullptr, project);

    if(projectWidget && layout){
        layout->insertWidget(layout->count()-1, projectWidget);
        projectWidget->setParent(ui->scrollAreaProjectWidgetContents); // to avoid memory leak warning
        connect(projectWidget, &PortfolioProject::goToProject, this, &PortfolioPage::goToProject);
    } else {
        projectWidget->deleteLater();
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
    setProjectWidgets(portfolio.getProjects());
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

void PortfolioPage::refreshTechnologies()
{
    /*
    Future implementation with service provider to avoid
    interferences between PortfolioPage and TechnologyRelation dialog,
    because they use the same service to get technologies
    */
}

void PortfolioPage::projectCoverReceipt(int projectId, const QPixmap &pixmap)
{
    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(ui->scrollAreaProjectWidgetContents->layout());
    if(!layout) return;

    for(int i = 0; i<layout->count(); i++){
        PortfolioProject *projectWidget = qobject_cast<PortfolioProject*>(layout->itemAt(i)->widget());
        if(projectWidget && projectWidget->getProject().getId() == projectId){
            projectWidget->setCoverImage(pixmap);
            break;
        }
    }
}

void PortfolioPage::goToProject(const Project &project)
{
    emit projectClicked(project);
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

void PortfolioPage::setProjectWidgets(const QVector<Project> &projects)
{
    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(ui->scrollAreaProjectWidgetContents->layout());
    if(!layout) return;

    for(const Project &project : projects){
        PortfolioProject *widget = new PortfolioProject(nullptr, project);
        projectService->getProjectCover(project.getId(), project.getCoverPath());
        layout->insertWidget(layout->count()-1, widget);
        connect(widget, &PortfolioProject::goToProject, this, &PortfolioPage::goToProject);
    }
}
