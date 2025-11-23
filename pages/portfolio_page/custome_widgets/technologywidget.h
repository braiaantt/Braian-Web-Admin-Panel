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

private:
    Ui::Technology *ui;

    //------ Initialization ------
    void init(const Technology &technology);

};

#endif // TECHNOLOGYWIDGET_H
