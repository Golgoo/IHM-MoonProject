#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QThread>

#include <QDebug>
/*C'est ici qu'on va définir toutes nos fonctionnalités*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); /*Fais l'association entre programme et ui ?*/

    this->setCentralWidget(ui->groupBox);
    _rdm_gene_dial = new RandomGenerationDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _rdm_gene_dial;
}


void MainWindow::on_actionGenerate_triggered()
{
    currentFile.clear();

    int execution_code = _rdm_gene_dial->exec();
    if(execution_code == QDialog::Accepted){
        if(_rdm_gene_dial->process_generation()>0){
            reload_model(_rdm_gene_dial->getTemporaryFilename());
        }else{
            // A voir.
            //TODO _rmd_gene_dial.getErrors() : QStringList // Ou Enum + Map<Enum, QString> .... => getErrorString(Enum)...
            //A faire dans une popup
            //A voir ... vérification de formulaire plutôt..
            //Si ErrorEnum != Enum::InternalError() => Réexécuter la dial sinon notifier l'erreur.
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    currentFile = filename;
    setWindowTitle(filename);

    reload_model(filename);
}

void MainWindow::reload_model(QString filename)
{
    if(_model != nullptr){
        delete _model;
        _model = nullptr;
    }
    _model = new DataModel(filename);
    ui->tableView->setModel(_model);
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
