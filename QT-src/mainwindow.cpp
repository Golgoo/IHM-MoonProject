#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backgroundcsvreader.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QThread>
/*C'est ici qu'on va définir toutes nos fonctionnalités*/

#include "datamodel.h"

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
    //TODO: Code pour générer des données
}

/*A partir d'ici voir toutes les instructions qu'on détaille pour les slots(ce qui suit...)*/
void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "Rentre ici " ;
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    //QFile file(filename);
    currentFile = filename;
    /*if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Attention", "Echec ouverture fichier : "+ file.errorString());
        return;
    }*/
    setWindowTitle(filename);


    ui->tableView->setModel(new DataModel(filename));
}

void MainWindow::on_read_operation_error(QString error)
{
     QMessageBox::warning(this, "Attention", error);
}

void MainWindow::on_read_operation_finished()
{
    //TODO : Stop feedback
    delete csvReader;
    csvReader = nullptr;
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
