#include "featureservice.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "networkutils.h"

FeatureService::FeatureService(ApiClient *apiClient, QObject *parent) :
    QObject(parent), apiClient(apiClient)
{

}

//------ Public Methods ------

void FeatureService::addFeature(int projectId, const QString &feature)
{
    QJsonObject obj;
    obj["id_project"] = projectId;
    obj["feat"] = feature;

    QJsonDocument doc(obj);
    QNetworkReply *reply = apiClient->postFeature(doc.toJson());
    if(!reply){
        emit errorOcurred("Feature Service - AddFeature: Reply Null. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &FeatureService::addFeatureFinished);
}

void FeatureService::deleteFeature(int featureId)
{
    QNetworkReply *reply = apiClient->deleteFeature(featureId);
    if(!reply){
        emit errorOcurred("Feature Service - Delete Feature: Reply Null. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &FeatureService::deleteFeatureFinished);
}

//------ Private Slots ------

void FeatureService::addFeatureFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMessage;
    if(!NetworkUtils::checkError(reply, errorMessage)){
        emit errorOcurred("Feature Service - Add Feature: " + errorMessage);
        reply->deleteLater();
        return;
    }

    Feature feature = handleAddFeature(reply->readAll());
    emit featureCreated(feature);
    reply->deleteLater();
}

void FeatureService::deleteFeatureFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMessage;
    if(!NetworkUtils::checkError(reply, errorMessage)){
        emit errorOcurred("Feature Service - Delete Feature: " + errorMessage);
        reply->deleteLater();
        return;
    }

    emit featureDeleted();
    reply->deleteLater();
}

//------ Reply Handlers ------

Feature FeatureService::handleAddFeature(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isObject()) return Feature();

    QJsonObject obj = doc.object();
    int id = obj["id"].toInt();
    int projectId = obj["id_project"].toInt();
    QString feat = obj["feat"].toString();

    return Feature(id, projectId, feat);
}
