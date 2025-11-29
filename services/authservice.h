#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QNetworkReply>
#include "apiclient.h"

class AuthService : public QObject
{
    Q_OBJECT

public:
    AuthService(ApiClient *apiClient, QObject *parent = nullptr);

    void login(const QString &email, const QString &password);

private slots:
    void loginFinished();

signals:
    void loginSuccess();
    void error(const QString &message);

private:
    ApiClient *apiClient;

    //------ Request Handlers ------
    void handleLoginFinished(const QByteArray &data);

};

#endif // AUTHSERVICE_H
