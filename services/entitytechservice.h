#ifndef ENTITYTECHSERVICE_H
#define ENTITYTECHSERVICE_H

#include <QObject>
#include "apiclient.h"
#include "technology.h"

class EntityTechService : public QObject
{
    Q_OBJECT
public:
    EntityTechService(ApiClient *apiClient);

    void addRelation(int entityId, const QString &entityType, int techId);
    void removeRelation(int entityId, const QString &entityType, int techId);
    void getRelations(int entityId, const QString &entityType);

private slots:
    void addRelationFinished();
    void removeRelationFinished();
    void getRelationsFinished();

signals:
    void commitSuccess();
    void errorOcurred(const QString &message);
    void technologiesRelated(const QVector<Technology> &techsRelated);

private:
    ApiClient *apiClient;

    //------ Reply Handlers ------
    void handleGetRelationsFinished(QVector<Technology> &container, const QByteArray &data);
};

#endif // ENTITYTECHSERVICE_H
