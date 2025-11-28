#ifndef TECHNOLOGYWIDGET_H
#define TECHNOLOGYWIDGET_H

#include <QWidget>
#include "technology.h"

namespace Ui {
class Technology;
}

class TechnologyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TechnologyWidget(QWidget *parent = nullptr, const Technology &technology = Technology());
    ~TechnologyWidget();

    //------ Getters ------
    const Technology& getTechnology() const;
    int isSelected() const;

    //------ Setters ------
    void setTechIcon(const QPixmap &pixmap);
    void setSelected(bool state);

    //------ Config Methods ------
    void enableDeleteButton();
    void enableRadioButton();

signals:
    void deleteTechnology(const Technology &tech);

private slots:
    //------ UI Slots ------
    void on_pushButtonDelete_clicked();

private:
    Ui::Technology *ui;
    Technology technology;

    //------ Initialization ------
    void init();

};

#endif // TECHNOLOGYWIDGET_H
