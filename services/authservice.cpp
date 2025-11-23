#include "authservice.h"
#include <QJsonObject>
#include "configmanager.h"

AuthService::AuthService(ApiClient *apiClient):
    apiClient(apiClient)
{
    //Important delete reply after finished, autoDeleteReply desactivated at ApiClient initialization
}

void AuthService::login(const QString &email, const QString &password)
{
    QJsonObject obj;
    obj["email"] = email;
    obj["password"] = password;

    QByteArray body = QJsonDocument(obj).toJson();
    QNetworkReply *reply = apiClient->login(body);

    if(!reply){
        emit error("Null Reply. Not sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &AuthService::loginFinished);
}

//------ Slots ------

void AuthService::loginFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply){
        emit error("Null Reply");
        return;
    }

    if(reply->error() == QNetworkReply::NoError){

        handleLoginFinished(reply->readAll());
        emit loginSuccess();
    } else {
        emit error(reply->errorString());
    }

    reply->deleteLater();
}

//------ Request Handlers ------

void AuthService::handleLoginFinished(const QByteArray &data)
{
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonObject obj = json.object();

    //set tokens to api
    QString refreshToken = obj["refresh_token"].toString();
    apiClient->setAccessToken(obj["access_token"].toString());
    apiClient->setRefreshToken(refreshToken);

    //save refresh token
    ConfigManager::setRefreshToken(refreshToken);
}
