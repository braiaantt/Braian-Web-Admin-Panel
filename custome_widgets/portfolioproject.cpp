#include "portfolioproject.h"
#include "ui_portfolioproject.h"

PortfolioProject::PortfolioProject(QWidget *parent, const Project &project)
    : QWidget(parent)
    , ui(new Ui::PortfolioProject)
{
    ui->setupUi(this);
    init(project);
}

PortfolioProject::~PortfolioProject()
{
    delete ui;
}

//------ Initialization ------

void PortfolioProject::init(const Project &project)
{
    if(!project.getCoverPath().isEmpty()){
        ui->labelImage->setPixmap(QPixmap(project.getCoverPath()));
    }

    ui->labelTitle->setText(project.getName());
    ui->labelSmallAbout->setText(project.getSmallAbout());
}
