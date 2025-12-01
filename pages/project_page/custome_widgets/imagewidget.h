#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();

    //------ Setters ------
    void setImagePath(const QString &imagePath);
    void setPixMap(const QPixmap &pixmap);

    //------ Getters ------
    QString getImagePath() const;

signals:
    void removeImage(const QString &imagePath);

private slots:
    //------ UI Slots ------
    void on_pushButton_clicked();

private:
    Ui::ImageWidget *ui;
    QString imagePath;
};

#endif // IMAGEWIDGET_H
