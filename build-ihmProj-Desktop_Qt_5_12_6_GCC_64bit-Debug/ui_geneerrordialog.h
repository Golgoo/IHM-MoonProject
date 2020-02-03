/********************************************************************************
** Form generated from reading UI file 'geneerrordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENEERRORDIALOG_H
#define UI_GENEERRORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneErrorDialog
{
public:
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *GeneErrorDialog)
    {
        if (GeneErrorDialog->objectName().isEmpty())
            GeneErrorDialog->setObjectName(QString::fromUtf8("GeneErrorDialog"));
        GeneErrorDialog->resize(671, 90);
        pushButton = new QPushButton(GeneErrorDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(570, 10, 89, 71));
        verticalLayoutWidget = new QWidget(GeneErrorDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 541, 71));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(GeneErrorDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), GeneErrorDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(GeneErrorDialog);
    } // setupUi

    void retranslateUi(QDialog *GeneErrorDialog)
    {
        GeneErrorDialog->setWindowTitle(QApplication::translate("GeneErrorDialog", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("GeneErrorDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeneErrorDialog: public Ui_GeneErrorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENEERRORDIALOG_H
