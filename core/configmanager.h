#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QJsonObject>
#include <QSettings>

class ConfigManager
{
public:
    static constexpr const char* CONFIG_FILE_NAME = "config.json";

    bool load();
    QString host() const;
    QString endpointLogin() const;
    QString endpointPortfolio() const;
    QString endpointTechnology() const;
    QString endpointImage() const;
    QString endpointEntityTechnology() const;
    QString endpointProject() const;

    //------ Persistent settings ------
    static QString refreshToken();
    static void setRefreshToken(const QString &token);

private:
    QJsonObject root;
    QJsonObject api;

    static QSettings& settings();
};

#endif // CONFIGMANAGER_H
