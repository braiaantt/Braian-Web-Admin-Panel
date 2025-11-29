#ifndef TECHNOLOGYHANDLER_H
#define TECHNOLOGYHANDLER_H

#include <QDialog>
#include "technology.h"
#include "technologyservice.h"

namespace Ui {
class TechnologyHandler;
}

class TechnologyHandler : public QDialog
{
    Q_OBJECT

public:
    explicit TechnologyHandler(TechnologyService* technologyService, QWidget *parent = nullptr);
    ~TechnologyHandler();

private slots:
    void setTechnologies(const QVector<Technology> &technologies);
    void setTechIcon(int techId, const QPixmap &pixmap);
    void techCreated(int techId);
    void techDeleted(int techId);
    void deleteTechnology(const Technology &tech);
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButtonAddTech_clicked();

private:
    Ui::TechnologyHandler *ui;
    TechnologyService *technologyService;
    Technology cacheTech;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // TECHNOLOGYHANDLER_H
