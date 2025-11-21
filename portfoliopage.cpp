#include "portfoliopage.h"
#include "ui_portfoliopage.h"
#include "createtechnology.h"

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

    Technology *technology = dialog.getTechnology();
    QHBoxLayout *layout = (QHBoxLayout*)ui->scrollAreaTechnologyWidgetContents->layout();

    if(technology && layout){
        layout->insertWidget(layout->count()-1, technology);
    }
}
