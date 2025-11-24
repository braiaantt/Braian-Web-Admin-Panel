#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <QString>
#include <QVector>
#include "technology.h"
#include "project.h"

class Portfolio
{
public:
    Portfolio();

    //------ Setters ------
    void setUserName(const QString &userName);
    void setUserProfession(const QString &userProfession);
    void setUserPhotoPath(const QString &userPhotoPath);
    void setUserAbout(const QString &userAbout);
    void setTechnologies(const QVector<Technology> &technologies);
    void setProjects(const QVector<Project> &projects);

    //------ Getters ------
    QString getUserName() const;
    QString getUserProfession() const;
    QString getUserPhotoPath() const;
    QString getUserAbout() const;
    const QVector<Technology>& getTechnologies() const;
    const QVector<Project>& getProjects() const;

private:
    QString userName;
    QString userProfession;
    QString userPhotoPath;
    QString userAbout;
    QVector<Technology> technologies;
    QVector<Project> projects;
};

#endif // PORTFOLIO_H
