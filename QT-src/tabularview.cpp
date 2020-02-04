#include "tabularview.h"
#include "ui_tabularview.h"
#include <QTableWidget>
#include <QStandardItem>
#include <QStandardItemModel>

TabularView::TabularView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabularView)
{
    ui->setupUi(this);

    QStandardItemModel *model=new QStandardItemModel(5,5,this);

    // pour les lignes
    for (int i=0;i<2;++i)

    // Pour les colonnes
        for (int j=0;j<2;++j)
        {
             QStandardItem *item= new QStandardItem();

                 item->setText("Hello");

                 item->setEditable(false);

                 model->setItem(i,j,item);
           }

    QTableView table(this);
    ui->dataTableView->setModel(model);



}

TabularView::~TabularView()
{
    delete ui;
}
