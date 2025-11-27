#ifndef TECHNOLOGYSERVICE_H
#define TECHNOLOGYSERVICE_H

#include <QObject>
#include <QHttpMultiPart>
#include "apiclient.h"
#include "technology.h"

class TechnologyService : public QObject
{
    Q_OBJECT
public:
    TechnologyService(ApiClient *apiClient);

    void addTechnology(const Technology &tech);
    void getTechIcon(int techId, const QString &path);
    void getTechnologies();
    void deleteTechnology(int techId);

signals:
    void technologiesReceipt(const QVector<Technology>& technologies);
    void techIconReceipt(int techId, const QPixmap &pixmap);
    void techCreated(int techId);
    void techDeleted(int techId);
    void errorOcurred(const QString &message);

private slots:
    void getTechnologiesFinished();
    void getTechIconFinished();
    void addTechnologyFinished();
    void deleteTechnologyFinished();

private:
    ApiClient* apiClient;

    //------ Request Handlers ------
    void handleGetTechnologies(const QByteArray &data, QVector<Technology>& container);
    int handleAddTechnology(const QByteArray &data);

    //------ Helpers ------
    QHttpMultiPart* makeTechnologyMultiPart(const QString &name, const QString &techIconPath);
};

#endif // TECHNOLOGYSERVICE_H
