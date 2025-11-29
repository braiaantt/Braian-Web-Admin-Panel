#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <basicrequests.h>
#include <QHttpMultiPart>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    ApiClient(QObject *parent = nullptr);

    //------ Requests ------
    //-- Auth --
    QNetworkReply* login(const QByteArray &body);

    //-- Portfolio --
    QNetworkReply* getPortfolio();

    //-- Technology --
    QNetworkReply* postTechnology(QHttpMultiPart *multipart);
    QNetworkReply* getTechnologies();
    QNetworkReply* deleteTechnology(int techId);

    //-- Entity Technology --
    QNetworkReply* addTechRelation(const QByteArray &body);
    QNetworkReply* removeTechRelation(const QString &queryParams);
    QNetworkReply* getRelations(const QString &queryParams);

    //-- Files --
    QNetworkReply* getImage(const QString &path);

    //------ Setters ------
    void setHostName(const QString &hostName);
    void setLoginEndpoint(const QString &loginEndpoint);
    void setPortfolioEndpoint(const QString &portfolioEndpoint);
    void setImageEndpoint(const QString &photoEndpoint);
    void setTechnologyEndpoint(const QString &technologyEndpoint);
    void setEntityTechnologyEndpoint(const QString &entityTechnologyEndpoint);
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
    QString technologyEndpoint;
    QString imageEndpoint;
    QString entityTechnologyEndpoint;
};

#endif // APICLIENT_H
