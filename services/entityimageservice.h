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

    void addImage(int projectId, const QString &pathImage);
    void getImage(const QString &path);
    void deleteImage(int projectId, const QString &sourcePath);

signals:
    void imageCreated(const QString &imgPath);
    void imageReceipt(const QString &imgPath, const QPixmap &pixmap);
    void deleteImageSuccess();
    void errorOcurred(const QString &message);

private slots:
    void addImageFinished();
    void getImageFinished();
    void deleteImageFinished();

private:
    ApiClient *apiClient;

    //------ Helpers ------
    QHttpMultiPart* makeAddImageMultiPart(int projectId, const QString &pathImage);
};

#endif // ENTITYIMAGESERVICE_H
