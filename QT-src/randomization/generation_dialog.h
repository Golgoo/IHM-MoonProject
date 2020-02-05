#ifndef GENERATION_DIALOG_H
#define GENERATION_DIALOG_H

#include "ui_generation_dialog.h"

namespace Ui {
class generation_dialog;
}

class generation_dialog : public QDialog, private Ui::generation_dialog
{
    Q_OBJECT

public:
    explicit generation_dialog(QWidget *parent = nullptr);

private:
    Ui::generation_dialog *ui ;
};

#endif // GENERATION_DIALOG_H
