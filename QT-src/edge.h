#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include "qgraphicsitem.h"
#include <cmath>

class Node;
class EmetteurSignal;

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
    QString name;
    int correspondingLine;

public:
    EmetteurSignal *sigEmet;

    Edge(Node *sourceNode, Node *destNode);

    Node *getSource() const;
    Node *getDest() const;
    QString getName() const;

    void adjust();
    void setColor(QColor color);
    QColor getColor();

    int getCorrespondingLine() const;
    void setCorrespondingLine(int num_line);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EDGE_H
