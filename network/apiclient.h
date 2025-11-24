#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <basicrequests.h>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    ApiClient(QObject *parent = nullptr);

    //------ Requests ------
    QNetworkReply* login(const QByteArray &body);
    QNetworkReply* getPortfolio();
    QNetworkReply* getPhoto(const QString &path);

    //------ Setters ------
    void setHostName(const QString &hostName);
    void setLoginEndpoint(const QString &loginEndpoint);
    void setPortfolioEndpoint(const QString &portfolioEndpoint);
    void setPhotoEndpoint(const QString &photoEndpoint);
    void setAccessToken(const QString &accesstoken);
    void setRefreshToken(const QString &refreshToken);

private:
    BasicRequests *basicRequests;
    QString hostName;
    QString accessToken;
    QString refreshToken;

    //------ Endpoints ------
    QString loginEndpoint;
    QString portfolioEndpoint;
    QString photoEndpoint;
};

#endif // APICLIENT_H
