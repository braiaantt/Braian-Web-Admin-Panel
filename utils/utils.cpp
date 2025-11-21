#include "utils.h"
#include <QFileDialog>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>

QString Utils::selectImageFile()
{
    return QFileDialog::getOpenFileName(
        nullptr,
        "Seleccionar imagen",
        "",
        "Imágenes (*.png *.jpg *.jpeg)"
        );
}

QPixmap Utils::roundedPixmap(const QPixmap &pixmap, const QSize &targetSize)
{
    //Scalate img
    QPixmap scaled = pixmap.scaled(
        targetSize,
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
        );

    //Crop as centered square
    int size = targetSize.width(); //Assuming targetSize is square
    QPixmap square = scaled.copy(
        (scaled.width() - size) / 2,
        (scaled.height() - size) / 2,
        size,
        size
        );

    //Create a transparent destination pixmap
    QPixmap dest(size, size);
    dest.fill(Qt::transparent);

    //Prepare painter
    QPainter painter(&dest);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);

    //Create painterPath and set it to painter
    QPainterPath path;
    path.addRoundedRect(dest.rect(), size/2, size/2);
    painter.setClipPath(path);

    //Paint the square image inside the clip path
    painter.drawPixmap(0, 0, square);

    return dest;
}

