#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datatable.h"
#include "csvparser.h"

#include <QDebug>

#include "backgroundcsvreader.h"
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
    QTextStream in(&file);
    QString text = in.readAll();

    CSVParser parser(text);
    DataTable table = parser.parse();
    std::cout << "taille du tableau : " << table.getColumns().size();
    //afficher ici le tableau

    file.close();

    ui->tableView->setModel(new DataModel(filename));
    //QTextStream in(&file);

    /*
    QThread* thread = new QThread;
    if(csvReader != nullptr){
        //Si nouvelle lecture avant que la précédente soit terminée
        delete csvReader;
        csvReader = nullptr;
        ui->tableWidget->clear();
    }
    csvReader = new BackgroundCSVReader(filename, ',', 4);
    csvReader->moveToThread(thread);

    connect(thread, SIGNAL (started()), csvReader, SLOT (process()));
    connect(csvReader, SIGNAL (finished()), thread, SLOT (quit()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));

    connect(csvReader,  &BackgroundCSVReader::finished, this, &MainWindow::on_read_operation_finished);
    connect(csvReader, &BackgroundCSVReader::error, this, &MainWindow::on_read_operation_error);
    qRegisterMetaType<vector<QStringList> >("vector<QStringList>");// <= TODO : Tester si l'appeler seulement une fois suffit
    connect(csvReader, &BackgroundCSVReader::new_lines, this, &MainWindow::on_read_operation_new_lines);

    thread->start();
    qDebug() <<"Lecture en cours" ;
    //TODO : Feedback
    */


    //QString text = in.readAll();
    //TODO: code pour traiter ce qu'on a lu dans fichier
    //file.close();
}

/*
void MainWindow::on_read_operation_new_lines(int line_start, vector<QStringList> lines)
{
    int k = 0 ;
    int i = 0 ;
    QTableWidgetItem * item ;
    qDebug() << lines ;
    for(vector<QStringList>::iterator it = lines.begin() ; it < lines.end() ; it++, i ++){
        for(QString item_str : *it ){
            item = new QTableWidgetItem(item_str);
            ui->tableWidget->setItem(line_start + i, k++, item);
        }
        k = 0 ;
    }
}
*/

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
