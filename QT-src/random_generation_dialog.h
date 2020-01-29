#ifndef RANDOM_GENERATION_DIALOG_H
#define RANDOM_GENERATION_DIALOG_H

#include <QDialog>
#include <QTemporaryFile>

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
    QVector<QString> _columns ;
    QString default_column_name = "colonne ";
    qint8 default_columns_count = 3 ;
    int generateRandomInt();

public slots:
    void columns_changed(int nb_cols);
    void column_renamed();

private:
    Ui::RandomGenerationDialog *ui;
};

#endif // RANDOM_GENERATION_DIALOG_H
