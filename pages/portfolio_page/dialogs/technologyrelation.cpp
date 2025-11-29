#include "technologyrelation.h"
#include "ui_technologyrelation.h"
#include "utils.h"
#include "technologywidget.h"

TechnologyRelation::TechnologyRelation(TechnologyService *technologyService, EntityTechService *entityTechService,
                                       int entityId, const QString &entityType, QWidget *parent)
    : QDialog(parent), technologyService(technologyService), entityTechService(entityTechService), entityId(entityId), entityType(entityType)
    , ui(new Ui::TechnologyRelation)
{
    ui->setupUi(this);
    init();
}

TechnologyRelation::~TechnologyRelation()
{
    delete ui;
}

//------ Initialization ------

void TechnologyRelation::init()
{
    ui->scrollAreaTechnologies->init();
    connectSignalsAndSlots();
    technologyService->getTechnologies();
}

void TechnologyRelation::connectSignalsAndSlots()
{
    connect(technologyService, &TechnologyService::technologiesReceipt, this, &TechnologyRelation::setTechnologies);
    connect(technologyService, &TechnologyService::techIconReceipt, this, &TechnologyRelation::setTechIcon);
    connect(technologyService, &TechnologyService::errorOcurred, this, &TechnologyRelation::errorOcurred);

    connect(entityTechService, &EntityTechService::commitSuccess, this, &TechnologyRelation::commitSuccess);
}

//------ Public Slots ------

void TechnologyRelation::setEntityTechnologies(const QVector<Technology> &techs)
{
    for(const Technology &tech : techs){
        ui->scrollAreaTechnologies->selectTechnology(tech.getId());
    }
}

//------ Private Slots ------

void TechnologyRelation::setTechnologies(const QVector<Technology> &technologies)
{
    for(const Technology &tech : technologies){

        //Create and initializate
        TechnologyWidget *widget = new TechnologyWidget(nullptr, tech);
        widget->enableRadioButton();

        //Get image from server
        technologyService->getTechIcon(tech.getId(), tech.getImgPath());

        //Add widget
        ui->scrollAreaTechnologies->addTechnologyWidget(widget);
    }
}

void TechnologyRelation::setTechIcon(int techId, const QPixmap &pixmap)
{
    ui->scrollAreaTechnologies->setTechIcon(techId, pixmap);
}

void TechnologyRelation::errorOcurred(const QString &message)
{
    Utils::showWarning(this, message);
}

void TechnologyRelation::commitSuccess()
{
    emit technologiesChanged();
}

//------ UI Slots ------

void TechnologyRelation::on_pushButtonCommitChanges_clicked()
{
    QHash<int, bool> initialStates = ui->scrollAreaTechnologies->getInitialStates();
    QHash<int, bool> finalStates = ui->scrollAreaTechnologies->getFinalStates();

    QList<int> toAdd;
    QList<int> toRemove;

    for(auto it = initialStates.begin(); it != initialStates.end(); ++it){
        int techId = it.key();
        bool wasSelected = it.value();
        bool isSelected  = finalStates.value(techId, false);

        if(wasSelected == isSelected)
            continue;

        if(!wasSelected && isSelected)
            toAdd.append(techId);

        if(wasSelected && !isSelected)
            toRemove.append(techId);
    }

    for(int techId : toAdd) entityTechService->addRelation(entityId, entityType, techId);
    for(int techId : toRemove) entityTechService->removeRelation(entityId, entityType, techId);
}
