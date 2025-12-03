#include "technicalinfoservice.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "networkutils.h"

TechnicalInfoService::TechnicalInfoService(ApiClient *apiClient, QObject *parent)
    : QObject(parent), apiClient(apiClient)
{

}

//------ Public Methods ------

void TechnicalInfoService::addTechnicalInfo(int projectId, const QString &info)
{
    QJsonObject obj;
    obj["id_project"] = projectId;
    obj["info"] = info;

    QNetworkReply *reply = apiClient->postTechnicalInfo(QJsonDocument(obj).toJson());
    if(!reply){
        emit errorOcurred("TechnicalInfoService - AddTechnicalInfo: Reply Null. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &TechnicalInfoService::addTechnicalInfoFinished);
}

void TechnicalInfoService::deleteTechnicalInfo(int infoId)
{
    QNetworkReply *reply = apiClient->deleteTechnicalInfo(infoId);
    if(!reply){
        emit errorOcurred("TechnicalInfoService - DeleteTechnicalInfo: Reply Null. Not Sended");
        return;
    }

    reply->setProperty("infoId", infoId);
    connect(reply, &QNetworkReply::finished, this, &TechnicalInfoService::deleteTechnicalInfoFinished);
}

//------ Private Slots ------

void TechnicalInfoService::addTechnicalInfoFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMessage;
    if(!NetworkUtils::checkError(reply, errorMessage)){
        emit errorOcurred("TechnicalInfoService - AddTechnicalInfo: " + errorMessage);
        reply->deleteLater();
        return;
    }

    TechnicalInfo info = handleAddTechnicalInfo(reply->readAll());
    emit technicalInfoAdded(info);
    reply->deleteLater();
}

void TechnicalInfoService::deleteTechnicalInfoFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMessage;
    if(!NetworkUtils::checkError(reply, errorMessage)){
        emit errorOcurred("TechnicalInfoService - DeleteTechnicalInfo: " + errorMessage);
        reply->deleteLater();
        return;
    }

    int deletedId = reply->property("infoId").toInt();
    emit infoDeleted(deletedId);
    reply->deleteLater();
}

TechnicalInfo TechnicalInfoService::handleAddTechnicalInfo(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isObject()) return TechnicalInfo();

    QJsonObject obj = doc.object();
    int id = obj["id"].toInt();
    int projectId = obj["id_project"].toInt();
    QString info = obj["info"].toString();

    return TechnicalInfo(id, projectId, info);
}
