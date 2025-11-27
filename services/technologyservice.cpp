#include "technologyservice.h"
#include "networkutils.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include <QFile>

TechnologyService::TechnologyService(ApiClient *apiClient) :
    apiClient(apiClient)
{

}

void TechnologyService::addTechnology(const Technology &tech)
{
    QHttpMultiPart *multiPart = makeTechnologyMultiPart(tech.getName(), tech.getImgPath());
    QNetworkReply *reply = apiClient->postTechnology(multiPart);

    if(!reply){
        emit errorOcurred("TechnologyService - GetTechnologies: Reply Null. Not Sended.");
        multiPart->deleteLater();
        return;
    }

    multiPart->setParent(reply),
    connect(reply, &QNetworkReply::finished, this, &TechnologyService::addTechnologyFinished);
}

void TechnologyService::getTechnologies()
{
    QNetworkReply* reply = apiClient->getTechnologies();
    if(!reply){
        emit errorOcurred("TechnologyService - GetTechnologies: Reply Null. Not Sended.");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &TechnologyService::getTechnologiesFinished);
}

void TechnologyService::getTechIcon(int techId, const QString &path)
{
    QNetworkReply *reply = apiClient->getImage(path);
    if(!reply){
        emit errorOcurred("TechnologyService - GetTechIcon: Reply Null. Not Sended.");
        return;
    }
    reply->setProperty("techId", techId);

    connect(reply, &QNetworkReply::finished, this, &TechnologyService::getTechIconFinished);
}

//------ Private Slots ------

void TechnologyService::getTechnologiesFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("TechnologyService - GetTechnologies: " + errorMsg);
        reply->deleteLater();
        return;
    }

    QVector<Technology> techs;
    handleGetTechnologies(reply->readAll(), techs);

    emit technologiesReceipt(techs);
    reply->deleteLater();
}

void TechnologyService::getTechIconFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("TechnologyService - GetTechIcon: " + errorMsg);
        reply->deleteLater();
        return;
    }

    int techId = reply->property("techId").toInt();
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());

    emit techIconReceipt(techId, pixmap);
    reply->deleteLater();
}

void TechnologyService::addTechnologyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("TechnologyService - AddTechnology: " + errorMsg);
        reply->deleteLater();
        return;
    }

    int techId = handleAddTechnology(reply->readAll());
    emit techCreated(techId);
    reply->deleteLater();
}

//------ Request Handlers ------

void TechnologyService::handleGetTechnologies(const QByteArray &data, QVector<Technology> &container)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if(!doc.isObject())
        return;

    QJsonObject obj = doc.object();

    if(!obj.contains("data") || !obj["data"].isArray())
        return;

    QJsonArray techs = obj["data"].toArray();

    for(const QJsonValue &techVal : std::as_const(techs)){
        if(!techVal.isObject())
            continue;

        QJsonObject techObj = techVal.toObject();
        int id = techObj.value("id").toInt();
        QString name = techObj.value("name").toString();
        QString iconSrc = techObj.value("icon_src").toString();
        Technology tech(id, name, iconSrc);

        container.append(tech);
    }
}

int TechnologyService::handleAddTechnology(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
        return -1;

    QJsonObject root = doc.object();
    if (!root.contains("data") || !root["data"].isObject())
        return -1;

    QJsonObject techObj = root["data"].toObject();
    if (!techObj.contains("id"))
        return -1;

    return techObj["id"].toInt();
}

//------ Helpers ------

QHttpMultiPart* TechnologyService::makeTechnologyMultiPart(const QString &name, const QString &techIconPath)
{
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //-- Name Part --
    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"name\""));
    namePart.setBody(name.toUtf8());

    //-- Icon Part --
    QFile* file = new QFile(techIconPath);
    file->open(QIODevice::ReadOnly);

    QHttpPart filePart;
    filePart.setHeader(
        QNetworkRequest::ContentDispositionHeader,
        QVariant("form-data; name=\"file\"; filename=\"" + file->fileName().toUtf8() + "\"")
        );
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/*");
    filePart.setBodyDevice(file);

    //-- Appends --
    multiPart->append(namePart);
    multiPart->append(filePart);

    return multiPart;
}
