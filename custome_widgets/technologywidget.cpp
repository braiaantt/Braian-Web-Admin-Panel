#include "technology.h"
#include "ui_technology.h"

Technology::Technology(QWidget *parent, const QPixmap &photo, const QString &name, const QString &_filePath)
    : QWidget(parent)
    , ui(new Ui::Technology)
{
    ui->setupUi(this);
    ui->labelPhoto->setPixmap(photo);
    ui->labelName->setText(name);
    filePath = _filePath;
}

Technology::~Technology()
{
    delete ui;
}
