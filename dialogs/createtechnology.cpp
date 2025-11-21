#include "createtechnology.h"
#include "ui_createtechnology.h"
#include <QMessageBox>
#include "utils.h"

CreateTechnology::CreateTechnology(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateTechnology)
{
    ui->setupUi(this);
}

CreateTechnology::~CreateTechnology()
{
    delete ui;
}

//------ UI Slots ------

void CreateTechnology::on_pushButtonSelectPhoto_clicked()
{
    imgPath = Utils::selectImageFile();
    if(imgPath.isEmpty())
        return;

    QPixmap original(imgPath);
    if(original.isNull())
        return;

    QSize targetSize = ui->labelPhoto->size();

    pixmapImage = Utils::roundedPixmap(original, targetSize);

    ui->labelPhoto->setPixmap(pixmapImage);
}


void CreateTechnology::on_pushButtonAccept_clicked()
{
    if(!checkValues()) return;

    QString techName = ui->lineEditName->text();
    technology = new Technology(this->parentWidget(), pixmapImage, techName, imgPath);

    accept();
}

//------ Helpers ------

bool CreateTechnology::checkValues()
{
    if(ui->lineEditName->text().isEmpty()){
        QMessageBox::warning(this, "Error", "La tecnología necesita un nombre!");
        return false;
    }

    if(pixmapImage.isNull()){
        QMessageBox::warning(this, "Error", "La tecnología necesita una imagen!");
        return false;
    }

    return true;
}

//------ Getters ------

Technology* CreateTechnology::getTechnology() const {
    return technology;
}
