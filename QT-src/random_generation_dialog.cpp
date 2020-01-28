#include "random_generation_dialog.h"
#include "ui_randomgenerationdialog.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
RandomGenerationDialog::RandomGenerationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomGenerationDialog)
{
    ui->setupUi(this);
}

int RandomGenerationDialog::getNbRows()
{
    return ui->nb_rows->value();
}

int RandomGenerationDialog::getNbCols()
{
    return ui->nb_cols->value();
}

QString RandomGenerationDialog::getTemporaryFilename()
{
    return _tmp_file.fileName();
}

int RandomGenerationDialog::process_generation()
{
    if(! (ui->borne_sup->value() > ui->borne_inf->value())) return -1 ;
    if(! _tmp_file.open()) return -1 ;
    QTextStream outStream (&_tmp_file);
    for(int line = 0 ; line < ui->nb_rows->value() ; line ++){
        for(int col = 0 ; col < ui->nb_cols->value() ; col ++ ){
            outStream << generateRandomInt() << ',';
        }
        outStream << "\n";
    }
    _tmp_file.close();
    return 1 ;
}



int RandomGenerationDialog::generateRandomInt()
{
    return ( qrand() % (ui->borne_sup->value() - ui->borne_inf->value() + 1 ) ) + ui->borne_inf->value();
}

RandomGenerationDialog::~RandomGenerationDialog()
{
    delete ui;
}
