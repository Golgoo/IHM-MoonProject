#ifndef GENERATION_DIALOG_H
#define GENERATION_DIALOG_H

#include "ui_generation_dialog.h"

#include <QVector>

#include "columngenerator.h"

#include <QModelIndex>
#include <QStringListModel>
#include <QTemporaryFile>

#include "curve/distributioncurve.h"
#include "curve/restrictioncurve.h"
#include "curve/curve.h"
#include <memory>

namespace Ui {
class generation_dialog;
}

class generation_dialog : public QDialog, private Ui::generation_dialog
{
    Q_OBJECT

public:
    explicit generation_dialog(QWidget *parent = nullptr);
    ~generation_dialog();
    int process_generation();
    QString getTemporaryFilename() const;

private:
    Ui::generation_dialog *ui ;
    QTemporaryFile _tmp_file;

    QVector<ColumnGenerator*> _columns_generator ;
    int _selected_generator_index ;

    QStringListModel* _columns_model;

    QVector<std::shared_ptr<DistributionCurve>> _distribution_curves ;
    QVector<std::shared_ptr<RestrictionCurve>> _restriction_curves ;

    void generate_headers(QTextStream &outStream) const;
    void generate_lines(QTextStream &outStream) const;

public slots:
    void current_column_change();
    void nbr_columns_changed(int nb_cols);
    void distribution_item_change(int item_index);
    void restriction_item_change(int item_index);
    void nbr_rows_changed(int nb_rows);
    void nbr_distinct_values_changed(int nb_values);
    void apply_to_other_columns_clicked();

private:
    void refresh_generator_UI();
    ColumnGenerator* getSelectedGenerator() const;

    //Cannot use generic with QVector<std::shared_ptr<Curve>> ...
    void initDistributionBox(const QVector<std::shared_ptr<DistributionCurve>> curves, QComboBox* comboBox);
    void initRestrictionBox(const QVector<std::shared_ptr<RestrictionCurve>> curves, QComboBox* comboBox);
};

#endif // GENERATION_DIALOG_H
