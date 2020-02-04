#include "node.h"
#include "edge.h"
#include <QDebug>

Node::Node()
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QVector<Edge*> Node::getEdges() const {
    return edges;
}

void Node::addEdge(Edge* edge) {
    edges << edge;
    //ADJUST DISPENSABLE ?
    edge->adjust();
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
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
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
