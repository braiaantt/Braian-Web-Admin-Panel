#include "entityimageservice.h"
#include "networkutils.h"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "QJsonValue"
#include "QPixmap"
#include "QFile"

EntityImageService::EntityImageService(ApiClient *apiClient, QObject *parent)
    : QObject(parent), apiClient(apiClient)
{

}

//------- Public Methods ------

void EntityImageService::addImage(int entityId, const QString &entityType, const QString &imgPath)
{
    QHttpMultiPart *multiPart = makeAddImageMultiPart(entityId, entityType, imgPath);
    QNetworkReply *reply = apiClient->postEntityImage(multiPart);
    if(!reply){
        emit errorOcurred("EntityImageService - AddImage: Reply Null. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &EntityImageService::addImageFinished);
}

void EntityImageService::getImagePaths(int entityId, const QString &entityType)
{
    QString queryParams = QString("?entity_id=%1&entity_type=%2").
                          arg(entityId).
                          arg(entityType);

    QNetworkReply *reply = apiClient->getEntityImagePaths(queryParams);
    if(!reply){
        emit errorOcurred("EntityImageService - GetImagePaths: Reply Null. Not Sended.");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &EntityImageService::getImagePathsFinished);
}

void EntityImageService::getImage(const QString &path)
{
    QNetworkReply *reply = apiClient->getImage(path);
    if(!reply){
        emit errorOcurred("EntityImageService - GetImage: Reply Null. Not Sended");
        return;
    }

    reply->setProperty("imgPath", path);
    connect(reply, &QNetworkReply::finished, this, &EntityImageService::getImageFinished);
}

void EntityImageService::deleteImage(int entityId, const QString &entityType, const QString &sourcePath)
{
    QString queryParams = QString("?entity_id=%1&entity_type=%2&img_path=%3")
                              .arg(QString::number(entityId), entityType, sourcePath);

    QNetworkReply *reply = apiClient->deleteEntityImage(queryParams);
    if(!reply){
        emit errorOcurred("EntityImageService - deleteImage: Reply Null. Not Sended.");
        return;
    }
    connect(reply, &QNetworkReply::finished, this, &EntityImageService::deleteImageFinished);
}

//------ Private Slots ------

void EntityImageService::addImageFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("EntityImageService - AddImage: " + errorMsg);
        reply->deleteLater();
        return;
    }
    QString imgPath = QString::fromUtf8(reply->readAll());
    emit imageCreated(imgPath);
    reply->deleteLater();
}

void EntityImageService::getImagePathsFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("EntityImageService - GetImagePaths: " + errorMsg);
        reply->deleteLater();
        return;
    }

    QVector<QString> paths = handleGetImagePaths(reply->readAll());
    emit pathsReceipt(paths);
    reply->deleteLater();
}

void EntityImageService::getImageFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("EntityImageService - GetImage: " + errorMsg);
        reply->deleteLater();
        return;
    }

    QString imgPath = reply->property("imgPath").toString();
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());

    emit imageReceipt(imgPath, pixmap);
    reply->deleteLater();
}

void EntityImageService::deleteImageFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("EntityImageService - DeleteImage: " + errorMsg);
        reply->deleteLater();
        return;
    }

    emit deleteImageSuccess();
    reply->deleteLater();
}

//------ Reply Handlers ------

QVector<QString> EntityImageService::handleGetImagePaths(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isArray()) return {};

    QJsonArray array = doc.array();
    QVector<QString> paths;

    for(const QJsonValue &value : std::as_const(array)){
        if(!value.isString())
            continue;

        paths.append(value.toString());
    }

    return paths;
}

//------ Helpers ------

QHttpMultiPart* EntityImageService::makeAddImageMultiPart(int entityId, const QString &entityType, const QString &imgPath)
{
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //-- Json Part --
    QString json = dataToStrJson(entityId, entityType);
    QHttpPart jsonPart;
    jsonPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"json\""));
    jsonPart.setBody(json.toUtf8());

    //-- File part --
    QFile *file = new QFile(imgPath);
    file->open(QIODevice::ReadOnly);

    QHttpPart filePart;
    filePart.setHeader(
        QNetworkRequest::ContentDispositionHeader,
        QVariant("form-data; name=\"file\"; filename=\"" + file->fileName() +"\"")
        );
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/*");
    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    //-- Appends --
    multiPart->append(jsonPart);
    multiPart->append(filePart);

    return multiPart;
}

QString EntityImageService::dataToStrJson(int entityId, const QString &entityType)
{
    QJsonObject obj;
    obj["entity_id"] = entityId;
    obj["entity_type"] = entityType;

    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson());
}
