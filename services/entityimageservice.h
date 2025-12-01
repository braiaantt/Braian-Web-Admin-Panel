#ifndef ENTITYIMAGESERVICE_H
#define ENTITYIMAGESERVICE_H

#include <QObject>
#include "apiclient.h"
#include <QHttpMultiPart>

class EntityImageService : public QObject
{
    Q_OBJECT
public:
    explicit EntityImageService(ApiClient *apiClient, QObject *parent = nullptr);

    void addImage(int entityId, const QString &entityType, const QString &pathImage);
    void getImagePaths(int entityId, const QString &entityType);
    void getImage(const QString &path);
    void deleteImage(int entityId, const QString &entityType, const QString &sourcePath);

signals:
    void imageCreated(const QString &imgPath);
    void pathsReceipt(const QVector<QString>& paths);
    void imageReceipt(const QString &imgPath, const QPixmap &pixmap);
    void deleteImageSuccess();
    void errorOcurred(const QString &message);

private slots:
    void addImageFinished();
    void getImagePathsFinished();
    void getImageFinished();
    void deleteImageFinished();

private:
    ApiClient *apiClient;

    //------ Reply handlers ------
    QVector<QString> handleGetImagePaths(const QByteArray &data);

    //------ Helpers ------
    QHttpMultiPart* makeAddImageMultiPart(int entityId, const QString &entityType, const QString &pathImage);
    QString dataToStrJson(int entityId, const QString &entityType);
};

#endif // ENTITYIMAGESERVICE_H
