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
    connect(technologyService, &TechnologyService::errorOcurred, this, &TechnologyHandler::errorOcurred);
}

//------ Private Slots ------

void TechnologyHandler::setTechnologies(const QVector<Technology> &technologies)
{
    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaTechnologiesWidgetContents->layout();
    if(!layout){
        Utils::showWarning(this, "No Layout For TechnologyWidget");
        return;
    }

    for(const Technology &tech : technologies){

        TechnologyWidget *widget = new TechnologyWidget(nullptr, tech);
        mode == Mode::Read ? widget->enableRadioButton() : widget->enableDeleteButton();

        layout->insertWidget(layout->count()-1, widget);
        technologyService->getTechIcon(tech.getId(), tech.getImgPath());
    }
}

void TechnologyHandler::setTechIcon(int techId, const QPixmap &pixmap)
{
    QLayout *layout = ui->scrollAreaTechnologiesWidgetContents->layout();
    if(!layout){
        Utils::showWarning(this, "No Layout For TechnologyWidget");
        return;
    }

    for(int i = 0; i<layout->count(); i++){
        QWidget *widget= layout->itemAt(i)->widget();
        TechnologyWidget *techWidget = qobject_cast<TechnologyWidget*>(widget);

        if(techWidget && techWidget->getTechnology().getId() == techId){
            techWidget->setTechIcon(pixmap);
            break;
        }

    }
}

void TechnologyHandler::techCreated(int techId)
{
    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaTechnologiesWidgetContents->layout();

    if(!layout){
        Utils::showWarning(this, "No Layout For TechnologyWidget");
        return;
    }
    cacheTech.setId(techId);
    TechnologyWidget *widget = new TechnologyWidget(nullptr, cacheTech);
    widget->setTechIcon(QPixmap(cacheTech.getImgPath()));
    mode == Mode::Read ? widget->enableRadioButton() : widget->enableDeleteButton();

    layout->insertWidget(layout->count()-1, widget);
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
