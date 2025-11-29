#include "entitytechservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "networkutils.h"

EntityTechService::EntityTechService(ApiClient *apiClient) :
    apiClient(apiClient)
{

}

//------ Public Methods ------

void EntityTechService::addRelation(int entityId, const QString &entityType, int techId)
{
    QJsonObject data;
    data["id_entity"] = entityId;
    data["type_entity"] = entityType;
    data["id_tech"] = techId;

    QByteArray body = QJsonDocument(data).toJson();
    QNetworkReply *reply = apiClient->addTechRelation(body);

    if(!reply){
        emit errorOcurred("EntityTechService - AddRelation: Null Reply. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &EntityTechService::addRelationFinished);
}

void EntityTechService::removeRelation(int entityId, const QString &entityType, int techId)
{
    QString queryParams = QString("?id_entity=%1&type_entity=%2&id_tech=%3")
                              .arg(entityId)
                              .arg(entityType)
                              .arg(techId);

    QNetworkReply *reply = apiClient->removeTechRelation(queryParams);
    if(!reply){
        emit errorOcurred("EntityTechService - RemoveRelation: Null Reply. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &EntityTechService::removeRelationFinished);
}

void EntityTechService::getRelations(int entityId, const QString &entityType)
{
    QString queryParams = QString("?id_entity=%1&type_entity=%2")
                              .arg(entityId)
                              .arg(entityType);
    QNetworkReply *reply = apiClient->getRelations(queryParams);
    if(!reply){
        emit errorOcurred("EntityTechService - GetRelations: Null Reply. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &EntityTechService::getRelationsFinished);
}

//------ Private Slots ------

void EntityTechService::addRelationFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("EntityTechnology - AddRelation: " + errorMsg);
        reply->deleteLater();
        return;
    }

    emit commitSuccess();
    reply->deleteLater();
}

void EntityTechService::removeRelationFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("EntityTechnology - RemoveRelation: " + errorMsg);
        reply->deleteLater();
        return;
    }

    emit commitSuccess();
    reply->deleteLater();
}

void EntityTechService::getRelationsFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("EntityTechnology - GetRelations: " + errorMsg);
        reply->deleteLater();
        return;
    }

    QVector<Technology> techsRelated;
    handleGetRelationsFinished(techsRelated, reply->readAll());

    emit technologiesRelated(techsRelated);
    reply->deleteLater();
}

//------ Reply Handlers ------

void EntityTechService::handleGetRelationsFinished(QVector<Technology> &container, const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isArray()) return;

    QJsonArray array = doc.array();
    for(const QJsonValue &value : std::as_const(array)){
        if(!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        int techId = obj["id"].toInt();
        QString techName = obj["name"].toString();
        QString iconSrc = obj["icon_src"].toString();

        Technology tech(techId, techName, iconSrc);
        container.append(tech);
    }
}
