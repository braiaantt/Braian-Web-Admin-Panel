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

    return basicRequests->post(loginEndpoint, body, headers);
}

QNetworkReply* ApiClient::getPortfolio()
{
    return basicRequests->get(portfolioEndpoint);
}

QNetworkReply* ApiClient::getPhoto(const QString &path)
{
    return basicRequests->get(photoEndpoint + "/" + path);
}

//------ Setters ------

void ApiClient::setHostName(const QString &_hostName)
{
    hostName = _hostName;
    basicRequests->setHostName(_hostName);
}

void ApiClient::setLoginEndpoint(const QString &endpoint){
    loginEndpoint= endpoint;
}

void ApiClient::setPortfolioEndpoint(const QString &endpoint)
{
    portfolioEndpoint = endpoint;
}

void ApiClient::setPhotoEndpoint(const QString &endpoint)
{
    photoEndpoint = endpoint;
}

void ApiClient::setAccessToken(const QString &token){
    accessToken = token;
}

void ApiClient::setRefreshToken(const QString &token){
    refreshToken = token;
}
