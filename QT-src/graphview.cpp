#include "graphview.h"
#include "datamodel.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHash>
#include <QWheelEvent>
#include <QTimeLine>
#include "node.h"
#include "edge.h"
#include "emetteursignal.h"

GraphView::GraphView(QWidget *parent)
    : QGraphicsView(parent)
{
    GRAPHICS_VIEW_DIMENSION = 400;

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(0, 0, 400, 400);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));

    /*TODO:A modifier plus tard ?*/
    setMinimumSize(GRAPHICS_VIEW_DIMENSION, GRAPHICS_VIEW_DIMENSION);
    /*Node *node1 = new Node();
    Node *node2 = new Node();
    Node *node3 = new Node();
    Node *node4 = new Node();
    node1->setPos(50, 50);
    node2->setPos(50, 170);
    node3->setPos(0, 50);
    node4->setPos(120, 30);
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(new Edge(node1, node2));
    scene->addItem(new Edge(node2, node3));
    scene->addItem(new Edge(node4, node1));*/

}

void GraphView::setModel(DataModel *model){
    modelOfGraph = model;
}

QGraphicsScene *GraphView::getScene(){
    return scene;
}

QList<Node*> GraphView::getEveryNode(){
    return everyNode;
}

QList<Edge*> GraphView::getEveryEdge(){
    return everyEdge;
}

void GraphView::generateGraphUsingDatas()
{
    everyEdge.clear();
    everyNode.clear();
    scene->clear();
    scene->update();

    int nb_sommet_in_graph = 0;
    int maxNbSommetOfColumn = 0;

    QList<QHash<QString,int>> list;
    /*TODO: Est-ce que 2 colonnes peuvent partager une même valeur ??????*/
    QHash<QString,Node*> hashOfNodesOfDV;

    for(int col=0; col<modelOfGraph->columnCount(); col++){
        QHash<QString,int> hashOfDV = modelOfGraph->getDistinctValuesOfColumn(col);
        //qDebug() << "taille hashOfDV " << hashOfDV.siz300e() << " " << hashOfDV;
        list.insert(col, hashOfDV);

        nb_sommet_in_graph = nb_sommet_in_graph + hashOfDV.size();
        if(maxNbSommetOfColumn < hashOfDV.size())
            maxNbSommetOfColumn = hashOfDV.size();
    }

    qDebug() << "Il y a " << nb_sommet_in_graph << " sommets dans le graphe";
    /*L'espacement entre les sommets peut varier si un sommet est plus gros qu'un autre ?*/

    int nbSommetsInsere = 0;

    for(int col=0; col < list.size(); col++){
        int indexInColumn = 0;
        int spaceX = GRAPHICS_VIEW_DIMENSION/modelOfGraph->columnCount();
        int spaceY = GRAPHICS_VIEW_DIMENSION/list.at(col).size();
        qDebug() << "spaceY pour col"<<col << " " << spaceY;
        for(auto dv : list.at(col).keys()){
            Node *node = new Node(dv);
            qDebug() << "ooooooooooo" << node->getName();
            node->setPosDansEveryNode(nbSommetsInsere);
            everyNode.push_back(node);
            hashOfNodesOfDV.insert(dv,node);
            //TODO: Enlever le -100, Comment fonctionne repère coordonnées ?
            node->setPos(col*spaceX+50, indexInColumn*spaceY+50);

            QColor nodeColor = QColor::fromHsl((360/nb_sommet_in_graph)*nbSommetsInsere,255,175);
            nbSommetsInsere++;
            node->setColor(nodeColor);

            indexInColumn++;
            scene->addItem(node);
        }
    }


    /*TODO: Les colonnes peuvent ne pas être de même taille ????*/
    for (int col=0; col<modelOfGraph->columnCount()-1; col++) {
        for (int row = 0; row<modelOfGraph->rowCount(); row++) {
            QString val1 = modelOfGraph->getValue(row,col);
            QString val2 = modelOfGraph->getValue(row,col+1);

            val1 = val1+"-"+col;
            val2 = val2+"-"+(col+1);

            qDebug() << val1 << "--" << val2;
            Node *node1 = hashOfNodesOfDV.value(val1);
            Node *node2 = hashOfNodesOfDV.value(val2);
            int nbMaxRow = modelOfGraph->rowCount();
            QColor color = QColor::fromHsl((360/nbMaxRow)*row,255,175);
            //qDebug() << color;
            Edge *e = new Edge(node1, node2);
            e->setColor(color);
            everyEdge.push_back(e);
            e->setCorrespondingLine(row);
            scene->addItem(e);

        }
    }
    scene->update();
}

void GraphView::wheelEvent ( QWheelEvent * event )
{
 int numDegrees = event->delta() / 8;
 int numSteps = numDegrees / 15; // see QWheelEvent documentation
 _numScheduledScalings += numSteps;
 if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
 _numScheduledScalings = numSteps;

 QTimeLine *anim = new QTimeLine(350, this);
 anim->setUpdateInterval(20);

 connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
 connect(anim, SIGNAL (finished()), SLOT (animFinished()));
 anim->start();
}

void GraphView::animFinished()
{
 if (_numScheduledScalings > 0)
 _numScheduledScalings--;
 else
 _numScheduledScalings++;
 sender()->~QObject();
}

void GraphView::scalingTime(qreal x)
{
 qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
 scale(factor, factor);
}
