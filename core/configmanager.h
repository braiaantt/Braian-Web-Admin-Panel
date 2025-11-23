#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QJsonObject>

class ConfigManager
{
public:
    static constexpr const char* CONFIG_FILE_NAME = "config.json";

    bool load();
    QString host() const;
    QString routeLogin() const;

private:
    QJsonObject root;
    QJsonObject api;
};

#endif // CONFIGMANAGER_H
