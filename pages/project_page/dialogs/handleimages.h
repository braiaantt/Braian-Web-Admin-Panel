#ifndef HANDLEIMAGES_H
#define HANDLEIMAGES_H

#include <QDialog>
#include "servicefactory.h"
#include "entityimageservice.h"

namespace Ui {
class HandleImages;
}

class HandleImages : public QDialog
{
    Q_OBJECT

public:
    explicit HandleImages(ServiceFactory *factory, int projectId, QWidget *parent = nullptr);
    ~HandleImages();

private slots:
    void imageCreated(const QString &imgPath);
    void pathsReceipt(const QVector<QString> &paths);
    void imageReceipt(const QString &imgPath, const QPixmap &pixmap);
    void removeImage(const QString &imgPath);
    void deleteImageSuccess();
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButton_clicked();

private:
    Ui::HandleImages *ui;
    ServiceFactory *factory;
    EntityImageService *entityImageService;
    ProjectService *projectService;
    int projectId;
    QString cachedPath;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();
};

#endif // HANDLEIMAGES_H
