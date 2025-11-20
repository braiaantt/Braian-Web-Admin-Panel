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
    explicit Technology(QWidget *parent, const QPixmap &image, const QString &name);
    ~Technology();

private:
    Ui::Technology *ui;
};

#endif // TECHNOLOGY_H
