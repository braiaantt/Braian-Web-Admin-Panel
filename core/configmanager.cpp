#include "configmanager.h"
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

QString ConfigManager::endpointLogin() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("login").toString();
}

QString ConfigManager::endpointPortfolio() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("portfolio").toString();
}

QString ConfigManager::endpointTechnology() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("technology").toString();
}

QString ConfigManager::endpointEntityTechnology() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("entityTechnology").toString();
}

QString ConfigManager::endpointProjectImage() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("projectImages").toString();
}

QString ConfigManager::endpointProject() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("project").toString();
}

QString ConfigManager::endpointFeatures() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("features").toString();
}

QString ConfigManager::endpointTechnicalInfo() const
{
    const QJsonObject routesObj = api.value("endpoints").toObject();
    return routesObj.value("technicalInfo").toString();
}

//------ Persistent settings ------

QSettings& ConfigManager::settings()
{
    static QSettings settings("Braian", "webAdminPanel");
    return settings;
}

void ConfigManager::setRefreshToken(const QString &token)
{
    settings().setValue("auth/refreshToken", token);
}

QString ConfigManager::refreshToken()
{
    return settings().value("auth/refreshToken").toString();
}
