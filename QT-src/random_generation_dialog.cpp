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

    connect(ui->nb_cols, SIGNAL(valueChanged(int)), this, SLOT(columns_changed(int)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(column_renamed()));

    ui->nb_cols->setValue(default_columns_count);
    ui->lineEdit->setText(default_column_name + QString::number(1));
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
    qDebug() << "cols : " << ui->nb_cols->value();
    qDebug() << "line : " << ui->nb_rows->value();
    if((ui->borne_sup->value() < ui->borne_inf->value())) return -1 ;
    if(! _tmp_file.open()) return -1 ;
    QTextStream outStream (&_tmp_file);
    for(int section = 0 ; section < ui->nb_cols->value() - 1 ; section++){
        outStream << "COL"<<section << ',' ;
    }
    outStream << "COL"<<ui->nb_cols->value() - 1;
    outStream << "\n";
    for(int line = 1 ; line < ui->nb_rows->value() ; line ++){
        for(int col = 0 ; col < ui->nb_cols->value() - 1 ; col ++ ){
            outStream << generateRandomInt() << ',';
        }
        outStream << generateRandomInt();
        outStream << "\n";
    }
    qDebug() << "Finito ! " << ui->nb_cols->value();
    _tmp_file.close();
    return 1 ;
}

int RandomGenerationDialog::generateRandomInt()
{
    return ( qrand() % (ui->borne_sup->value() - ui->borne_inf->value() + 1 ) ) + ui->borne_inf->value();
}

void RandomGenerationDialog::columns_changed(int nb_cols)
{
    int col_size = _columns.size();
    QString tmp ;
    for(int i = col_size ; i  <  nb_cols ; i++){
        tmp = QString::number(i+1);
        _columns.push_back(default_column_name + " " + tmp);
        ui->comboBox->insertItem(i, _columns.at(i));
    }
    for(int i = col_size - 1; i >= nb_cols ; i--){
        _columns.pop_back();
        ui->comboBox->removeItem(i);
    }
}

void RandomGenerationDialog::column_renamed()
{
    ui->comboBox->setItemText(ui->comboBox->currentIndex(), ui->lineEdit->text());
}

RandomGenerationDialog::~RandomGenerationDialog()
{
    delete ui;
}
