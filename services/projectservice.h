#ifndef PROJECTSERVICE_H
#define PROJECTSERVICE_H

#include <QObject>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include "apiclient.h"
#include "project.h"

class ProjectService : public QObject
{
    Q_OBJECT
public:
    ProjectService(ApiClient *apiClient, QObject *parent = nullptr);

    void createProject(const Project &project);
    void getProjectCover(int projectId, const QString &coverSrc);

private slots:
    void createProjectFinished();
    void getProjectCoverFinished();

signals:
    void projectCreated(int projectId);
    void projectCoverReceipt(int projectId, const QPixmap &pixmap);
    void errorOcurred(const QString &message);

private:
    ApiClient *apiClient;

    //------ Helpers ------
    QHttpMultiPart* makeProjectMultiPart(const Project &project);
    QString projectToStrJson(const Project &project);

    //------ Reply Handlers ------
    int handleCreateProject(const QByteArray &data);

};

#endif // PROJECTSERVICE_H
