#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QThread>
#include <QColorDialog>
#include <QDebug>
#include "emetteursignal.h"
#include "node.h"
#include "edge.h"
#include <QDate>

#include <QList>
#include "randomization/generation_dialog.h"

/*C'est ici qu'on va définir toutes nos fonctionnalités*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); /*Fais l'association entre programme et ui ?*/

    this->setCentralWidget(ui->groupBox);
    this->resize(900,400);
    QMainWindow::statusBar()->resize(30,15);
    myTablet = new QColorDialog();
    /*à chaque nouvelle sélection d'une couleur dans la tablette, on envoie la couleur sélectionné*/
    QObject::connect(myTablet, SIGNAL(currentColorChanged(const QColor)), this, SLOT(onColorTabletChanged(const QColor)));


    _rdm_gene_dial = new generation_dialog(this);

    /*Les différentes vue possible pour les données*/
    _view_actions_group = new QActionGroup(this);
    _view_actions_group->addAction(ui->actionTabulaire);
    _view_actions_group->addAction(ui->actionGraphique);
    _view_actions_group->addAction(ui->actionGlobale);
//---------------------------------------------
    set_status(QString("Prêt à l'emploi"));
    QMainWindow::setStatusBar(ui->statusbar);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _rdm_gene_dial;
    delete _view_actions_group;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    qDebug() << "WIDTH VIEW : " << ui->graphicsView->width();
    qDebug() << "HEIGHT VIEW : " << ui->graphicsView->height();
    qDebug() << "WIDTH SCENE : " << ui->graphicsView->getScene()->width();
    qDebug() << "HEIGHT SCENE : " << ui->graphicsView->getScene()->height();
    ui->graphicsView->getScene()->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
}

void MainWindow::on_actionGenerate_triggered()
{
    currentFile.clear();
    /*On éxécute l'utilitaire pour générer données aléatoirement*/
    int execution_code = _rdm_gene_dial->exec();
    if(execution_code == QDialog::Accepted){
        if(_rdm_gene_dial->process_generation()>0){
            qDebug() << "GENERATION TERMINEE _____________";

            reload_model(_rdm_gene_dial->getTemporaryFilename());

            /*Partie génération des représentations de données*/
            ui->graphicsView->setModel(_model);
            ui->graphicsView->generateGraphUsingDatas();
            connectForlastSelectedObjects();
        }else{
            set_status("Unable to generate data");
        }
    }
}


void MainWindow::updateLastSelectedNode(int id_sommet){
    lastSelectedSommet = id_sommet;
    lastSelect = VERTEX;
    Node *node = ui->graphicsView->getEveryNode().at(lastSelectedSommet);
    ui->selectedObjLabel->setText("A sélectionné le noeud : "+node->getName());
}

void MainWindow::updateLastSelectedEdge(Edge &e){
    ui->selectedObjLabel->setText("A sélectionné l'arête : "+e.getName());
    lastSelectedEdge = &e;
    lastSelect = EDGE;
}

/*A partir d'ici voir toutes les instructions qu'on détaille pour les slots(ce qui suit...)*/
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    currentFile = filename;
    if(filename==""){
        QMessageBox::warning(this, "Warning", "Cannot open file");
        set_status("Echec Ouverture du fichier csv");
        return;
    }
    setWindowTitle(filename);
    reload_model(filename);

    QTextStream in(&file);
    QString text = in.readAll();

    file.close();

    DataModel *model;
    model = new DataModel(filename);
    /*On vérifie conformité du modèle (matrice bien formé)*/
    if(!model->isConform()){
        delete model;
        ui->tableView->setModel(nullptr);
        QMessageBox::warning(this, "Warning", "Fichier non conforme !");
        return;
    }

    /*Dans le cas où le fichier et conforme*/
    ui->tableView->setModel(model);
    ui->graphicsView->modelOfGraph = model;

    qDebug() << "Le modèle possède " << ui->graphicsView->modelOfGraph->rowCount() << " rows et " << ui->graphicsView->modelOfGraph->columnCount() << " col";
    if (ui->graphicsView->modelOfGraph->rowCount()!=0 && ui->graphicsView->modelOfGraph->columnCount()!=0)
    {
        /*On construit le graphe*/
        ui->graphicsView->setModel(model);
        ui->graphicsView->generateGraphUsingDatas();
        connectForlastSelectedObjects();
    }
    set_status("chargement fichier + génération graphe OK");
}

void MainWindow::connectForlastSelectedObjects(){

    for(Node *node : ui->graphicsView->getEveryNode()){
        EmetteurSignal *em = node->sigEmet;
        QObject::connect(em, SIGNAL(lastSelectedNode(int)), this, SLOT(updateLastSelectedNode(int)));
    }

    for(Edge *edge : ui->graphicsView->getEveryEdge()){
        EmetteurSignal *em = edge->sigEmet;
        QObject::connect(em, SIGNAL(lastSelectedEdge(Edge&)), this, SLOT(updateLastSelectedEdge(Edge&)));
    }
}

//---------------------------------------------------------
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
     set_status("Echec ouverture fichier .csv");
}

void MainWindow::on_read_operation_finished()
{
    //TODO : Stop feedback &| MAJ Status bar
    set_status("A fini de lire le fichier ouvert");
}


void MainWindow::set_status(QString status_text)
{
    //QMainWindow::statusBar()->showMessage(status_text);
    ui->statusbar->showMessage(status_text);
}

void MainWindow::on_actionExport_triggered()
{
    /*On récupère destination de l'export*/
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
        if (!fileName.isNull())
        {
            /*Extraction image du graphe*/
            QPixmap pixMap = this->ui->graphicsView->grab();
            pixMap.save(fileName);

            /*partie description des données*/
            QString descriptionfileName=fileName.split(".").first()+".txt";
            QFile file(descriptionfileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
               return;

            QTextStream out(&file);
            out << "File name:"<< fileName.split("/").last() <<"\nnumber of lines: "<< this->_model->rowCount()<<"\nnumber of columns: "<< this->_model->columnCount()<< "\nexport date: (day,mounth,year) " << QDate::currentDate().toString("dd.MM.yyyy") << "\nfichier csv de base: " << this->currentFile.split("/").last();
            set_status(QString("Exportation du graphe réussi"));
        }
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionChanger_couleur_triggered()
{
    if(lastSelect == NOTHING){
        QMessageBox::warning(this, "Warning", "Aucun objet sélectionné");
        return;
    }
    myTablet->exec();
}

void MainWindow::onColorTabletChanged(const QColor &color)
{
    if(lastSelect == NOTHING)
        return;

    if(lastSelect == VERTEX){
        /*On change la couleur du sommet en même temps que la palette est ouverte*/
    Node *node = ui->graphicsView->getEveryNode().at(lastSelectedSommet);
    node->setColor(color);
    node->update();
    }

    if(lastSelect == EDGE){
        /*Change couleur arête*/
        for(Edge *e :getEveryEdgeOfLine(lastSelectedEdge->getCorrespondingLine())){
            e->setColor(color);
            e->update();
            /*change couleur ligne de la table à laquelle appartient l'arête*/
            ui->graphicsView->modelOfGraph->setColorOfLine(lastSelectedEdge->getCorrespondingLine(), color);
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

//--------------------------------------------------
void MainWindow::hide_tabular_view() const
{
    ui->tableView->hide();
}

void MainWindow::show_tabular_view() const
{
    ui->tableView->show();
}

void MainWindow::hide_graphic_view() const
{
    ui->graphicsView->hide();
}

void MainWindow::show_graphic_view() const
{
    ui->graphicsView->show();
}

void MainWindow::on_actionTabulaire_triggered()
{
    hide_graphic_view();
    show_tabular_view();
}

void MainWindow::on_actionGraphique_triggered()
{
    show_graphic_view();
    hide_tabular_view();
}

void MainWindow::on_actionGlobale_triggered()
{
    show_graphic_view();
    show_tabular_view();
}
//------------------------------------------------------------

