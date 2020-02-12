#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QThread>
#include <QColorDialog>
#include <QDebug>
#include "emetteursignal.h"
#include "node.h"
#include "edge.h"

#include <QList>
#include "randomization/generation_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->groupBox);
    this->resize(900,400);
    QColor myColor;
    //QObject::connect(this, SIGNAL(testSignal(const QColor)), this, SLOT(onColorTabletChanged(const QColor)));
    myTablet = new QColorDialog();
    QObject::connect(myTablet, SIGNAL(currentColorChanged(const QColor)), this, SLOT(onColorTabletChanged(const QColor)));

//-----------------------------------------------
    _rdm_gene_dial = new generation_dialog(this);
    _view_actions_group = new QActionGroup(this);
    _view_actions_group->addAction(ui->actionTabulaire);
    _view_actions_group->addAction(ui->actionGraphique);
    _view_actions_group->addAction(ui->actionGlobale);
//---------------------------------------------

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
    int execution_code = _rdm_gene_dial->exec();
    if(execution_code == QDialog::Accepted){
        if(_rdm_gene_dial->process_generation()>0){
            qDebug() << "GENERATION TERMINEE _____________";
            reload_model(_rdm_gene_dial->getTemporaryFilename());

            /*Reload graphique*/
            ui->graphicsView->setModel(_model);
            ui->graphicsView->generateGraphUsingDatas();
            connectForlastSelectedObjects();
            /*---------------*/
        }else{
            set_status("Unable to generate data");
        }
    }
}

void MainWindow::on_actionSaveTableur_triggered()
{
    if(_model!=nullptr){
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Exporter tableur"), "",
            tr("Address Book (*.csv);;All Files (*)"));
        if (fileName.isEmpty())
            return;
        else {
            _model->export_csv(fileName);
        }
    }else{
        set_status("Aucun tableur n'est ouvert");
    }
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
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
    currentFile = filename;
    if(filename==""){
        QMessageBox::warning(this, "Warning", "Cannot open file");
        return;
    }
    setWindowTitle(filename);
    reload_model(filename);

    QTextStream in(&file);
    QString text = in.readAll();


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
    connectForlastSelectedObjects();


}

void MainWindow::connectForlastSelectedObjects(){

    for(Node *node : ui->graphicsView->getEveryNode()){
        EmetteurSignal *em = node->sigEmet;
        QObject::connect(em, SIGNAL(lastSelectedNode(int)), this, SLOT(updateLastSelectedNode(int)));
        //qDebug() << "node dans EveryNode : " << node->getName();
    }

    for(Edge *edge : ui->graphicsView->getEveryEdge()){
        EmetteurSignal *em = edge->sigEmet;
        QObject::connect(em, SIGNAL(lastSelectedEdge(Edge&)), this, SLOT(updateLastSelectedEdge(Edge&)));
        //qDebug() << "edge dans EveryEdge : " << edge->getName();
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
    /*ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();*/
}

void MainWindow::show_tabular_view() const
{
    ui->tableView->show();
    /*ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();*/
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

