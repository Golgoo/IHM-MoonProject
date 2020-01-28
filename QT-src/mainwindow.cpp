#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QThread>
#include "datatable.h"
#include "csvparser.h"

#include <QDebug>
/*C'est ici qu'on va définir toutes nos fonctionnalités*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); /*Fais l'association entre programme et ui ?*/

    this->setCentralWidget(ui->groupBox);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionGenerate_triggered()
{
    /*On efface pour laisser place à un nouveau fichier*/
    currentFile.clear();

    _rdm_gene_dial->exec();

    //TODO Ouvrir un formulaire dans une QDialog qui rempli/renvoie une structure :
    // =>NbLines / NbCols / bounds / etc..
    // => (if _model != nullptr ) delete _model
    // => _model = new DataModel(<structure_retournée>);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    currentFile = filename;

    setWindowTitle(filename);

    if(_model != nullptr){
        delete _model;
        _model = nullptr;
    }
    _model = new DataModel(filename);
    ui->tableView->setModel(_model);

    _model->shiftColumn(1,2);
    //Et après ça, la colonne 2 ( l'ancienne colonne 3 ) de 1 cran vers la gauche
    _model->shiftColumn(2,-1);

}

void MainWindow::on_read_operation_error(QString error)
{
     QMessageBox::warning(this, "Attention", error);
}

void MainWindow::on_read_operation_finished()
{
    //TODO : Stop feedback &| MAJ Status bar
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Attention", "Impossible de sauvegarder fichier : "+ file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = "AHHAHAHA"; //:TODO Il faudra mettre ce que l'on voudra stocker dans le fichier dans cette var
    out << text;
    file.close();
}

void MainWindow::set_status(QString status_text)
{
    ui->statusbar->showMessage(status_text);
}

void MainWindow::on_actionExport_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionUndo_triggered()
{

}

void MainWindow::on_actionRedo_triggered()
{

}
