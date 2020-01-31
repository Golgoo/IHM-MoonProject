#include "random_generation_dialog.h"
#include "ui_randomgenerationdialog.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>


//#include "generator.h"
#include "integergenerator.h"
#include "customgenerator.h"
#include "geneerrordialog.h"

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
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(change_generator_type(int)));
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(update_current_generator()));

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
    qDebug() << __FUNCTION__;
    int col_size = _columns_generators.size();
    QString tmp ;
    Generator *generatorToDelTmp ;
    for(int i = col_size ; i  <  nb_cols ; i++){
        tmp = QString::number(i+1);
        _columns_generators.push_back(new IntegerGenerator(Generator::build_default_gen_s()));
        ui->comboBox->insertItem(i, default_column_name + tmp);
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
    qDebug() << __FUNCTION__;
    Generator *current_generator = _columns_generators.at(ui->comboBox->currentIndex());

    generator_s gen_s = current_generator->getGeneratorInfo();
    ui->borne_inf->setValue(gen_s.borne_inf);
    ui->borne_sup->setValue(gen_s.borne_sup);
    qDebug() << gen_s.items ;
    ui->textEdit->clear();
    for(auto it = gen_s.items.begin() ; it < gen_s.items.end() - 1 ; it ++){
        ui->textEdit->append(*it);
    }
    if(! gen_s.items.isEmpty())ui->textEdit->append(gen_s.items.last());
    qDebug() <<"End Of - " << __FUNCTION__;
}

void RandomGenerationDialog::done(int r)
{
    if(QDialog::Accepted == r)  // ok was pressed
    {
        QStringList errorList ;
        int i = 0 ;
        for(auto col_gen : _columns_generators){
            if(! col_gen->valid()){
                errorList.push_back(ui->comboBox->itemText(i++) + " : " + col_gen->errorMessage());
            }
        }
        if(errorList.isEmpty()){
            QDialog::done(r);
        }
        else{
            //TODO Display errorList in a popup
            GeneErrorDialog errorDial(this);
            errorDial.addErrors(errorList);
            errorDial.exec();
            qDebug() << errorList ;
        }
    }
    else // cancel, close or exc was pressed
    {
        QDialog::done(r);
    }
}

generator_s RandomGenerationDialog::build_gen_s_from_ui() const
{
    generator_s gen_s;

    gen_s.borne_inf = ui->borne_inf->value();
    gen_s.borne_sup = ui->borne_sup->value();
    gen_s.items = ui->textEdit->toPlainText().split('\n');
    qDebug() << "Splitting : " << gen_s.items;

    return gen_s;
}

void RandomGenerationDialog::update_current_generator()
{
    qDebug() << __FUNCTION__ ;
    generator_s gen_s = build_gen_s_from_ui();
    _columns_generators.at(ui->comboBox->currentIndex())->updateFrom(gen_s);
    qDebug() << "End of - " << __FUNCTION__;
}

void RandomGenerationDialog::change_current_generator()
{
    qDebug() << __FUNCTION__;
    updateGeneratorUI();
    ui->tabWidget->setCurrentIndex(_columns_generators.at(ui->comboBox->currentIndex())->getUiSection());
    qDebug() << "End of " << __FUNCTION__;
}

void RandomGenerationDialog::column_renamed()
{
    qDebug() << __FUNCTION__;
    ui->comboBox->setItemText(ui->comboBox->currentIndex(), ui->lineEdit->text());
}

void RandomGenerationDialog::change_generator_type(int type_clicked_index)
{
    qDebug() << __FUNCTION__;
    Generator *current_generator = _columns_generators.at(ui->comboBox->currentIndex());
    qDebug() << "Current index" << ui->comboBox->currentIndex();
    _columns_generators.remove(ui->comboBox->currentIndex());
    qDebug() << "After we crash" ;
    generator_s gen_s = current_generator->getGeneratorInfo();
    qDebug() << "Type clicked : " << type_clicked_index;
    switch(type_clicked_index){
    case 1 :
        _columns_generators.insert(ui->comboBox->currentIndex(), new CustomGenerator(gen_s));
        break;
    case 0 :
        _columns_generators.insert(ui->comboBox->currentIndex(), new IntegerGenerator(gen_s));
        break;
    default:
        break;
    }
    qDebug() << "Col gen Size : " << _columns_generators.size();
    qDebug() << "Combo b Size : " << ui->comboBox->count();
    delete current_generator;
    updateGeneratorUI();
    qDebug() << "End of " << __FUNCTION__;
}

RandomGenerationDialog::~RandomGenerationDialog()
{
    delete ui;
}
