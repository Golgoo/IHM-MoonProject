#ifndef GENEERRORDIALOG_H
#define GENEERRORDIALOG_H

#include <QDialog>

#include "ui_geneerrordialog.h"

#include <QString>
#include <QStringList>

namespace Ui {
class GeneErrorDialog;
}

class GeneErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneErrorDialog(QWidget *parent = nullptr);
    ~GeneErrorDialog();

    void addError(QString error);
    void addErrors(QStringList errors);

private:
    Ui::GeneErrorDialog *ui;
};

#endif // GENEERRORDIALOG_H
