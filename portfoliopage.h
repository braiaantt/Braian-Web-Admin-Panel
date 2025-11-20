#ifndef PORTFOLIOPAGE_H
#define PORTFOLIOPAGE_H

#include <QWidget>

namespace Ui {
class PortfolioPage;
}

class PortfolioPage : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioPage(QWidget *parent = nullptr);
    ~PortfolioPage();

private:
    Ui::PortfolioPage *ui;
};

#endif // PORTFOLIOPAGE_H
