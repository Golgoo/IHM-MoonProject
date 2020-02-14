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
#include <QTransform>
#include <QScrollBar>

GraphView::GraphView(QWidget *parent)
    : QGraphicsView(parent)
{
    //constante magique 498.6/400
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
   initial_ratio = ratio = QGraphicsView::transform().m11();

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

        list.insert(col, hashOfDV);

        nb_sommet_in_graph = nb_sommet_in_graph + hashOfDV.size();
        if(maxNbSommetOfColumn < hashOfDV.size())
            maxNbSommetOfColumn = hashOfDV.size();
    }

    qDebug() << "Il y a " << nb_sommet_in_graph << " sommets dans le graphe";
    /*L'espacement entre les sommets peut varier si un sommet est plus gros qu'un autre ?*/

    int nbSommetsInsere = 0;
    int lengthOfLargestCol = 0; /*taille de la colonne ayant le plus de val distinctes*/

    for(int col=0; col < list.size(); col++){
        if(list.at(col).size() > lengthOfLargestCol)
            lengthOfLargestCol = list.at(col).size();
    }
    int border_space = 20;
    int spaceX;
    int spaceY;
    int dim_scene;

    if(lengthOfLargestCol < modelOfGraph->rowCount()){
        dim_scene = lengthOfLargestCol*60;
        spaceX = dim_scene/modelOfGraph->columnCount();
        //spaceY = 50;
    }
    else{
        dim_scene = lengthOfLargestCol*60;
        spaceX = dim_scene/modelOfGraph->columnCount();
        //spaceY = 50;
    }

    scene->setSceneRect(0,0, dim_scene, dim_scene);
    scale(1,1);
    qDebug() << "dimension de la scene" << dim_scene;

    for(int col=0; col < list.size(); col++){
        int indexInColumn = 0;
        //int spaceX = GRAPHICS_VIEW_DIMENSION/modelOfGraph->columnCount();
        //int spaceY = GRAPHICS_VIEW_DIMENSION/list.at(col).size();
        spaceY = dim_scene/list.at(col).size();
        qDebug() << "spaceY pour col"<<col << " " << spaceY;
        for(auto dv : list.at(col).keys()){
            Node *node = new Node(dv);
            node->setPosDansEveryNode(nbSommetsInsere);
            everyNode.push_back(node);
            hashOfNodesOfDV.insert(dv,node);
            node->setPos(col*spaceX+border_space, indexInColumn*spaceY+border_space);

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

            val1 = val1+"-"+QString("%1").arg(col);
            val2 = val2+"-"+QString("%1").arg(col+1);

            Node *node1 = hashOfNodesOfDV.value(val1);
            Node *node2 = hashOfNodesOfDV.value(val2);
            int nbMaxRow = modelOfGraph->rowCount();
            QColor color = QColor::fromHsl((360/nbMaxRow)*row,255,175);

            Edge *e = new Edge(node1, node2);
            e->setColor(color);
            everyEdge.push_back(e);
            e->setCorrespondingLine(row);
            scene->addItem(e);

        }
    }
    scene->update();
}

void GraphView::wheelEvent(QWheelEvent* event)
{
   const QPointF p0scene = mapToScene(event->pos());

   qreal factor = std::pow(1.001, event->delta());
   scale(factor, factor);

   const QPointF p1mouse = mapFromScene(p0scene);
   const QPointF move = p1mouse - event->pos(); // The move
   horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
   verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
   qDebug() << transform().m11();
   qDebug() << transform().m22();
}
