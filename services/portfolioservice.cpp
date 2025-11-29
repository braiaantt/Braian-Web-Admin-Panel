#include "portfolioservice.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QPixmap>
#include "networkutils.h"

PortfolioService::PortfolioService(ApiClient *apiClient, QObject *parent) :
    QObject(parent)
    , apiClient(apiClient)
{
    //Important delete reply after finished, autoDeleteReply desactivated at ApiClient initialization
}

void PortfolioService::getPortfolio()
{
    QNetworkReply *reply = apiClient->getPortfolio();
    if(!reply){
        emit errorOcurred("PortfolioService - GetPortfolio: Null Reply. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &PortfolioService::getPortfolioFinished);
}

void PortfolioService::getUserPhoto(const QString &path)
{
    QNetworkReply *reply = apiClient->getImage(path);
    if(!reply){
        emit errorOcurred("PortfolioService - GetPhoto: Null Reply. Not Sended");
        return;
    }

    connect(reply, &QNetworkReply::finished, this, &PortfolioService::getUserPhotoFinished);
}

//------ Private Slots ------

void PortfolioService::getPortfolioFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if(!reply){
        emit errorOcurred("PortfolioService - GetPortfolio: Null Reply");
        return;
    }

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("PortfolioService - GetPortfolio: " + errorMsg);
        reply->deleteLater();
        return;
    }

    Portfolio portfolio = handlePortfolioFinished(reply->readAll());
    getUserPhoto(portfolio.getUserPhotoPath());
    emit portfolioReceipt(portfolio);

    reply->deleteLater();
}

void PortfolioService::getUserPhotoFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply){
        emit errorOcurred("PortfolioService - GetPhoto: Null Reply");
        return;
    }

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("PortfolioService - GetPhoto: " + errorMsg);
        reply->deleteLater();
        return;
    }

    QPixmap photo;
    photo.loadFromData(reply->readAll());
    emit userPhotoReceipt(photo);

    reply->deleteLater();
}

//------ Request Handlers ------

Portfolio PortfolioService::handlePortfolioFinished(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject obj = jsonDoc.object();
    QJsonObject jsonPortfolio = obj["data"].toObject();

    Portfolio portfolio;
    portfolio.setUserName(jsonPortfolio["user_name"].toString());
    portfolio.setUserProfession(jsonPortfolio["user_profession"].toString());
    portfolio.setUserPhotoPath(jsonPortfolio["user_photo"].toString());
    portfolio.setUserAbout(jsonPortfolio["user_about"].toString());
    portfolio.setTechnologies(getTechnologiesFromArray(jsonPortfolio["techs"].toArray()));

    return portfolio;
}

//------ Helpers ------

QVector<Technology> PortfolioService::getTechnologiesFromArray(const QJsonArray &array)
{
    QVector<Technology> techs;

    for(const QJsonValue &value : array){
        if(!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        int techId = obj["id"].toInt();
        QString name = obj["name"].toString();
        QString iconSrc = obj["icon_src"].toString();

        Technology tech(techId, name, iconSrc);
        techs.append(tech);

    }

    return techs;
}
