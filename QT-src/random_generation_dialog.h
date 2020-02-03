#ifndef RANDOM_GENERATION_DIALOG_H
#define RANDOM_GENERATION_DIALOG_H

#include <QDialog>
#include <QTemporaryFile>
#include <QTextStream>
#include <QComboBox>
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

//Concrete
private:
    QTemporaryFile _tmp_file;
    QVector<Generator*> _columns_generators ;
    QString default_column_name_prefix = "colonne ";
    qint8 default_columns_count = 3 ;
    void updateGeneratorUI();
    generator_s build_gen_s_from_ui() const;
    Generator* buildGenerator(const int generator_type, generator_s gen_s = Generator::build_default_gen_s());

// Refactoring
private:
    void generate_headers(QTextStream &outStream) const;
    void generate_lines(QTextStream &outStream) const;
    void push_back_columns(const int from, const int to);
    void pop_back_columns(const int from, const int to);
    void add_new_generator(const int index, const QString name);
    void remove_generator(const int index);
    Generator * get_current_generator() const;
    Generator* get_generator_at(const int index) const;
    void updateGeneratorBoundsUI(const generator_s gen_s);
    void updateGeneratorCustomItemsUI(const generator_s gen_s);
    int current_generator_index() const;
    int apply_other_generator_index() const;
    int get_current_generator_section() const;
    QComboBox* get_current_generator_combo_box() const;
    QComboBox* get_apply_other_generator_combo_box() const;


public slots:
    void columns_changed(const int nb_cols);
    void column_renamed();
    void update_current_generator();
    void change_current_generator();
    void change_generator_type(const int type_clicked_index);
    void done(int r) override;
    void apply_to_another_generator();
private:
    Ui::RandomGenerationDialog *ui;
};

#endif // RANDOM_GENERATION_DIALOG_H
