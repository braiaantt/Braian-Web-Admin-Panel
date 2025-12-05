#ifndef TECHNOLOGYRELATION_H
#define TECHNOLOGYRELATION_H

#include <QDialog>
#include "servicefactory.h"
#include "technologyservice.h"
#include "entitytechservice.h"

namespace Ui {
class TechnologyRelation;
}

class TechnologyRelation : public QDialog
{
    Q_OBJECT

public:
    explicit TechnologyRelation(ServiceFactory *factory, int entityId, const QString &entityType, QWidget *parent = nullptr);
    ~TechnologyRelation();

private slots:
    void setTechnologies(const QVector<Technology> &technologies);
    void setTechIcon(int techId, const QPixmap &pixmap);
    void commitSuccess();
    void technologiesRelated(const QVector<Technology> &techsRelated);
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButtonCommitChanges_clicked();

signals:
    void technologiesChanged();

private:
    Ui::TechnologyRelation *ui;
    ServiceFactory *factory;
    TechnologyService *technologyService;
    EntityTechService *entityTechService;
    int entityId;
    QString entityType;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // TECHNOLOGYRELATION_H
