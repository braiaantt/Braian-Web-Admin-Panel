#ifndef CREATETECHNOLOGY_H
#define CREATETECHNOLOGY_H

#include <QDialog>
#include "technology.h"

namespace Ui {
class CreateTechnology;
}

class CreateTechnology : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTechnology(QWidget *parent);
    ~CreateTechnology();

    //getters
    Technology* getTechnology() const;

private slots:
    void on_pushButtonSelectPhoto_clicked();
    void on_pushButtonAccept_clicked();

private:
    Ui::CreateTechnology *ui;
    QString imgPath;
    QPixmap pixmapImage;
    Technology *technology;

    bool checkValues();

};

#endif // CREATETECHNOLOGY_H
