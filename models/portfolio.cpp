#include "portfolio.h"

Portfolio::Portfolio()
{

}

//------ Setters ------

void Portfolio::setUserName(const QString &name)
{
    userName = name;
}

void Portfolio::setUserProfession(const QString &profession)
{
    userProfession = profession;
}

void Portfolio::setUserPhotoPath(const QString &path)
{
    userPhotoPath = path;
}

void Portfolio::setUserAbout(const QString &about)
{
    userAbout = about;
}

void Portfolio::setTechnologies(const QVector<Technology> &_technologies)
{
    technologies = _technologies;
}

void Portfolio::setProjects(const QVector<Project> &_projects)
{
    projects = _projects;
}

//------ Getters ------

QString Portfolio::getUserName() const
{
    return userName;
}

QString Portfolio::getUserProfession() const
{
    return userProfession;
}

QString Portfolio::getUserPhotoPath() const
{
    return userPhotoPath;
}

QString Portfolio::getUserAbout() const
{
    return userAbout;
}

const QVector<Technology>& Portfolio::getTechnologies() const
{
    return technologies;
}

const QVector<Project>& Portfolio::getProjects() const
{
    return projects;
}
