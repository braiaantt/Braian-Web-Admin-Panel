#ifndef TECHNOLOGIESVIEW_H
#define TECHNOLOGIESVIEW_H

#include <QScrollArea>
#include <QHBoxLayout>
#include "technologywidget.h"

class TechnologiesView : public QScrollArea
{
public:
    TechnologiesView(QWidget *parent = nullptr);

    void addTechnologyWidget(TechnologyWidget *widget);
    void deleteTechnologyWidget(int id);
    void setTechIcon(int techId, const QPixmap &pixmap);

private:
    QHBoxLayout *layout;

    //------ Helpers ------
    TechnologyWidget* fromWidget(QWidget *widget);
};

#endif // TECHNOLOGIESVIEW_H
