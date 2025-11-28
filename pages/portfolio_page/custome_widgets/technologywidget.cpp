#include "technologywidget.h"
#include "ui_technologywidget.h"
#include "utils.h"

TechnologyWidget::TechnologyWidget(QWidget *parent, const Technology &technology)
    : QWidget(parent), technology(technology)
    , ui(new Ui::Technology)
{
    ui->setupUi(this);
    init();
}

TechnologyWidget::~TechnologyWidget()
{
    delete ui;
}

//------ Initialization ------

void TechnologyWidget::init()
{
    ui->labelName->setText(technology.getName());
    ui->pushButtonDelete->setVisible(false);
    ui->radioButton->setVisible(false);
}

//------ Config Methods ------

void TechnologyWidget::enableDeleteButton()
{
    ui->pushButtonDelete->setVisible(true);
}

void TechnologyWidget::enableRadioButton()
{
    ui->radioButton->setVisible(true);
}

//------ UI Slots ------

void TechnologyWidget::on_pushButtonDelete_clicked()
{
    emit deleteTechnology(technology);
}

//------ Getters ------

const Technology& TechnologyWidget::getTechnology() const
{
    return technology;
}

int TechnologyWidget::isSelected() const
{
    return ui->radioButton->isChecked();
}

//------ Setters ------

void TechnologyWidget::setTechIcon(const QPixmap &pixmap)
{
    QPixmap rounded = Utils::roundedPixmap(pixmap, ui->labelPhoto->size());
    ui->labelPhoto->setPixmap(rounded);
}

void TechnologyWidget::setSelected(bool state)
{
    ui->radioButton->setChecked(state);
}
