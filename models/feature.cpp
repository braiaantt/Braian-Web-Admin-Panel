#include "feature.h"

Feature::Feature() :
    id(-1), projectId(-1)
{

}

Feature::Feature(int id, int projectId, const QString &feature) :
    id(id), projectId(projectId), feature(feature)
{

}

//------ Getters ------

int Feature::getId() const
{
    return id;
}

int Feature::getProjectId() const
{
    return projectId;
}

QString Feature::getFeature() const
{
    return feature;
}

//------ Setters ------

void Feature::setId(int _id)
{
    id = _id;
}

void Feature::setProjectId(int _projectId)
{
    projectId = _projectId;
}

void Feature::setFeature(const QString &_feature)
{
    feature = _feature;
}
