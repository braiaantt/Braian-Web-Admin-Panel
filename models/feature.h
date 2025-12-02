#ifndef FEATURE_H
#define FEATURE_H

#include <QString>

class Feature
{
public:
    Feature();
    Feature(int id, int projectId, const QString &feature);

    //------ Getters ------
    int getId() const;
    int getProjectId() const;
    QString getFeature() const;

    //------ Setters ------
    void setId(int id);
    void setProjectId(int projectId);
    void setFeature(const QString &feature);

private:
    int id;
    int projectId;
    QString feature;
};

#endif // FEATURE_H
