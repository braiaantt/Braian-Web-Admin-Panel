#ifndef PROJECTPAGE_H
#define PROJECTPAGE_H

#include <QWidget>
#include "project.h"
#include "technologyservice.h"
#include "entitytechservice.h"

namespace Ui {
class ProjectPage;
}

class ProjectPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectPage(TechnologyService *technologyService, EntityTechService *entityTechService,
                         const Project &project, QWidget *parent = nullptr);
    ~ProjectPage();

private slots:
    void technologiesRelated(const QVector<Technology> &techs);
    void techIconReceipt(int techId, const QPixmap &pixmap);

    //------ UI Slots ------
    void on_pushButtonBack_clicked();

    void on_pushButtonAddTechnology_clicked();

signals:
    void backToPortfolio(ProjectPage *page);

private:
    Ui::ProjectPage *ui;
    TechnologyService *technologyService;
    EntityTechService *entityTechService;
    Project project;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // PROJECTPAGE_H
