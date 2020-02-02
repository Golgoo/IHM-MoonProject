#include "geneerrordialog.h"

#include <QLabel>

#include <QDebug>
#include <QLayout>
GeneErrorDialog::GeneErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneErrorDialog)
{
    ui->setupUi(this);
}

GeneErrorDialog::~GeneErrorDialog()
{

}


void GeneErrorDialog::addError(QString error)
{
    ui->verticalLayout->addWidget(new QLabel(error));
}
void GeneErrorDialog::addErrors(QStringList errors)
{
    for(int i = 0 ; i < errors.size() && i < 3 ; i ++){
        ui->verticalLayout->addWidget(new QLabel(errors[i]));
    }
}
