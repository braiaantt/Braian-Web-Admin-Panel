#include "ConfigManager.h"
#include <QDir>
#include <QCoreApplication>
#include <CommonUtils/fileutils.h>
#include <CommonUtils/jsonutils.h>

bool ConfigManager::load()
{
    QString path = QDir(QCoreApplication::applicationDirPath()).filePath(CONFIG_FILE_NAME);
    QByteArray bytes = FileUtils::readFile(path);

    if(bytes.isEmpty() || !JsonUtils::isValid(bytes))
        return false;

    root = QJsonDocument::fromJson(bytes).object();
    api = root.value("api").toObject();
    return true;
}

QString ConfigManager::host() const
{
    return api.value("hostName").toString();
}

QString ConfigManager::routeLogin() const
{
    const QJsonObject routesObj = api.value("routes").toObject();
    return routesObj.value("login").toString();
}

