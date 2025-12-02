#include "servicefactory.h"
#include "configmanager.h"

ServiceFactory::ServiceFactory() {}

//------ Initialization ------

bool ServiceFactory::init()
{
    ConfigManager config;
    if(!config.load()) return false;

    apiClient.setHostName(config.host());
    apiClient.setLoginEndpoint(config.endpointLogin());
    apiClient.setPortfolioEndpoint(config.endpointPortfolio());
    apiClient.setTechnologyEndpoint(config.endpointTechnology());
    apiClient.setEntityTechnologyEndpoint(config.endpointEntityTechnology());
    apiClient.setEntityImageEndpoint(config.endpointEntityImage());
    apiClient.setProjectEndpoint(config.endpointProject());

    return true;
}

//------ Make ------

AuthService* ServiceFactory::makeAuthService(QObject *parent)
{
    return new AuthService(&apiClient, parent);
}

PortfolioService* ServiceFactory::makePortfolioService(QObject *parent)
{
    return new PortfolioService(&apiClient, parent);
}

TechnologyService* ServiceFactory::makeTechnologyService(QObject *parent)
{
    return new TechnologyService(&apiClient, parent);
}

EntityTechService* ServiceFactory::makeEntityTechService(QObject *parent)
{
    return new EntityTechService(&apiClient, parent);
}

ProjectService *ServiceFactory::makeProjectService(QObject *parent)
{
    return new ProjectService(&apiClient, parent);
}

EntityImageService *ServiceFactory::makeEntityImageService(QObject *parent)
{
    return new EntityImageService(&apiClient, parent);
}
