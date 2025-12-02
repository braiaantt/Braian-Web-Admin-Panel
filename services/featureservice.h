#ifndef FEATURESERVICE_H
#define FEATURESERVICE_H

#include <QObject>
#include "apiclient.h"
#include "feature.h"

class FeatureService : public QObject
{
    Q_OBJECT
public:
    FeatureService(ApiClient *apiClient, QObject *parent);
    void addFeature(int projectId, const QString &feature);
    void deleteFeature(int featureId);

private slots:
    void addFeatureFinished();
    void deleteFeatureFinished();

signals:
    void featureCreated(const Feature &feature);
    void featureDeleted();
    void errorOcurred(const QString &message);

private:
    ApiClient *apiClient;

    //------ Reply Handlers ------
    Feature handleAddFeature(const QByteArray &data);
};

#endif // FEATURESERVICE_H
