#include "portfoliopage.h"
#include "ui_portfoliopage.h"
#include "createtechnology.h"
#include "createproject.h"
#include "portfolioproject.h"
#include "technologywidget.h"

PortfolioPage::PortfolioPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PortfolioPage)
{
    ui->setupUi(this);
}

PortfolioPage::~PortfolioPage()
{
    delete ui;
}

//------ UI Slots ------

void PortfolioPage::on_pushButtonAddTechnology_clicked()
{
    CreateTechnology dialog(this);
    if(dialog.exec() == QDialog::Rejected) return;

    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaTechnologyWidgetContents->layout();
    Technology technology = dialog.getTechnology();
    TechnologyWidget *technologyWidget = new TechnologyWidget(nullptr, technology);
    technologyWidget->setParent(ui->scrollAreaTechnologyWidgetContents); // to avoid memory leak warning

    if(technologyWidget && layout){
        layout->insertWidget(layout->count()-1, technologyWidget);
    }
}

void PortfolioPage::on_pushButtonAddProject_clicked()
{
    CreateProject dialog(this);
    if(dialog.exec() == QDialog::Rejected) return;

    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaProjectWidgetContents->layout();
    Project project = dialog.getProject();
    PortfolioProject *projectWidget = new PortfolioProject(nullptr, project);
    projectWidget->setParent(ui->scrollAreaProjectWidgetContents); // to avoid memory leak warning

    if(projectWidget && layout){
        layout->insertWidget(layout->count()-1, projectWidget);
    }
}

