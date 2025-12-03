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

void EntityImageService::addImage(int projectId, const QString &imgPath)
{
    QHttpMultiPart *multiPart = makeAddImageMultiPart(projectId, imgPath);
    QNetworkReply *reply = apiClient->postProjectImage(multiPart);
    if(!reply){
        emit errorOcurred("ProjectImageService - AddImage: Reply Null. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &EntityImageService::addImageFinished);
}

void EntityImageService::getImage(const QString &path)
{
    QNetworkReply *reply = apiClient->getImage(path);
    if(!reply){
        emit errorOcurred("ProjectImageService - GetImage: Reply Null. Not Sended");
        return;
    }

    reply->setProperty("imgPath", path);
    connect(reply, &QNetworkReply::finished, this, &EntityImageService::getImageFinished);
}

void EntityImageService::deleteImage(int projectId, const QString &sourcePath)
{
    QString queryParams = QString("?id_project=%1&src=%2")
                              .arg(QString::number(projectId), sourcePath);

    QNetworkReply *reply = apiClient->deleteProjectImage(queryParams);
    if(!reply){
        emit errorOcurred("ProjectImageService - DeleteImage: Reply Null. Not Sended.");
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

//------ Helpers ------

QHttpMultiPart* EntityImageService::makeAddImageMultiPart(int projectId, const QString &imgPath)
{
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //-- Project Id Part --
    QHttpPart jsonPart;
    jsonPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"project_id\""));
    jsonPart.setBody(QString::number(projectId).toUtf8());

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
