#include "projectpage.h"
#include "ui_projectpage.h"
#include "technologyrelation.h"
#include "handleimages.h"
#include "featureshandler.h"
#include "technicalinfohandler.h"
#include "utils.h"

ProjectPage::ProjectPage(ServiceFactory *factory, const Project &project, QWidget *parent)
    : QWidget(parent), factory(factory), project(project)
    , ui(new Ui::ProjectPage)
{
    ui->setupUi(this);
    init();
}

ProjectPage::~ProjectPage()
{
    delete ui;
}

//------ Initialization ------

void ProjectPage::init()
{
    technologyService = factory->makeTechnologyService(this);
    entityTechService = factory->makeEntityTechService(this);
    entityImageService = factory->makeEntityImageService(this);
    projectService = factory->makeProjectService(this);

    ui->lineEditTitle->setText(project.getName());
    ui->plainTextEditSmallAbout->setPlainText(project.getSmallAbout());
    ui->plainTextEditBigAbout->setPlainText(project.getBigAbout());
    ui->plainTextEditMyComments->setPlainText(project.getUserComments());
    ui->scrollAreaTechnologies->init();

    connectSignalsAndSlots();

    QString entityType = "project";
    entityTechService->getRelations(project.getId(), entityType);
}

void ProjectPage::connectSignalsAndSlots()
{
    connect(entityTechService, &EntityTechService::technologiesRelated, this, &ProjectPage::technologiesRelated);
    connect(entityTechService, &EntityTechService::errorOcurred, this, &ProjectPage::errorOcurred);

    connect(technologyService, &TechnologyService::techIconReceipt, this, &ProjectPage::techIconReceipt);
    connect(technologyService, &TechnologyService::errorOcurred, this, &ProjectPage::errorOcurred);

    connect(projectService, &ProjectService::projectDeleted, this, &ProjectPage::projectDeleted);
    connect(projectService, &ProjectService::errorOcurred, this, &ProjectPage::errorOcurred);
}

//------ UI Slots ------

void ProjectPage::on_pushButtonBack_clicked()
{
    emit backToPortfolio(this);
}

void ProjectPage::on_pushButtonAddTechnology_clicked()
{
    disconnect(entityTechService, &EntityTechService::technologiesRelated, this, &ProjectPage::technologiesRelated);

    QString entityType = "project";
    TechnologyRelation dialog(technologyService, entityTechService, project.getId(), entityType, this);
    dialog.exec();

    connect(entityTechService, &EntityTechService::technologiesRelated, this, &ProjectPage::technologiesRelated);
    //connect and disconnect this way temporaly
}

void ProjectPage::on_pushButtonHandleGallery_clicked()
{
    QString entityType = "project";
    HandleImages dialog(factory, project.getId(), this);
    dialog.exec();;
}


void ProjectPage::on_pushButtonHandleFeats_clicked()
{
    FeaturesHandler dialog(factory, project.getId(), this);
    dialog.exec();
}

void ProjectPage::on_pushButtonHandleTechnicalInf_clicked()
{
    TechnicalInfoHandler dialog(factory, project.getId(), this);
    dialog.exec();
}

void ProjectPage::on_pushButtonDeleteProject_clicked()
{
    projectService->deleteProject(project.getId());
}

//------ Private Slots ------

void ProjectPage::technologiesRelated(const QVector<Technology> &techs)
{
    for(const Technology &tech : techs){
        TechnologyWidget *techWidget = new TechnologyWidget(nullptr, tech);
        technologyService->getTechIcon(tech.getId(), tech.getImgPath());
        ui->scrollAreaTechnologies->addTechnologyWidget(techWidget);
    }
}

void ProjectPage::techIconReceipt(int techId, const QPixmap &pixmap)
{
    ui->scrollAreaTechnologies->setTechIcon(techId, pixmap);
}

void ProjectPage::projectDeleted()
{
    emit deleteProject(project.getId());
    emit backToPortfolio(this);
}

void ProjectPage::errorOcurred(const QString &message)
{
    Utils::showWarning(this, message);
}
