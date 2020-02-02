#ifndef RANDOM_GENERATION_DIALOG_H
#define RANDOM_GENERATION_DIALOG_H

#include <QDialog>
#include <QTemporaryFile>
#include "generator.h"

namespace Ui {
class RandomGenerationDialog;
}

class RandomGenerationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RandomGenerationDialog(QWidget *parent = nullptr);
    ~RandomGenerationDialog();

    QString getLabelValue();
    int getNbRows();
    int getNbCols();
    int process_generation();

    QString getTemporaryFilename();

private:
    QTemporaryFile _tmp_file;
    QVector<Generator*> _columns_generators ;
    QString default_column_name = "colonne ";
    qint8 default_columns_count = 3 ;
    void updateGeneratorUI();
    generator_s build_gen_s_from_ui() const;

public slots:
    void columns_changed(int nb_cols);
    void column_renamed();
    void update_current_generator();
    void change_current_generator();
    void change_generator_type(int type_clicked_index);
    void done(int r) override;
    void apply_to_another_generator();
private:
    Ui::RandomGenerationDialog *ui;
};

#endif // RANDOM_GENERATION_DIALOG_H
