#ifndef PORTFOLIOSERVICE_H
#define PORTFOLIOSERVICE_H

#include <QObject>
#include "apiclient.h"
#include "portfolio.h"

class PortfolioService : public QObject
{
    Q_OBJECT
public:
    PortfolioService(ApiClient *apiClient);

    void getPortfolio();

signals:
    void portfolioReceipt(const Portfolio &portfolio);
    void userPhotoReceipt(const QPixmap& photo);
    void errorOcurred(const QString &message);

private slots:
    void getPortfolioFinished();
    void getUserPhotoFinished();

private:
    ApiClient *apiClient;

    //------ Methods ------
    void getUserPhoto(const QString &path);

    //------ Request Handlers ------
    Portfolio handlePortfolioFinished(const QByteArray &data);

};

#endif // PORTFOLIOSERVICE_H
