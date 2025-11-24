#include "networkutils.h"
#include <QJsonDocument>
#include <QJsonObject>

bool NetworkUtils::checkError(QNetworkReply *reply, QString &errorMsg)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(reply->error() != QNetworkReply::NoError){
        errorMsg = reply->errorString();
        return false;
    }

    if(status >= 200 && status < 300)
        return true;

    QByteArray response = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);

    if(doc.isObject() && doc.object().contains("detail")){
        errorMsg = doc.object().value("detail").toString();
    } else {
        errorMsg = QString("HTTP %1 Error").arg(status);
    }

    return false;
}
