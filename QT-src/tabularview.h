#ifndef TABULARVIEW_H
#define TABULARVIEW_H

#include <QWidget>

namespace Ui {
class TabularView;
}

class TabularView : public QWidget
{
    Q_OBJECT

public:
    explicit TabularView(QWidget *parent = nullptr);
    ~TabularView();

private:
    Ui::TabularView *ui;
};

#endif // TABULARVIEW_H
