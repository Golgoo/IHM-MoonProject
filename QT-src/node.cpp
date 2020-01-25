#include "node.h"

Node::Node()
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
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
    painter->drawEllipse(-7, -7, 20, 20);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged:
        /*
        for (Edge *edge : qAsConst(edgeList))
            edge->adjust();
        graph->itemMoved();*/
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
