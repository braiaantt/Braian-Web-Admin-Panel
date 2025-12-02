#ifndef FEATURESHANDLER_H
#define FEATURESHANDLER_H

#include <QDialog>
#include "servicefactory.h"
#include "projectservice.h"
#include "featureservice.h"
#include "feature.h"

namespace Ui {
class FeaturesHandler;
}

class FeaturesHandler : public QDialog
{
    Q_OBJECT

public:
    explicit FeaturesHandler(ServiceFactory *serviceFactory, int projectId, QWidget *parent = nullptr);
    ~FeaturesHandler();

private slots:
    void featuresReceipt(const QVector<Feature> &feats);
    void featureCreated(const Feature &feature);
    void featureDeleted();
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButtonAddFeat_clicked();

    void on_pushButtonDeleteFeat_clicked();

private:
    Ui::FeaturesHandler *ui;
    int projectId;
    ServiceFactory *factory;
    ProjectService *projectService;
    FeatureService *featureService;

    //------ Cache ------
    Feature cacheFeature;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // FEATURESHANDLER_H
