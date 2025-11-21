#include "project.h"

Project::Project() :
    id(-1)
{

}

Project::Project(int id, const QString &name, const QString &smallAbout,
                 const QString &bigAbout, const QString &userComments, const QString &coverPath) :
    id(id), name(name), smallAbout(smallAbout),
    bigAbout(bigAbout), userComments(userComments), coverPath(coverPath)
{

}

//------ Setters ------

void Project::setId(int _id){
    id = _id;
}

void Project::setName(const QString &_name){
    name = _name;
}

void Project::setSmallAbout(const QString &_smallAbout){
    smallAbout = _smallAbout;
}

void Project::setBigAbout(const QString &_bigAbout){
    bigAbout = _bigAbout;
}

void Project::setUserComments(const QString &_userComments){
    userComments = _userComments;
}

void Project::setCoverPath(const QString &_coverPath){
    coverPath = _coverPath;
}

//------ Getters ------

int Project::getId() const {
    return id;
}

QString Project::getName() const {
    return name;
}

QString Project::getSmallAbout() const {
    return smallAbout;
}

QString Project::getBigAbout() const {
    return bigAbout;
}

QString Project::getUserComments() const {
    return userComments;
}

QString Project::getCoverPath() const {
    return coverPath;
}
