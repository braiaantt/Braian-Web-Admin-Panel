#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include <QString>

class Technology
{
public:
    Technology();
    Technology(int id, const QString &name, const QString &imgPath);

    //------ Setters ------
    void setId(int id);
    void setName(const QString &name);
    void setImgPath(const QString &imgPath);

    //------ Getters ------
    int getId() const;
    QString getName() const;
    QString getImgPath() const;

private:
    int id;
    QString name;
    QString imgPath;
};

#endif // TECHNOLOGY_H
