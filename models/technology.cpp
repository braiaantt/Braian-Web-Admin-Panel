#include "technology.h"

Technology::Technology() :
    id(-1)
{

}

Technology::Technology(int id, const QString &name, const QString &imgPath) :
    id(id), name(name), imgPath(imgPath)
{

}

//------ Setters ------

void Technology::setId(int _id){
    id = _id;
}

void Technology::setName(const QString &_name){
    name = _name;
}

void Technology::setImgPath(const QString &_imgPath){
    imgPath = _imgPath;
}

//------ Getters ------

int Technology::getId() const {
    return id;
}

QString Technology::getName() const {
    return name;
}

QString Technology::getImgPath() const {
    return imgPath;
}
