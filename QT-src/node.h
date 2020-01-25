#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

class Edge;

class Node : public QGraphicsItem
{

private:
    qreal radius = 10;
    qreal thickness;
    QColor color;
    QVector<Edge*> edges;

    QPointF newPos;

public:
    Node();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    QVector<Edge*> getEdges() const;

    void addEdge(Edge* edge);
};

#endif // NODE_H
