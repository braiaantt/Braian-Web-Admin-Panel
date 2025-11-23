#include "apiclient.h"

ApiClient::ApiClient(QObject *parent) :
    QObject(parent),
    basicRequests(new BasicRequests(this))
{
    basicRequests->setAutoDeleteReply(false); // Configure BasicRequest for let us handle reply delete
}

//------ Requests ------

QNetworkReply* ApiClient::login(const QByteArray &body)
{
    QMap<QByteArray,QByteArray> headers;
    headers.insert("Content-Type", "application/json");

    return basicRequests->post(loginRoute, body, headers);
}
//------ Setters ------

void ApiClient::setHostName(const QString &_hostName)
{
    hostName = _hostName;
    basicRequests->setHostName(_hostName);
}

void ApiClient::setLoginRoute(const QString &route){
    loginRoute = route;
}

void ApiClient::setAccessToken(const QString &token){
    accessToken = token;
}

void ApiClient::setRefreshToken(const QString &token){
    refreshToken = token;
}
