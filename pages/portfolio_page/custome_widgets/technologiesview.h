#ifndef TECHNOLOGIESVIEW_H
#define TECHNOLOGIESVIEW_H

#include <QScrollArea>
#include <QHBoxLayout>
#include "technologywidget.h"

class TechnologiesView : public QScrollArea
{
public:
    TechnologiesView(QWidget *parent = nullptr);

    //------ Initialization ------
    void init();

    //------ Public Methods ------
    void addTechnologyWidget(TechnologyWidget *widget);
    void deleteTechnologyWidget(int id);
    void setTechIcon(int techId, const QPixmap &pixmap);
    void selectTechnology(int techId);

    //------ Getters ------
    QHash<int, bool> getInitialStates() const;
    QHash<int, bool> getFinalStates();

private:
    QHBoxLayout *layout;
    QHash<int, bool> initialStates;

    //------ Helpers ------
    TechnologyWidget* fromWidget(QWidget *widget);
};

#endif // TECHNOLOGIESVIEW_H
