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

private:
    Ui::PortfolioProject *ui;

    //------ Initialization ------
    void init(const Project &project);
};

#endif // PORTFOLIOPROJECT_H
