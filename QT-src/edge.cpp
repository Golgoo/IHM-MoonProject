#include "edge.h"
#include "node.h"
#include "math.h"
#include <QDebug>


Edge::Edge(Node *sourceNode, Node *destNode)
    : source(sourceNode), dest(destNode)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

Node *Edge::getSource() const
{
    return source;
}

Node *Edge::getDest() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QPainterPath Edge::shape() const {
    //TODO : à changer si on veut faire des noeuds de différentes formes (classe abstraite ?)
    QPainterPath path;

    QRectF rect(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                          destPoint.y() - sourcePoint.y()));

    //path.addRect(topLeftRectX, topLeftRectY, widthRect, heightRect);
    path.addRect(rect.normalized());

    return path;
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (!source || !dest)
        return;

    //si la distance est quasiment 0 on ne dessine pas la ligne
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    //C'est là qu'on devra changer la couleur, le style des arêtes en fonction de la palette
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    double angle = std::atan2(-line.dy(), line.dx());

    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

//TODO: faire que quand on tire un noeud en dhors de la graphics view, il reste collé au bord et ne sorte pas du cadre
QVariant Edge::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged:
        /*QPointF mousePos = value.toPointF();
        QPointF newPos = mousePos - oldValue;
        oldValue = mousePos;

        qDebug() << "newPos : " << newPos.x() << " y : " << newPos.y();

        qreal srcPosX = sourcePoint.x();
        qreal srcPosY = sourcePoint.y();
        qDebug() << "srcPos : " << srcPosX << " y : " << srcPosY;

        source->setPos(srcPosX + newPos.x(), srcPosY + newPos.y());

        qreal destPosX = destPoint.x();
        qreal destPosY = destPoint.y();
        qDebug() << "destPos : " << destPosX << " y : " << destPosY;
        dest->setPos(destPosX + newPos.x(), destPosY + newPos.y());

        for (Edge* edge : source->getEdges()) {
           // edge->adjust();
        }

        for (Edge* edge : dest->getEdges()) {
            //edge->adjust();
        }*/
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
