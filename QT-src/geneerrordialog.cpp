#include "geneerrordialog.h"

#include <QLabel>
#include <QDebug>
GeneErrorDialog::GeneErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneErrorDialog)
{

}

GeneErrorDialog::~GeneErrorDialog()
{

}


void GeneErrorDialog::addError(QString error)
{
    //ui->verticalLayout->addWidget(new QLabel(error));
}
void GeneErrorDialog::addErrors(QStringList errors)
{
    qDebug() << "Adding Stuff : " << errors.size();
    for(int i = 0 ; i < errors.size() && i < 3 ; i ++){

    }
}
