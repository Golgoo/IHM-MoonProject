#include "edge.h"
#include "node.h"
#include "math.h"
#include <QDebug>
#include "emetteursignal.h"


/**
 * @brief Edge::Edge
 * @param sourceNode
 * @param destNode
 * On met le flag ItemIsMovable et ItemSendsGeometryChanges car une arête est déplaçable
 * en la sélectionnant et en laissant le clic appuyé et car elle peut changer de longueur et d'angle.
 */
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

    name = sourceNode->getName() + " -- " + destNode->getName();

    sigEmet = new EmetteurSignal;
}

QString Edge::getName() const {
    return name;
}

QColor Edge::getColor() {
    return color;
}

void Edge::setCorrespondingLine(int num_line){
    correspondingLine = num_line;
}

int Edge::getCorrespondingLine() const{
    return correspondingLine;
}

Node *Edge::getSource() const
{
    return source;
}

Node *Edge::getDest() const
{
    return dest;
}

void Edge::setColor(QColor color){
    this->color = color;
}

/**
 * @brief Edge::adjust
 * Cette fonction est appelée dès que l'affichage de l'arête a besoin d'être changée. Elle modifie
 * sourcePoint et destPoint, qui sont les 2 points qui sont utilisés pour dessigner la ligne
 * correspondant à l'arête.
 */
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

/**
 * @brief Edge::shape
 * Cette fonction détermine la zone de sélection d'une arête, c'est-à-dire la zone qui
 * lorsque l'on clique à l'intérieur déclenchera la fonction itemChange avec le flag ItemPositionHasChanged.
 * Cette zone correspond à l'intérieur d'un polygone à 4 côtés qui est un rectangle si les 2 noeuds de l'arête
 * ont le même rayon. La longueur de ce rectangle est alors la longueur de l'arête et sa largeur le diamètre des
 * noeuds tel que le vecteur directeur du côté longueur du rectangle est parallèle à l'arête et celui du côté largeur
 * lui est perpendiculaire.
 * @return
 */
QPainterPath Edge::shape() const {
    QPainterPath path;

    qreal vx = fabs(sourcePoint.x() - destPoint.x());
    qreal vy = fabs(sourcePoint.y() - destPoint.y());

    qreal nx = vy;
    qreal ny = -vx;

    qreal length = sqrt(pow(nx,2) + pow(ny,2));

    qreal normalized_nx = nx / length;
    qreal normalized_ny = ny / length;

    if ((sourcePoint.x() < destPoint.x() && sourcePoint.y() < destPoint.y()) || (destPoint.x() < sourcePoint.x() && destPoint.y() < sourcePoint.y())) {
        QPointF point1(sourcePoint.x() + normalized_nx * source->getRadius(), sourcePoint.y() + normalized_ny * source->getRadius());
        QPointF point2(sourcePoint.x() - normalized_nx * source->getRadius(), sourcePoint.y() - normalized_ny * source->getRadius());
        QPointF point3(destPoint.x() + normalized_nx * dest->getRadius(), destPoint.y() + normalized_ny * dest->getRadius());
        QPointF point4(destPoint.x() - normalized_nx * dest->getRadius(), destPoint.y() - normalized_ny * dest->getRadius());

        QPolygonF edge_hitbox(QVector<QPointF> {point3, point4, point2, point1});
        path.addPolygon(edge_hitbox);
    }
    else {
        QPointF point1(sourcePoint.x() + normalized_nx * source->getRadius(), sourcePoint.y() - normalized_ny * source->getRadius());
        QPointF point2(sourcePoint.x() - normalized_nx * source->getRadius(), sourcePoint.y() + normalized_ny * source->getRadius());
        QPointF point3(destPoint.x() + normalized_nx * dest->getRadius(), destPoint.y() - normalized_ny * dest->getRadius());
        QPointF point4(destPoint.x() - normalized_nx * dest->getRadius(), destPoint.y() + normalized_ny * dest->getRadius());

        QPolygonF edge_hitbox(QVector<QPointF> {point3, point4, point2, point1});
        path.addPolygon(edge_hitbox);
    }


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

/**
 * @brief Edge::paint
 * @param painter
 * @param option inutilisé
 * @param widget inutilisé
 * La fonction qui dessine une arête, c'est-à-dire la ligne reliant les 2 noeuds et les flèches.
 */
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (!source || !dest)
        return;

    //si la distance est quasiment 0 on ne dessine pas la ligne
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(color, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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

    painter->setBrush(color);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

/**
 * @brief Edge::itemChange
 * @param change
 * @param value
 * Cette fonction permet d'actualiser l'affichage de l'arête.
 * @return
 */
QVariant Edge::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged:

        QPointF mousePos = value.toPointF();
        QPointF newPos = mousePos - oldValue;
        oldValue = mousePos;

        source->moveBy(newPos.x(), newPos.y());
        dest->moveBy(newPos.x(), newPos.y());

        for (Edge* edge : source->getEdges()) {
            edge->adjust();
        }

        for (Edge* edge : dest->getEdges()) {
            edge->adjust();
        }
        break;

    };

    return QGraphicsItem::itemChange(change, value);
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event){
        //qDebug() << "Je suis l'arête " <<  this;
        sigEmet->emitLastSelectedEdgeSignal(this);
}
