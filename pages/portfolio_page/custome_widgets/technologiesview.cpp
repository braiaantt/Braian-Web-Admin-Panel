#include "technologiesview.h"
#include <QHBoxLayout>

TechnologiesView::TechnologiesView(QWidget *parent) :
    QScrollArea(parent)
{

}

void TechnologiesView::addTechnologyWidget(TechnologyWidget *widget)
{
    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(this->widget()->layout());
    layout->insertWidget(layout->count() - 1, widget);
}

void TechnologiesView::deleteTechnologyWidget(int id)
{
    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(this->widget()->layout());

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
    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(this->widget()->layout());

    for(int i = 0; i<layout->count(); i++){
        TechnologyWidget *techWidget = fromWidget(layout->itemAt(i)->widget());
        if(!techWidget) continue;

        if(techWidget->getTechnology().getId() == techId){
            techWidget->setTechIcon(icon);
            break;
        }
    }
}

//------ Helpers ------

TechnologyWidget* TechnologiesView::fromWidget(QWidget *widget)
{
    if(!widget) return nullptr;

    TechnologyWidget *techWidget = qobject_cast<TechnologyWidget*>(widget);
    if(!techWidget) return nullptr;

    return techWidget;
}
