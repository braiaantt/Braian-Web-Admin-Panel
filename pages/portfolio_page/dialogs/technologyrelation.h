#ifndef TECHNOLOGYRELATION_H
#define TECHNOLOGYRELATION_H

#include <QDialog>
#include "technologyservice.h"
#include "entitytechservice.h"

namespace Ui {
class TechnologyRelation;
}

class TechnologyRelation : public QDialog
{
    Q_OBJECT

public:
    explicit TechnologyRelation(TechnologyService *technologyService, EntityTechService *entityTechService,
                                int entityId, const QString &entityType, QWidget *parent = nullptr);
    ~TechnologyRelation();

    void setEntityTechnologies(const QVector<Technology> &techs);

private slots:
    void setTechnologies(const QVector<Technology> &technologies);
    void setTechIcon(int techId, const QPixmap &pixmap);
    void commitSuccess();
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButtonCommitChanges_clicked();

signals:
    void technologiesChanged();

private:
    Ui::TechnologyRelation *ui;
    TechnologyService *technologyService;
    EntityTechService *entityTechService;
    int entityId;
    QString entityType;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // TECHNOLOGYRELATION_H
