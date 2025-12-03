#ifndef TECHNICALINFOHANDLER_H
#define TECHNICALINFOHANDLER_H

#include <QDialog>
#include "servicefactory.h"
#include "projectservice.h"
#include "technicalinfoservice.h"
#include "technicalinfo.h"

namespace Ui {
class TechnicalInfoHandler;
}

class TechnicalInfoHandler : public QDialog
{
    Q_OBJECT

public:
    explicit TechnicalInfoHandler(ServiceFactory *factory, int projectId, QWidget *parent = nullptr);
    ~TechnicalInfoHandler();

private slots:
    void technicalInfoReceipt(const QVector<TechnicalInfo> &info);
    void technicalInfoAdded(const TechnicalInfo &info);
    void technicalInfoDeleted(int deletedId);
    void errorOcurred(const QString &message);

    void on_pushButtonDeleteTechnicalInfo_clicked();

    void on_pushButtonAddTechnicalInfo_clicked();

private:
    Ui::TechnicalInfoHandler *ui;
    ServiceFactory *factory;
    ProjectService *projectService;
    TechnicalInfoService *technicalInfoService;
    int projectId;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // TECHNICALINFOHANDLER_H
