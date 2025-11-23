#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QPixmap>

namespace Utils{
    QString selectImageFile();
    QPixmap roundedPixmap(const QPixmap &pixmap, const QSize &targetSize);
    void showWarning(QWidget* parent, const QString &message);
}

#endif // UTILS_H
