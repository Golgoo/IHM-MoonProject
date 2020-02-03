#include "node.h"
#include "emetteursignal.h"
#include "edge.h"
#include <QDebug>
#include "ui_mainwindow.h"


Node::Node(QString name)
{
    /*Cette ligne permet la sélection des sommets*/
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    this->name = name;
    sigEmet = new EmetteurSignal;
}

QVector<Edge*> Node::getEdges() const {
    return edges;
}

void Node::addEdge(Edge* edge) {
    edges << edge;
    //ADJUST DISPENSABLE ?
    edge->adjust();
}

QString Node::getName() {
    return name;
}

QRectF Node::boundingRect() const {
    //TODO : à changer si on veut faire des noeuds de différentes formes (classe abstraite ?)
    return QRectF(-radius, -radius, radius * 2, radius * 2);
}

QPainterPath Node::shape() const {
    //TODO : à changer si on veut faire des noeuds de différentes formes (classe abstraite ?)
    QPainterPath path;
    path.addEllipse(-radius, -radius, radius * 2, radius * 2);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*) {
    painter->setPen(Qt::NoPen);
    //painter->setBrush(Qt::darkGreen);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void Node::setColor(QColor color){
    this->color = color;
}

QColor Node::getColor(){
    return this->color;
    //emit lastSelectedNode();
}

int Node::getPosDansEveryNode(){
    return posDansEveryNode;
}

void Node::setPosDansEveryNode(int pos){
    posDansEveryNode = pos;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event){
        qDebug() << "J'ai des tongues " << this;
        qDebug() << "Je suis le sommet " <<  this->getName();
        Node *node = this;
        sigEmet->emitLastSelectedNodeSignal(node->getPosDansEveryNode());
        qDebug() << "Yo voici ma couleur " << node->getColor();
}


QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : getEdges()) {
            edge->adjust();
        }

        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::adjust() {

}

qreal Node::getRadius() {
    return radius;
}
