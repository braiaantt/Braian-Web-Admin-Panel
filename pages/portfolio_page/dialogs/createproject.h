#ifndef CREATEPROJECT_H
#define CREATEPROJECT_H

#include <QDialog>
#include "project.h"

namespace Ui {
class CreateProject;
}

class CreateProject : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProject(QWidget *parent = nullptr);
    ~CreateProject();

    //------ Getters ------
    Project getProject() const;

private slots:
    void on_pushButtonAccept_clicked();

    void on_pushButtonSelectImage_clicked();

private:
    Ui::CreateProject *ui;
    Project project;

    //------ Initialization ------
    void init();

    //------ Helpers ------
    bool checkValues();
    void setProjectValues(Project &project);
};

#endif // CREATEPROJECT_H
