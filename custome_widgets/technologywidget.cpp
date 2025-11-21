#include "technologywidget.h"
#include "ui_technologywidget.h"
#include "utils.h"

TechnologyWidget::TechnologyWidget(QWidget *parent, const Technology &technology)
    : QWidget(parent)
    , ui(new Ui::Technology)
{
    ui->setupUi(this);
    init(technology);
}

TechnologyWidget::~TechnologyWidget()
{
    delete ui;
}

//------ Initialization ------

void TechnologyWidget::init(const Technology &technology)
{
    if(!technology.getImgPath().isEmpty()){
        QPixmap pixmap = Utils::roundedPixmap(QPixmap(technology.getImgPath()), ui->labelPhoto->size());
        ui->labelPhoto->setPixmap(pixmap);
    }

    ui->labelName->setText(technology.getName());
}
