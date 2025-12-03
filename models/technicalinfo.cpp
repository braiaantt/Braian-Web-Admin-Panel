#include "technicalinfo.h"

TechnicalInfo::TechnicalInfo() :
    id(-1), projectId(-1)
{

}

TechnicalInfo::TechnicalInfo(int id, int projectId, const QString &info) :
    id(id), projectId(projectId), info(info)
{

}

//------ Getters ------

int TechnicalInfo::getId() const
{
    return id;
}

int TechnicalInfo::getProjectId() const
{
    return projectId;
}

QString TechnicalInfo::getInfo() const
{
    return info;
}

//------ Setters ------

void TechnicalInfo::setId(int _id)
{
    id = _id;
}

void TechnicalInfo::setProjectId(int _projectId)
{
    projectId = _projectId;
}

void TechnicalInfo::setInfo(const QString &_info)
{
    info = _info;
}
