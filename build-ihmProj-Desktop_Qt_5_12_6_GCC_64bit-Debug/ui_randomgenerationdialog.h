/********************************************************************************
** Form generated from reading UI file 'randomgenerationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANDOMGENERATIONDIALOG_H
#define UI_RANDOMGENERATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RandomGenerationDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *DimensionLayout;
    QLabel *label_2;
    QHBoxLayout *rows_layout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpinBox *nb_rows;
    QHBoxLayout *columns_layout;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *nb_cols;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *DataLayout;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *current_generator_combo_box;
    QLineEdit *column_name_form;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QVBoxLayout *form_layout;
    QHBoxLayout *borne_inf_layout;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QSpinBox *borne_inf;
    QHBoxLayout *borne_sup_layout;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *borne_sup;
    QWidget *tab;
    QTextEdit *textEdit;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QComboBox *apply_to_other_combo_box;
    QPushButton *pushButton_2;

    void setupUi(QDialog *RandomGenerationDialog)
    {
        if (RandomGenerationDialog->objectName().isEmpty())
            RandomGenerationDialog->setObjectName(QString::fromUtf8("RandomGenerationDialog"));
        RandomGenerationDialog->resize(554, 439);
        buttonBox = new QDialogButtonBox(RandomGenerationDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(370, 400, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(RandomGenerationDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 325, 87));
        DimensionLayout = new QVBoxLayout(verticalLayoutWidget);
        DimensionLayout->setObjectName(QString::fromUtf8("DimensionLayout"));
        DimensionLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignCenter);

        DimensionLayout->addWidget(label_2);

        rows_layout = new QHBoxLayout();
        rows_layout->setObjectName(QString::fromUtf8("rows_layout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        rows_layout->addWidget(label);

        horizontalSpacer = new QSpacerItem(700, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        rows_layout->addItem(horizontalSpacer);

        nb_rows = new QSpinBox(verticalLayoutWidget);
        nb_rows->setObjectName(QString::fromUtf8("nb_rows"));
        nb_rows->setMaximum(100000000);
        nb_rows->setValue(10);

        rows_layout->addWidget(nb_rows);

        rows_layout->setStretch(0, 100);

        DimensionLayout->addLayout(rows_layout);

        columns_layout = new QHBoxLayout();
        columns_layout->setObjectName(QString::fromUtf8("columns_layout"));
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        columns_layout->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(700, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        columns_layout->addItem(horizontalSpacer_4);

        nb_cols = new QSpinBox(verticalLayoutWidget);
        nb_cols->setObjectName(QString::fromUtf8("nb_cols"));
        nb_cols->setMinimum(1);
        nb_cols->setMaximum(100000000);
        nb_cols->setValue(10);

        columns_layout->addWidget(nb_cols);


        DimensionLayout->addLayout(columns_layout);

        verticalLayoutWidget_2 = new QWidget(RandomGenerationDialog);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 130, 531, 261));
        DataLayout = new QVBoxLayout(verticalLayoutWidget_2);
        DataLayout->setObjectName(QString::fromUtf8("DataLayout"));
        DataLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        DataLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        current_generator_combo_box = new QComboBox(verticalLayoutWidget_2);
        current_generator_combo_box->setObjectName(QString::fromUtf8("current_generator_combo_box"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(current_generator_combo_box->sizePolicy().hasHeightForWidth());
        current_generator_combo_box->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(current_generator_combo_box);

        column_name_form = new QLineEdit(verticalLayoutWidget_2);
        column_name_form->setObjectName(QString::fromUtf8("column_name_form"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(6);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(column_name_form->sizePolicy().hasHeightForWidth());
        column_name_form->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(column_name_form);

        pushButton = new QPushButton(verticalLayoutWidget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        DataLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(verticalLayoutWidget_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setCursor(QCursor(Qt::ArrowCursor));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 501, 121));
        form_layout = new QVBoxLayout(layoutWidget);
        form_layout->setObjectName(QString::fromUtf8("form_layout"));
        form_layout->setContentsMargins(0, 0, 0, 0);
        borne_inf_layout = new QHBoxLayout();
        borne_inf_layout->setObjectName(QString::fromUtf8("borne_inf_layout"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        borne_inf_layout->addWidget(label_6);

        horizontalSpacer_5 = new QSpacerItem(700, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        borne_inf_layout->addItem(horizontalSpacer_5);

        borne_inf = new QSpinBox(layoutWidget);
        borne_inf->setObjectName(QString::fromUtf8("borne_inf"));
        borne_inf->setMinimum(-100000000);
        borne_inf->setMaximum(100000000);
        borne_inf->setValue(0);

        borne_inf_layout->addWidget(borne_inf);


        form_layout->addLayout(borne_inf_layout);

        borne_sup_layout = new QHBoxLayout();
        borne_sup_layout->setObjectName(QString::fromUtf8("borne_sup_layout"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        borne_sup_layout->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(700, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        borne_sup_layout->addItem(horizontalSpacer_3);

        borne_sup = new QSpinBox(layoutWidget);
        borne_sup->setObjectName(QString::fromUtf8("borne_sup"));
        borne_sup->setMinimum(-100000000);
        borne_sup->setMaximum(100000000);
        borne_sup->setValue(0);

        borne_sup_layout->addWidget(borne_sup);


        form_layout->addLayout(borne_sup_layout);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(30, 10, 461, 81));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(230, 100, 261, 20));
        tabWidget->addTab(tab, QString());

        DataLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_2->addWidget(label_8);

        apply_to_other_combo_box = new QComboBox(verticalLayoutWidget_2);
        apply_to_other_combo_box->setObjectName(QString::fromUtf8("apply_to_other_combo_box"));

        horizontalLayout_2->addWidget(apply_to_other_combo_box);

        pushButton_2 = new QPushButton(verticalLayoutWidget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        DataLayout->addLayout(horizontalLayout_2);


        retranslateUi(RandomGenerationDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RandomGenerationDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RandomGenerationDialog, SLOT(reject()));
        QObject::connect(current_generator_combo_box, SIGNAL(currentTextChanged(QString)), column_name_form, SLOT(setText(QString)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(RandomGenerationDialog);
    } // setupUi

    void retranslateUi(QDialog *RandomGenerationDialog)
    {
        RandomGenerationDialog->setWindowTitle(QApplication::translate("RandomGenerationDialog", "Dialog", nullptr));
        label_2->setText(QApplication::translate("RandomGenerationDialog", "Dimension", nullptr));
        label->setText(QApplication::translate("RandomGenerationDialog", "Nombre de lignes :", nullptr));
        label_5->setText(QApplication::translate("RandomGenerationDialog", "Nombre de colonnes :", nullptr));
        label_3->setText(QApplication::translate("RandomGenerationDialog", "Donn\303\251es g\303\251n\303\251r\303\251es", nullptr));
        column_name_form->setText(QString());
        pushButton->setText(QApplication::translate("RandomGenerationDialog", "Renommer", nullptr));
        label_6->setText(QApplication::translate("RandomGenerationDialog", "Borne inf\303\251rieure :", nullptr));
        label_4->setText(QApplication::translate("RandomGenerationDialog", "Borne sup\303\251rieure :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("RandomGenerationDialog", "Enti\303\250res", nullptr));
        label_7->setText(QApplication::translate("RandomGenerationDialog", "S\303\251parez vos items avec un retour ligne", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RandomGenerationDialog", "Personalis\303\251es", nullptr));
        label_8->setText(QApplication::translate("RandomGenerationDialog", "Appliquer ce mod\303\250le pour une autre colonne ", nullptr));
        pushButton_2->setText(QApplication::translate("RandomGenerationDialog", "Appliquer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RandomGenerationDialog: public Ui_RandomGenerationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANDOMGENERATIONDIALOG_H
