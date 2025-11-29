#include "projectservice.h"
#include <QJsonObject>
#include <QFile>
#include <QPixmap>
#include "networkutils.h"

ProjectService::ProjectService(ApiClient *apiClient, QObject *parent)
    : QObject(parent)
    , apiClient(apiClient)
{

}

void ProjectService::createProject(const Project &project)
{
    QHttpMultiPart *multiPart = makeProjectMultiPart(project);
    QNetworkReply *reply = apiClient->postProject(multiPart);

    if(!reply){
        emit errorOcurred("ProjectService - CreateProject: Reply Null. Not Sended.");
        multiPart->deleteLater();
        return;
    }

    multiPart->setParent(reply);
    connect(reply, &QNetworkReply::finished, this, &ProjectService::createProjectFinished);
}

void ProjectService::getProjectCover(int projectId, const QString &coverSrc)
{
    QNetworkReply *reply = apiClient->getImage(coverSrc);

    if(!reply){
        emit errorOcurred("ProjectService - CreateProject: Reply Null. Not Sended.");
        return;
    }

    reply->setProperty("projectId", projectId);
    connect(reply, &QNetworkReply::finished, this, &ProjectService::getProjectCoverFinished);
}

//------ Private Slots ------

void ProjectService::createProjectFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("ProjectService - AddProject: " + errorMsg);
        reply->deleteLater();
        return;
    }

    int projectId = handleCreateProject(reply->readAll());
    emit projectCreated(projectId);

    reply->deleteLater();
}

void ProjectService::getProjectCoverFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QString errorMsg;
    if(!NetworkUtils::checkError(reply, errorMsg)){
        emit errorOcurred("ProjectService - GetProjectCover: " + errorMsg);
        reply->deleteLater();
        return;
    }

    int projectId = reply->property("projectId").toInt();
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());

    emit projectCoverReceipt(projectId, pixmap);

    reply->deleteLater();
}

//------ Reply Handlers ------

int ProjectService::handleCreateProject(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isObject()) return -1;

    QJsonObject obj = doc.object();
    if(!obj.contains("id")) return -1;

    return obj["id"].toInt();
}

//------ Helpers ------

QHttpMultiPart* ProjectService::makeProjectMultiPart(const Project &project)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //-- JSON part --
    QHttpPart jsonPart;
    jsonPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"project\""));
    jsonPart.setBody(projectToStrJson(project).toUtf8());

    //-- File part --
    QFile *file = new QFile(project.getCoverPath());
    file->open(QIODevice::ReadOnly);

    QHttpPart filePart;
    filePart.setHeader(
        QNetworkRequest::ContentDispositionHeader,
        QVariant("form-data; name=\"file\"; filename=\"" + file->fileName() +"\"")
        );
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/*");
    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    //-- Appends --
    multiPart->append(jsonPart);
    multiPart->append(filePart);

    return multiPart;
}

QString ProjectService::projectToStrJson(const Project &project)
{
    QJsonObject obj;
    obj["name"] = project.getName();
    obj["small_about"] = project.getSmallAbout();
    obj["big_about"] = project.getBigAbout();
    obj["user_comment"] = project.getUserComments();

    QJsonDocument doc(obj);
    QString projectJson = QString::fromUtf8(doc.toJson());
    return projectJson;
}
