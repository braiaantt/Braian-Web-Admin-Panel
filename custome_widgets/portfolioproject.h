#ifndef PORTFOLIOPROJECT_H
#define PORTFOLIOPROJECT_H

#include <QWidget>

namespace Ui {
class PortfolioProject;
}

class PortfolioProject : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioProject(QWidget *parent = nullptr);
    ~PortfolioProject();

private:
    Ui::PortfolioProject *ui;
};

#endif // PORTFOLIOPROJECT_H
