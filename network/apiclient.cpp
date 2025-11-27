#include "apiclient.h"

ApiClient::ApiClient(QObject *parent) :
    QObject(parent),
    basicRequests(new BasicRequests(this))
{
    basicRequests->setAutoDeleteReply(false); // Configure BasicRequest for let us handle reply delete
}

//------ Requests ------
//-- Auth --
QNetworkReply* ApiClient::login(const QByteArray &body)
{
    QMap<QByteArray,QByteArray> headers;
    headers.insert("Content-Type", "application/json");

    return basicRequests->post(loginEndpoint, body, headers);
}

//-- Portfolio --
QNetworkReply* ApiClient::getPortfolio()
{
    return basicRequests->get(portfolioEndpoint);
}

//-- Technology --

QNetworkReply* ApiClient::postTechnology(QHttpMultiPart *multiPart)
{
    QMap<QByteArray,QByteArray> headers;
    headers.insert("Authorization", ("Bearer " + accessToken).toUtf8());

    return basicRequests->postMultipart(technologyEndpoint, multiPart, headers);
}

QNetworkReply* ApiClient::getTechnologies()
{
    QMap<QByteArray,QByteArray> headers;
    headers.insert("Authorization", ("Bearer " + accessToken).toUtf8());
    return basicRequests->get(technologyEndpoint, headers);
}

//-- Files --

QNetworkReply* ApiClient::getImage(const QString &path)
{
    return basicRequests->get(imageEndpoint + path);
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

void ApiClient::setImageEndpoint(const QString &endpoint)
{
    imageEndpoint = endpoint;
}

void ApiClient::setTechnologyEndpoint(const QString &endpoint)
{
    technologyEndpoint = endpoint;
}

void ApiClient::setAccessToken(const QString &token){
    accessToken = token;
}

void ApiClient::setRefreshToken(const QString &token){
    refreshToken = token;
}
