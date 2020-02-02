#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include "qgraphicsitem.h"
#include <cmath>

class Node;

class Edge : public QGraphicsItem
{

private:
    Node *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;

    qreal thickness;
    QColor color;

    QPointF oldValue;

public:
    Edge(Node *sourceNode, Node *destNode);

    Node *getSource() const;
    Node *getDest() const;

    void adjust();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EDGE_H
