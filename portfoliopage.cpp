#include "portfoliopage.h"
#include "ui_portfoliopage.h"

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
