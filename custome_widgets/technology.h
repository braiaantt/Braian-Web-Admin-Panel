#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include <QWidget>

namespace Ui {
class Technology;
}

class Technology : public QWidget
{
    Q_OBJECT

public:
    explicit Technology(QWidget *parent, const QPixmap &photo, const QString &name, const QString &filePath = "");
    ~Technology();

private:
    Ui::Technology *ui;
    QString filePath;
};

#endif // TECHNOLOGY_H
