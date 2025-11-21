#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

class Project
{
public:
    Project();
    Project(int id, const QString &name, const QString &smallAbout, const QString &bigAbout, const QString &userComments, const QString &coverPath);

    //------ Setters ------
    void setId(int id);
    void setName(const QString &name);
    void setSmallAbout(const QString &smallAbout);
    void setBigAbout(const QString &bigAbout);
    void setUserComments(const QString &userComments);
    void setCoverPath(const QString &coverPath);

    //------ Getters ------
    int getId() const;
    QString getName() const;
    QString getSmallAbout() const;
    QString getBigAbout() const;
    QString getUserComments() const;
    QString getCoverPath() const;

private:
    int id;
    QString name;
    QString smallAbout;
    QString bigAbout;
    QString userComments;
    QString coverPath;
};

#endif // PROJECT_H
