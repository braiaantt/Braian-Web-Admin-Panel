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

    //------ Setters ------
    void setHostName(const QString &hostName);
    void setLoginRoute(const QString &loginRoute);
    void setAccessToken(const QString &accesstoken);
    void setRefreshToken(const QString &refreshToken);

private:
    BasicRequests *basicRequests;
    QString hostName;
    QString accessToken;
    QString refreshToken;

    //------ Routes ------
    QString loginRoute;

};

#endif // APICLIENT_H
