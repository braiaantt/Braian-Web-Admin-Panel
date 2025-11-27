#ifndef TECHNOLOGYHANDLER_H
#define TECHNOLOGYHANDLER_H

#include <QDialog>
#include "technology.h"
#include "technologyservice.h"

enum class Mode{
    Read,
    Delete
};

namespace Ui {
class TechnologyHandler;
}

class TechnologyHandler : public QDialog
{
    Q_OBJECT

public:
    explicit TechnologyHandler(TechnologyService* technologyService, Mode mode, QWidget *parent = nullptr);
    ~TechnologyHandler();

private slots:
    void setTechnologies(const QVector<Technology> &technologies);
    void setTechIcon(int techId, const QPixmap &pixmap);
    void techCreated(int techId);
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButtonAddTech_clicked();

private:
    Ui::TechnologyHandler *ui;
    TechnologyService *technologyService;
    Technology cacheTech;
    Mode mode;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // TECHNOLOGYHANDLER_H
