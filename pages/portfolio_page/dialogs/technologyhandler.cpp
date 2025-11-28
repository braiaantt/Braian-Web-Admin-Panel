#include "technologyhandler.h"
#include "ui_technologyhandler.h"
#include "technologywidget.h"
#include "utils.h"
#include "createtechnology.h"

TechnologyHandler::TechnologyHandler(TechnologyService *technologyService, Mode mode, QWidget *parent)
    : QDialog(parent), technologyService(technologyService), mode(mode)
    , ui(new Ui::TechnologyHandler)
{
    ui->setupUi(this);
    init();
}

TechnologyHandler::~TechnologyHandler()
{
    delete ui;
}

//------ Initialization ------

void TechnologyHandler::init()
{
    connectSignalsAndSlots();
    technologyService->getTechnologies();
}

void TechnologyHandler::connectSignalsAndSlots()
{
    connect(technologyService, &TechnologyService::technologiesReceipt, this, &TechnologyHandler::setTechnologies);
    connect(technologyService, &TechnologyService::techIconReceipt, this, &TechnologyHandler::setTechIcon);
    connect(technologyService, &TechnologyService::techCreated, this, &TechnologyHandler::techCreated);
    connect(technologyService, &TechnologyService::techDeleted, this, &TechnologyHandler::techDeleted);
    connect(technologyService, &TechnologyService::errorOcurred, this, &TechnologyHandler::errorOcurred);
}

//------ Private Slots ------

void TechnologyHandler::setTechnologies(const QVector<Technology> &technologies)
{
    for(const Technology &tech : technologies){

        //Create and initializate
        TechnologyWidget *widget = new TechnologyWidget(nullptr, tech);
        mode == Mode::Read ? widget->enableRadioButton() : widget->enableDeleteButton();
        connect(widget, &TechnologyWidget::deleteTechnology, this, &TechnologyHandler::deleteTechnology);

        //Get image from server
        technologyService->getTechIcon(tech.getId(), tech.getImgPath());

        //Add widget
        ui->scrollAreaTechnologies->addTechnologyWidget(widget);
    }
}

void TechnologyHandler::setTechIcon(int techId, const QPixmap &pixmap)
{
    ui->scrollAreaTechnologies->setTechIcon(techId, pixmap);
}

void TechnologyHandler::techCreated(int techId)
{
    cacheTech.setId(techId);

    //Create and initializate
    TechnologyWidget *widget = new TechnologyWidget(nullptr, cacheTech);
    widget->setTechIcon(QPixmap(cacheTech.getImgPath()));
    mode == Mode::Read ? widget->enableRadioButton() : widget->enableDeleteButton();
    connect(widget, &TechnologyWidget::deleteTechnology, this, &TechnologyHandler::deleteTechnology);

    //Add widget
    ui->scrollAreaTechnologies->addTechnologyWidget(widget);
}

void TechnologyHandler::deleteTechnology(const Technology &tech)
{
    technologyService->deleteTechnology(tech.getId());
}

void TechnologyHandler::techDeleted(int techId)
{
    ui->scrollAreaTechnologies->deleteTechnologyWidget(techId);
}

void TechnologyHandler::errorOcurred(const QString &message)
{
    Utils::showWarning(this, message);
}

//------ UI Slots ------

void TechnologyHandler::on_pushButtonAddTech_clicked()
{
    CreateTechnology dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        cacheTech = dialog.getTechnology();
        technologyService->addTechnology(cacheTech);
    }
}
