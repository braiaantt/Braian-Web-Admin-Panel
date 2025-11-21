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
    QString imgPath = Utils::selectImageFile();
    if(imgPath.isEmpty())
        return;

    QPixmap original(imgPath);
    if(original.isNull())
        return;

    QSize targetSize = ui->labelPhoto->size();

    QPixmap pixmapImage = Utils::roundedPixmap(original, targetSize);

    ui->labelPhoto->setPixmap(pixmapImage);
    technology.setImgPath(imgPath);
}


void CreateTechnology::on_pushButtonAccept_clicked()
{
    if(!checkValues()) return;

    QString techName = ui->lineEditName->text();
    technology.setName(techName);

    accept();
}

//------ Helpers ------

bool CreateTechnology::checkValues()
{
    if(ui->lineEditName->text().isEmpty()){
        QMessageBox::warning(this, "Error", "La tecnología necesita un nombre!");
        return false;
    }

    if(technology.getImgPath().isEmpty()){
        QMessageBox::warning(this, "Error", "La tecnología necesita una imagen!");
        return false;
    }

    return true;
}

//------ Getters ------

Technology CreateTechnology::getTechnology() const {
    return technology;
}
