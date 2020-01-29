#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

class Edge;
class EmetteurSignal;
class Node : public QGraphicsItem
{

private:
    QString name;
    qreal radius = 10;
    qreal thickness;
    QColor color;
    QVector<Edge*> edges;
    QPointF newPos;

public:
    Node(QString name = "");
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setColor(QColor color);

    EmetteurSignal *sigEmet;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QVector<Edge*> getEdges() const;
    QString getName();

    void addEdge(Edge* edge);
};

#endif // NODE_H
