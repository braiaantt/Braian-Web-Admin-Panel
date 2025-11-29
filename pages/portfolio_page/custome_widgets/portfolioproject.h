#ifndef PORTFOLIOPROJECT_H
#define PORTFOLIOPROJECT_H

#include <QWidget>
#include "project.h"

namespace Ui {
class PortfolioProject;
}

class PortfolioProject : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioProject(QWidget *parent = nullptr, const Project &project = Project());
    ~PortfolioProject();

    //------ Setters ------
    void setCoverImage(const QPixmap &pixmap);

    //------ Getters ------
    const Project& getProject() const;

private:
    Ui::PortfolioProject *ui;
    Project project;

    //------ Initialization ------
    void init();
};

#endif // PORTFOLIOPROJECT_H
