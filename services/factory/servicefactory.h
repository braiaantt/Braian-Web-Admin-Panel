#ifndef SERVICEFACTORY_H
#define SERVICEFACTORY_H

#include <QObject>
#include "apiclient.h"
#include "authservice.h"
#include "portfolioservice.h"
#include "technologyservice.h"
#include "entitytechservice.h"
#include "projectservice.h"
#include "entityimageservice.h"

class ServiceFactory
{
public:
    ServiceFactory();

    //------ Initialization ------
    bool init();

    //------ Make ------
    AuthService* makeAuthService(QObject *parent);
    PortfolioService* makePortfolioService(QObject *parent);
    TechnologyService* makeTechnologyService(QObject *parent);
    EntityTechService* makeEntityTechService(QObject *parent);
    ProjectService* makeProjectService(QObject *parent);
    EntityImageService* makeEntityImageService(QObject *parent);

private:
    ApiClient apiClient;
};

#endif // SERVICEFACTORY_H
