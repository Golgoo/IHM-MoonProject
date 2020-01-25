#ifndef NODE_H
#define NODE_H

#include "qgraphicsitem.h"
#include <QPainter>

class Node : public QGraphicsItem
{

private:
    float radius;
    float thickness;
    QColor color;
    //QVector ou std::vector de Edge&

public:
    Node();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // NODE_H
