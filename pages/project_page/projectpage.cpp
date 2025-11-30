#include "projectpage.h"
#include "ui_projectpage.h"
#include "technologyrelation.h"

ProjectPage::ProjectPage(TechnologyService *technologyService, EntityTechService *entityTechService,
                         const Project &project, QWidget *parent)
    : QWidget(parent), technologyService(technologyService), entityTechService(entityTechService), project(project)
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
    connect(technologyService, &TechnologyService::techIconReceipt, this, &ProjectPage::techIconReceipt);
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
