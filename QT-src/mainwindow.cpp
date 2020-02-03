#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "backgroundcsvreader.h"
#include <QTableWidgetItem>
#include <QThread>
#include "datatable.h"
#include "csvparser.h"
#include <QColorDialog>
#include <QDebug>
#include "emetteursignal.h"
#include "node.h"
#include "edge.h"

#include <QList>

/*C'est ici qu'on va définir toutes nos fonctionnalités*/

#include "datamodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); /*Fais l'association entre programme et ui ?*/

    this->setCentralWidget(ui->groupBox);

    QColor myColor;
    //QObject::connect(this, SIGNAL(testSignal(const QColor)), this, SLOT(onColorTabletChanged(const QColor)));
    myTablet = new QColorDialog();
    QObject::connect(myTablet, SIGNAL(currentColorChanged(const QColor)), this, SLOT(onColorTabletChanged(const QColor)));

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

void MainWindow::updateLastSelectedNode(int id_sommet){
    qDebug() << "yeeeeeeahhhhhh " << id_sommet;
    lastSelectedSommet = id_sommet;
    lastSelect = VERTEX;
}

void MainWindow::updateLastSelectedEdge(Edge &e){
    qDebug() << "mon slot capte l'edge " << &e;

    lastSelectedEdge = &e;
    lastSelect = EDGE;
}

/*A partir d'ici voir toutes les instructions qu'on détaille pour les slots(ce qui suit...)*/
void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "Rentre ici " ;
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    currentFile = filename;
    if(filename==""){
        QMessageBox::warning(this, "Warning", "Cannot open file");
        return;
    }
    setWindowTitle(filename);

    QTextStream in(&file);
    QString text = in.readAll();

    CSVParser parser(text);
    DataTable table = parser.parse();
    std::cout << "taille du tableau : " << table.getColumns().size();
    //afficher ici le tableau

    file.close();

    DataModel *model = new DataModel(filename);
    ui->tableView->setModel(model);
    //ui->graphicsView->generateGraphUsingDatas(&model);
    //ui->graphicsView->setModell();
    ui->graphicsView->modelOfGraph = model;
    pthread_yield();
    qDebug() << "modèle finit de construire ??";

    /*Rajouter ici model en paramètre d'une fonction qui génére graphe à partir des données*/
    qDebug() << "Le modèle possède " << ui->graphicsView->modelOfGraph->rowCount() << " rows et " << ui->graphicsView->modelOfGraph->columnCount() << " col";
    ui->graphicsView->setModel(model);
    ui->graphicsView->generateGraphUsingDatas();

    for(Node *node : ui->graphicsView->getEveryNode()){
        EmetteurSignal *em = node->sigEmet;
        QObject::connect(em, SIGNAL(lastSelectedNode(int)), this, SLOT(updateLastSelectedNode(int)));
        qDebug() << "gg " << node->getName();
    }

    for(Edge *edge : ui->graphicsView->getEveryEdge()){
        EmetteurSignal *em = edge->sigEmet;
        QObject::connect(em, SIGNAL(lastSelectedEdge(Edge&)), this, SLOT(updateLastSelectedEdge(Edge&)));
        qDebug() << "lol " << edge->getName();
    }
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

    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
        if (!fileName.isNull())
        {
            QPixmap pixMap = this->ui->graphicsView->grab();
            pixMap.save(fileName);
        }
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

void MainWindow::on_actionChanger_couleur_triggered()
{
    qDebug() << "Ahhhh une palette de couleur ?";

    //QColor myColor = QColorDialog::getColor();
    QColor myColor;

    myTablet->exec();
}

void MainWindow::onColorTabletChanged(const QColor &color)
{
    /*Si aucun sommet sélectionner mieux vaut ne pas autoriser ouverture palette*/
    if(lastSelect == NOTHING)
        return;

    if(lastSelect == VERTEX){
    qDebug() << "couleur gg " << color;
    Node *node = ui->graphicsView->getEveryNode().at(lastSelectedSommet);
    node->setColor(color);
    qDebug() << "Le sommet d'indice " << lastSelectedSommet << " a la couleur " << ui->graphicsView->getEveryNode().at(lastSelectedSommet)->getColor();
    node->update();
    }

    if(lastSelect == EDGE){
        for(Edge *e :getEveryEdgeOfLine(lastSelectedEdge->getCorrespondingLine())){
            e->setColor(color);
            e->update();
        }
    }
}

QList<Edge*> MainWindow::getEveryEdgeOfLine(int num_line){
    QList<Edge*> list;
    for(Edge* e : ui->graphicsView->getEveryEdge())
        if(e->getCorrespondingLine() == num_line)
            list.push_back(e);
    return list;
}


