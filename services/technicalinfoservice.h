#ifndef TECHNICALINFOSERVICE_H
#define TECHNICALINFOSERVICE_H

#include <QObject>
#include "apiclient.h"
#include "technicalinfo.h"

class TechnicalInfoService : public QObject
{
    Q_OBJECT
public:
    explicit TechnicalInfoService(ApiClient *apiClient, QObject *parent = nullptr);

    void addTechnicalInfo(int projectId, const QString &info);
    void deleteTechnicalInfo(int infoId);

private slots:
    void addTechnicalInfoFinished();
    void deleteTechnicalInfoFinished();

signals:
    void technicalInfoAdded(const TechnicalInfo &technicalInfo);
    void infoDeleted(int deletedId);
    void errorOcurred(const QString &message);

private:
    ApiClient *apiClient;

    //------ Reply Handlers ------
    TechnicalInfo handleAddTechnicalInfo(const QByteArray &data);
};

#endif // TECHNICALINFOSERVICE_H
