#include "generation_dialog.h"

#include <QEasingCurve>
#include <QListWidgetItem>
#include <QPainter>

#include "uniformdistribution.h"
#include "noconstraint.h"


#include <QStringList>

#include <QDebug>

#include <memory>
#include <QItemSelection>

using namespace std;

#include "curve/uniformcurve.h"
#include "curve/exponentialcurve.h"
#include "curve/linearcurve.h"
#include "curve/noconstraintcurve.h"

generation_dialog::generation_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generation_dialog)
{
    ui->setupUi(this);

    _columns_model = new QStringListModel();

    QStringList stringList ;
    _columns_model->setStringList(stringList);

    ui->cols_list_view->setModel(_columns_model);

    _selected_generator_index = 0 ;
    _restriction_curves.push_back(shared_ptr<RestrictionCurve>(new NoConstraintCurve()));
    _restriction_curves.push_back(shared_ptr<RestrictionCurve>(new LinearCurve()));
    initRestrictionBox(_restriction_curves, ui->restriction_combo_box);
    _distribution_curves.push_back(shared_ptr<DistributionCurve>(new UniformCurve()));
    _distribution_curves.push_back(shared_ptr<DistributionCurve>(new ExponentialCurve()));
    initDistributionBox(_distribution_curves, ui->distributive_combo_box);

    connect(ui->restriction_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(restriction_item_change(int)));
    connect(ui->distributive_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(distribution_item_change(int)));

    connect(ui->cols_list_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &generation_dialog::current_column_change);
    connect(ui->nbr_cols, SIGNAL(valueChanged(int)), this, SLOT(nbr_columns_changed(int)));

    ui->nbr_cols->setValue(1);
    ui->cols_list_view->selectionModel()->setCurrentIndex(ui->cols_list_view->indexAt(QPoint(0,0)), QItemSelectionModel::Select);


    connect(ui->nbr_rows, SIGNAL(valueChanged(int)), this, SLOT(nbr_rows_changed(int)));
    connect(ui->apply_button, SIGNAL(clicked()), this, SLOT(apply_to_other_columns_clicked()));
    connect(ui->nbr_distinct_values, SIGNAL(valueChanged(int)), this, SLOT(nbr_distinct_values_changed(int)));

}

void generation_dialog::initDistributionBox(const QVector<std::shared_ptr<DistributionCurve>> curves, QComboBox * const comboBox)
{
    for(auto curve : curves){
        curve->loadPixMap();
        comboBox->addItem(curve->getString());
    }
}

void generation_dialog::initRestrictionBox(const QVector<std::shared_ptr<RestrictionCurve> > curves, QComboBox *comboBox)
{
    for(auto curve : curves){
        curve->loadPixMap();
        comboBox->addItem(curve->getString());
    }
}

void generation_dialog::distribution_item_change(int item_index)
{
    qDebug() << "Generating distribution column";
    qDebug() << "Size : " << _distribution_curves.size() << "Item : " << item_index;
    ui->distributive_graph_label->setPixmap(_distribution_curves.at(item_index)->getPixMap());
    ColumnGenerator* current_generator = getSelectedGenerator();
    current_generator->setNewDistributiveLaw(_distribution_curves.at(item_index)->buildDistributiveLaw());
}

void generation_dialog::restriction_item_change(int item_index)
{
    ui->restriction_graph_label->setPixmap(_restriction_curves.at(item_index)->getPixMap());
    ColumnGenerator* current_generator = getSelectedGenerator();
    current_generator->setNewValueRestriction(_restriction_curves.at(item_index)->buildValueConstraint(ui->nbr_distinct_values->value(), ui->nbr_rows->value()));
}

void generation_dialog::current_column_change()
{
    qDebug()<<"Column CHanged" ;
    qDebug()<< ui->cols_list_view->currentIndex();
    _selected_generator_index = ui->cols_list_view->currentIndex().row();
    refresh_generator_UI();
}

ColumnGenerator* generation_dialog::getSelectedGenerator() const
{
    qDebug() << "Selecting current generator :  ";
    qDebug() << "generatorsize: " << _columns_generator.size();
    qDebug() << "Selected Index : " << _selected_generator_index;
    return _columns_generator.at(_selected_generator_index);
}

void generation_dialog::refresh_generator_UI()
{
     qDebug() << "Refreshgin generator ui ";
    ColumnGenerator* current_generator = getSelectedGenerator();
    int restriction_index = current_generator->getValueRestriction().getUISection();
    int distribution_index = current_generator->getDistributiveLaw().getUISection();
    ui->restriction_graph_label->setPixmap(_restriction_curves.at(restriction_index)->getPixMap());
    ui->distributive_graph_label->setPixmap(_distribution_curves.at(distribution_index)->getPixMap());
    ui->restriction_combo_box->setCurrentIndex(restriction_index);
    ui->distributive_combo_box->setCurrentIndex(distribution_index);
    ui->nbr_distinct_values->setValue(current_generator->getValueRestriction().getMaxValues());
    qDebug() << "End of generator ui refresh";
}

void generation_dialog::nbr_columns_changed(int nb_cols)
{
    qDebug() << "Generating default column";
    int col_size = _columns_generator.size();
    QStringList list = _columns_model->stringList();
    QModelIndex modelIndex = ui->cols_list_view->currentIndex();
    for(int i = col_size ; i < nb_cols ; i ++){
        _columns_generator.insert(i, new ColumnGenerator(
                                        new UniformDistribution(),
                                        new NoConstraint(ui->nbr_distinct_values->value(), ui->nbr_rows->value())
                                      )
                                  );
        _columns_model->insertRow(i);
        list.push_back("Colonne "+QString::number(i+1));
    }
    for(int i = col_size - 1 ; i >= nb_cols ; i --){
        ColumnGenerator *generatorToDelTmp = _columns_generator.at(i);
        _columns_generator.remove(i);
        delete generatorToDelTmp;
        list.pop_back();
    }
    _columns_model->setStringList(list);
    if(modelIndex.row() < nb_cols){
        ui->cols_list_view->setCurrentIndex(modelIndex);
    }else{
        ui->cols_list_view->setCurrentIndex(ui->cols_list_view->indexAt(QPoint(0,0)));
    }

    ui->apply_from_coombo_box->clear();
    ui->apply_from_coombo_box->insertItems(0, list);
    ui->apply_to_combo_box->clear();
    ui->apply_to_combo_box->insertItems(0, list);

    ui->apply_from_coombo_box->setCurrentIndex(0);
    ui->apply_to_combo_box->setCurrentIndex(list.size()-1);
    qDebug() << "End of generation column";
}

void generation_dialog::nbr_rows_changed(int nb_rows)
{
    for(auto generator : _columns_generator){
        generator->getValueRestriction().setNbLines(nb_rows);
    }
}

void generation_dialog::nbr_distinct_values_changed(int nb_values)
{
    qDebug() << "Distinct Value changed";
    ColumnGenerator *current_generator = getSelectedGenerator();
    current_generator->getValueRestriction().setMaxValues(nb_values);
}

void generation_dialog::apply_to_other_columns_clicked()
{
    shared_ptr<DistributionCurve> selectedDistriCurve = _distribution_curves.at(ui->distributive_combo_box->currentIndex());
    shared_ptr<RestrictionCurve> selectedRestrictCurve = _restriction_curves.at(ui->restriction_combo_box->currentIndex());

    ColumnGenerator * tmpGenerator ;
    for(int ind = ui->apply_from_coombo_box->currentIndex() ; ind <= ui->apply_to_combo_box->currentIndex() ; ind ++){
        tmpGenerator = _columns_generator.at(ind);
        tmpGenerator->setNewDistributiveLaw(selectedDistriCurve->buildDistributiveLaw());
        tmpGenerator->setNewValueRestriction(selectedRestrictCurve->buildValueConstraint(ui->nbr_distinct_values->value(), ui->nbr_rows->value()));
    }
}

int generation_dialog::process_generation()
{
    if(! _tmp_file.open()) return -1 ;
    QTextStream outStream (&_tmp_file);
    generate_headers(outStream);
    generate_lines(outStream);
    _tmp_file.close();
    return 1 ;
}

void generation_dialog::generate_headers(QTextStream &outStream) const
{
    QStringList columns_name = _columns_model->stringList();
    for(int section = 0 ; section < columns_name.size() - 1 ; section++){
        outStream << columns_name.at(section) << ',' ;
    }
    outStream << columns_name.last();
    outStream << "\n";
}

void generation_dialog::generate_lines(QTextStream &outStream) const
{

    for(int line = 1 ; line < ui->nbr_rows->value() ; line ++){
        for(auto it = _columns_generator.begin() ; it < _columns_generator.end() - 1 ; it ++){
            outStream << (*it)->generate(line) << ',';
        }
        outStream << _columns_generator.last()->generate(line);
        outStream << "\n";
    }
}

QString generation_dialog::getTemporaryFilename() const
{
    return _tmp_file.fileName();
}

generation_dialog::~generation_dialog()
{
    for(auto col_gen : _columns_generator){
        delete col_gen;
    }
    delete _columns_model;
}



