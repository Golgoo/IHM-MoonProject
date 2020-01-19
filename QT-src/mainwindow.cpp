#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datatable.h"
#include "csvparser.h"

#include <QDebug>

/*C'est ici qu'on va définir toutes nos fonctionnalités*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); /*Fais l'association entre programme et ui ?*/

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
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Attention", "Echec ouverture fichier : "+ file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    //TODO: code pour traiter ce qu'on a lu dans fichier
    //qDebug() << text << '\n';
    CSVParser parser(text);
    parser.parse();

    file.close();

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
