#include "portfolioproject.h"
#include "ui_portfolioproject.h"

PortfolioProject::PortfolioProject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PortfolioProject)
{
    ui->setupUi(this);
}

PortfolioProject::~PortfolioProject()
{
    delete ui;
}
