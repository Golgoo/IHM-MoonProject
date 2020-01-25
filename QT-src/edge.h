#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include "qgraphicsitem.h"

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

public:
    Edge(Node *sourceNode, Node *destNode);

    Node *getSource() const;
    Node *getDest() const;

    void adjust();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EDGE_H
