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
    connect(get_current_generator_combo_box(), SIGNAL(currentIndexChanged(int)), this, SLOT(change_current_generator()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(change_generator_type(int)));
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(update_current_generator()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(apply_to_another_generator()));

    ui->nb_cols->setValue(default_columns_count);
    ui->column_name_form->setText(default_column_name_prefix + QString::number(1));
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
    if(! _tmp_file.open()) return -1 ;
    QTextStream outStream (&_tmp_file);
    generate_headers(outStream);
    generate_lines(outStream);
    _tmp_file.close();
    return 1 ;
}

void RandomGenerationDialog::generate_headers(QTextStream &outStream) const
{
    for(int section = 0 ; section < ui->nb_cols->value() - 1 ; section++){
        outStream << get_current_generator_combo_box()->itemText(section) << ',' ;
    }
    outStream << get_current_generator_combo_box()->itemText(ui->nb_cols->value() - 1);
    outStream << "\n";
}

void RandomGenerationDialog::generate_lines(QTextStream &outStream) const
{
    for(int line = 1 ; line < ui->nb_rows->value() ; line ++){
        for(int col = 0 ; col < ui->nb_cols->value() - 1 ; col ++ ){
            outStream << _columns_generators.at(col)->generate() << ',';
        }
        outStream << _columns_generators.at(ui->nb_cols->value() - 1)->generate();
        outStream << "\n";
    }
}

void RandomGenerationDialog::columns_changed(int nb_cols)
{
    qDebug() << __FUNCTION__;
    int col_size = _columns_generators.size();

    push_back_columns(col_size, nb_cols);
    pop_back_columns(col_size - 1, nb_cols);

    updateGeneratorUI();
    qDebug() << "End of " << __FUNCTION__;
}

void RandomGenerationDialog::push_back_columns(int from, int to)
{
    for(int i = from ; i  <  to ; i++){
        add_new_generator(i, default_column_name_prefix + QString::number(i+1));
    }
}

void RandomGenerationDialog::add_new_generator(int index, QString name)
{
    _columns_generators.insert(index, new IntegerGenerator(Generator::build_default_gen_s()));
    get_current_generator_combo_box()->insertItem(index, name);
    get_apply_other_generator_combo_box()->insertItem(index, name);
}

void RandomGenerationDialog::pop_back_columns(int from, int to)
{
    for(int i = from ; i >= to ; i--){
        remove_generator(i);
    }
}

void RandomGenerationDialog::remove_generator(int index)
{
    Generator *generatorToDelTmp = _columns_generators.at(index);
    _columns_generators.remove(index);
    delete generatorToDelTmp;
    get_current_generator_combo_box()->removeItem(index);
    get_apply_other_generator_combo_box()->removeItem(index);
}

void RandomGenerationDialog::updateGeneratorUI()
{
    qDebug() << __FUNCTION__;
    generator_s gen_s = get_current_generator()->getGeneratorInfo();

    updateGeneratorBoundsUI(gen_s);
    updateGeneratorCustomItemsUI(gen_s);

    qDebug() <<"End Of - " << __FUNCTION__;
}

void RandomGenerationDialog::updateGeneratorBoundsUI(const generator_s gen_s)
{
    ui->borne_inf->setValue(gen_s.borne_inf);
    ui->borne_sup->setValue(gen_s.borne_sup);
}

void RandomGenerationDialog::updateGeneratorCustomItemsUI(const generator_s gen_s)
{
    ui->textEdit->clear();
    for(auto it = gen_s.items.begin() ; it < gen_s.items.end() ; it ++){
        ui->textEdit->append(*it);
    }
}


void RandomGenerationDialog::done(int r)
{
    if(QDialog::Accepted == r)
    {
        QStringList errorList ;
        int i = 0 ;
        for(auto col_gen : _columns_generators){
            if(! col_gen->valid()){
                errorList.push_back(get_current_generator_combo_box()->itemText(i++) + " : " + col_gen->errorMessage());
            }
        }
        if(errorList.isEmpty()){
            QDialog::done(r);
        }
        else{
            qDebug() << errorList ;
            GeneErrorDialog errorDial(this);
            errorDial.addErrors(errorList);
            errorDial.exec();
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
    get_current_generator()->updateFrom(gen_s);
    qDebug() << "End of - " << __FUNCTION__;
}

void RandomGenerationDialog::change_current_generator()
{
    qDebug() << __FUNCTION__;
    updateGeneratorUI();
    ui->tabWidget->setCurrentIndex(get_current_generator()->getUiSection());
    qDebug() << "End of " << __FUNCTION__;
}

void RandomGenerationDialog::column_renamed()
{
    qDebug() << __FUNCTION__;
    get_current_generator_combo_box()->setItemText(current_generator_index(), ui->column_name_form->text());
    get_apply_other_generator_combo_box()->setItemText(current_generator_index(), ui->column_name_form->text());
}

Generator* RandomGenerationDialog::buildGenerator(const int generator_type, generator_s gen_s)
{
    switch (generator_type) {
    case 1:
        return new CustomGenerator(gen_s);
    case 0:
        return new IntegerGenerator(gen_s);
    default:
        return Generator::build_default_generator();
    }
}

void RandomGenerationDialog::change_generator_type(int type_clicked_index)
{
    qDebug() << __FUNCTION__;

    Generator *current_generator = get_current_generator();
    _columns_generators.remove(current_generator_index());
    generator_s gen_s = current_generator->getGeneratorInfo();
    delete current_generator;

    _columns_generators.insert(current_generator_index(), buildGenerator(type_clicked_index, gen_s));

    updateGeneratorUI();

    qDebug() << "End of " << __FUNCTION__;
}

//To rename .ui easier
QComboBox* RandomGenerationDialog::get_current_generator_combo_box() const
{
    return ui->current_generator_combo_box ;
}

//To rename .ui easier
QComboBox* RandomGenerationDialog::get_apply_other_generator_combo_box() const
{
    return ui->apply_to_other_combo_box ;
}

int RandomGenerationDialog::current_generator_index() const
{
    return get_current_generator_combo_box()->currentIndex();
}

int RandomGenerationDialog::apply_other_generator_index() const
{
    return get_apply_other_generator_combo_box()->currentIndex();
}

int RandomGenerationDialog::get_current_generator_section() const
{
    return ui->tabWidget->currentIndex();
}

Generator* RandomGenerationDialog::get_current_generator() const
{
    return get_generator_at(current_generator_index());
}

Generator* RandomGenerationDialog::get_generator_at(int index) const
{
    if(_columns_generators.size() > index && index >= 0){
        return _columns_generators.at(index);
    }else{
        return nullptr;
    }
}

void RandomGenerationDialog::apply_to_another_generator()
{
    int current_generator_section = get_current_generator_section();
    int other_index = apply_other_generator_index();
    Generator* other_generator = get_generator_at(other_index);
    Generator* current_generator = get_current_generator();
    if(other_generator->getUiSection() != current_generator_section){
        _columns_generators.remove(other_index);
        Generator * new_generator = buildGenerator(current_generator_section, current_generator->getGeneratorInfo());
        _columns_generators.insert(other_index, new_generator);
        delete other_generator;
    }else{
        other_generator->updateFrom(current_generator->getGeneratorInfo());
    }
}

RandomGenerationDialog::~RandomGenerationDialog()
{
    delete ui;
}
