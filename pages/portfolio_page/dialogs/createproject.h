#ifndef CREATEPROJECT_H
#define CREATEPROJECT_H

#include <QDialog>
#include "project.h"
#include "projectservice.h"

namespace Ui {
class CreateProject;
}

class CreateProject : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProject(ProjectService *projectService, QWidget *parent = nullptr);
    ~CreateProject();

    //------ Getters ------
    Project getProject() const;

private slots:
    void projectCreated(int id);
    void errorOcurred(const QString &message);

    //------ UI Slots ------
    void on_pushButtonAccept_clicked();

    void on_pushButtonSelectImage_clicked();

private:
    Ui::CreateProject *ui;
    ProjectService *projectService;
    Project project;

    //------ Initialization ------
    void init();
    void connectSignalsAndSlots();

    //------ Helpers ------
    bool checkValues();
    void setProjectValues(Project &project);
};

#endif // CREATEPROJECT_H
