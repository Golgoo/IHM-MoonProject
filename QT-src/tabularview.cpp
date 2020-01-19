#include "tabularview.h"
#include "ui_tabularview.h"

TabularView::TabularView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabularView)
{
    ui->setupUi(this);
}

TabularView::~TabularView()
{
    delete ui;
}
