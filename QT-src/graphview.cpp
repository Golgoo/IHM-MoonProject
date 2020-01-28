#include "graphview.h"
#include "node.h"
#include "edge.h"

GraphView::GraphView(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 400, 400);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);

    Node *node1 = new Node();
    Node *node2 = new Node();
    Node *node3 = new Node();
    Node *node4 = new Node();
    node1->setPos(50, 50);
    node2->setPos(50, 100);
    node3->setPos(0, 50);
    node4->setPos(120, 30);
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(new Edge(node1, node2));
    //scene->addItem(new Edge(node2, node3));
    //scene->addItem(new Edge(node4, node1));


}
