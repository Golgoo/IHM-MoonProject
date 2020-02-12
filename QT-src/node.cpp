#include "node.h"
#include "emetteursignal.h"
#include "edge.h"
#include <QDebug>
#include "ui_mainwindow.h"

qreal Node::ratio = 1;

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
        if (this->scene() != nullptr) {
            if (pos().x() < radius) {
                this->setX(radius);
            }
            if (pos().y() < radius) {
                this->setY(radius);
            }
            qreal width = scene()->views().first()->width();
            qreal height = scene()->views().first()->height();
            //qDebug() << "RATIO : " << Node::ratio;
            if (pos().x() >= width * 1.2465 * Node::ratio - radius) {
                this->setX(width * 1.2465 * Node::ratio - radius);
            }
            if (pos().y() >= height *1.2465 *  Node::ratio - radius) {
                this->setY(height  * 1.2465 * Node::ratio - radius);
            }

            for (Edge *edge : getEdges()) {
                edge->adjust();
            }
        }

        break;
    default:
        break;
    };
    qDebug() << "Pos du sommet manipulé " << pos().x() << " " << pos().y();

    return QGraphicsItem::itemChange(change, value);
}

void Node::adjust() {

}

qreal Node::getRadius() {
    return radius;
}
