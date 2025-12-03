#ifndef TECHNICALINFO_H
#define TECHNICALINFO_H

#include <QString>

class TechnicalInfo
{
public:
    TechnicalInfo();
    TechnicalInfo(int id, int projectId, const QString &info);

    //------ Getters ------
    int getId() const;
    int getProjectId() const;
    QString getInfo() const;

    //------ Setters ------
    void setId(int id);
    void setProjectId(int projectId);
    void setInfo(const QString &info);

private:
    int id;
    int projectId;
    QString info;
};

#endif // TECHNICALINFO_H
