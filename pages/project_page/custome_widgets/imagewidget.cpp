#include "imagewidget.h"
#include "ui_imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

//------ UI Slots ------

void ImageWidget::on_pushButton_clicked()
{
    emit removeImage(imagePath);
}

//------ Setters ------

void ImageWidget::setImagePath(const QString &path)
{
    imagePath = path;
}

void ImageWidget::setPixMap(const QPixmap &pixmap)
{
    ui->label->setPixmap(pixmap);
}

//------ Getters ------

QString ImageWidget::getImagePath() const
{
    return imagePath;
}
