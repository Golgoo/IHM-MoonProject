#include "random_generation_dialog.h"
#include "ui_randomgenerationdialog.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>


#include "integergenerator.h"

RandomGenerationDialog::RandomGenerationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomGenerationDialog)
{
    ui->setupUi(this);

    connect(ui->nb_cols, SIGNAL(valueChanged(int)), this, SLOT(columns_changed(int)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(column_renamed()));
    connect(ui->borne_inf, SIGNAL(valueChanged(int)), this, SLOT(update_current_generator()));
    connect(ui->borne_sup, SIGNAL(valueChanged(int)), this, SLOT(update_current_generator()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(change_current_generator()));

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
    if((ui->borne_sup->value() < ui->borne_inf->value())) return -1 ;
    if(! _tmp_file.open()) return -1 ;
    QTextStream outStream (&_tmp_file);
    for(int section = 0 ; section < ui->nb_cols->value() - 1 ; section++){
        outStream << ui->comboBox->itemText(section) << ',' ;
    }
    outStream << ui->comboBox->itemText(ui->nb_cols->value() - 1);
    outStream << "\n";
    for(int line = 1 ; line < ui->nb_rows->value() ; line ++){
        for(int col = 0 ; col < ui->nb_cols->value() - 1 ; col ++ ){
            outStream << _columns_generators.at(col)->generate() << ',';
        }
        outStream << _columns_generators.at(ui->nb_cols->value() - 1)->generate();
        outStream << "\n";
    }
    _tmp_file.close();
    return 1 ;
}


void RandomGenerationDialog::columns_changed(int nb_cols)
{
    int col_size = _columns_generators.size();
    QString tmp ;
    Generator *generatorToDelTmp ;
    for(int i = col_size ; i  <  nb_cols ; i++){
        tmp = QString::number(i+1);
        _columns_generators.push_back(new IntegerGenerator(default_column_name + tmp, 0, 0));
        ui->comboBox->insertItem(i, _columns_generators.at(i)->name());
    }
    for(int i = col_size - 1; i >= nb_cols ; i--){
        generatorToDelTmp = _columns_generators.last();
        _columns_generators.pop_back();
        delete generatorToDelTmp;
        ui->comboBox->removeItem(i);
    }

    updateGeneratorUI();
}

void RandomGenerationDialog::updateGeneratorUI()
{
    Generator *current_generator = _columns_generators.at(ui->comboBox->currentIndex());
    ui->tabWidget->setCurrentIndex(current_generator->getUiSection());
    generator_s gen_s = current_generator->updateWidget();
    ui->borne_inf->setValue(gen_s.borne_inf);
    ui->borne_sup->setValue(gen_s.borne_sup);
}

generator_s RandomGenerationDialog::build_gen_s_from_ui() const
{
    generator_s gen_s;
    gen_s.borne_inf = ui->borne_inf->value();
    gen_s.borne_sup = ui->borne_sup->value();
    return gen_s;
}

void RandomGenerationDialog::update_current_generator()
{
    generator_s gen_s = build_gen_s_from_ui();
    qDebug() << "Need to update the current generator ";
    _columns_generators.at(ui->comboBox->currentIndex())->updateFrom(gen_s);
}

void RandomGenerationDialog::change_current_generator()
{
    qDebug() << "Need to update the ui" ;
    updateGeneratorUI();
}

void RandomGenerationDialog::column_renamed()
{
    ui->comboBox->setItemText(ui->comboBox->currentIndex(), ui->lineEdit->text());
}

RandomGenerationDialog::~RandomGenerationDialog()
{
    delete ui;
}
