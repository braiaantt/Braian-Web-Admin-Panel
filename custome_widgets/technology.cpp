#include "technology.h"
#include "ui_technology.h"

Technology::Technology(QWidget *parent, const QPixmap &image, const QString &name)
    : QWidget(parent)
    , ui(new Ui::Technology)
{
    ui->setupUi(this);
}

Technology::~Technology()
{
    delete ui;
}
