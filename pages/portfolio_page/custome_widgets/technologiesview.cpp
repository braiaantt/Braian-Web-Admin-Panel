#include "technologiesview.h"

TechnologiesView::TechnologiesView(QWidget *parent) :
    QScrollArea(parent)
{

}

//------ Initialization ------

void TechnologiesView::init()
{
    layout = qobject_cast<QHBoxLayout*>(this->widget()->layout());
}

//------ Public Methods ------

void TechnologiesView::addTechnologyWidget(TechnologyWidget *widget)
{
    layout->insertWidget(layout->count() - 1, widget);
    initialStates.insert(widget->getTechnology().getId(), false);
}

void TechnologiesView::deleteTechnologyWidget(int id)
{
    for(int i = 0; i<layout->count(); i++){
        TechnologyWidget *techWidget = fromWidget(layout->itemAt(i)->widget());
        if(!techWidget) continue;

        if(techWidget->getTechnology().getId() == id){
            layout->removeWidget(techWidget);
            techWidget->deleteLater();
            break;
        }
    }
}

void TechnologiesView::setTechIcon(int techId, const QPixmap &icon)
{
    for(int i = 0; i<layout->count(); i++){
        TechnologyWidget *techWidget = fromWidget(layout->itemAt(i)->widget());
        if(!techWidget) continue;

        if(techWidget->getTechnology().getId() == techId){
            techWidget->setTechIcon(icon);
            break;
        }
    }
}

void TechnologiesView::selectTechnology(int techId)
{
    for(int i = 0; i<layout->count(); i++){
        TechnologyWidget *techWidget = fromWidget(layout->itemAt(i)->widget());
        if(!techWidget) continue;

        if(techWidget->getTechnology().getId() == techId){
            techWidget->setSelected(true);
            initialStates[techId] = true;
            break;
        }
    }
}

//------ Getters ------

QHash<int, bool> TechnologiesView::getInitialStates() const
{
    return initialStates;
}

QHash<int, bool> TechnologiesView::getFinalStates()
{
    QHash<int, bool> finalStates;

    for(int i = 0; i<layout->count(); i++){
        TechnologyWidget *techWidget = fromWidget(layout->itemAt(i)->widget());
        if(!techWidget) continue;

        int id = techWidget->getTechnology().getId();
        bool state = techWidget->isSelected();
        finalStates.insert(id, state);
    }

    return finalStates;
}

//------ Helpers ------

TechnologyWidget* TechnologiesView::fromWidget(QWidget *widget)
{
    if(!widget) return nullptr;

    TechnologyWidget *techWidget = qobject_cast<TechnologyWidget*>(widget);
    if(!techWidget) return nullptr;

    return techWidget;
}
