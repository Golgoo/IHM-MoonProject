#include "node.h"
#include "emetteursignal.h"
#include "edge.h"
#include <QDebug>
#include "ui_mainwindow.h"

qreal Node::ratio = 1;

/**
 * @brief Node::Node
 * @param name
 * On met le flag ItemIsMovable et ItemSendsGeometryChanges car un noeud est déplaçable
 * en le sélectionnant et en laissant le clic appuyé
 */
Node::Node(QString name)
{
    /*Cette ligne permet la sélection des sommets*/
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    this->name = name;
    sigEmet = new EmetteurSignal;
}

QVector<Edge*> Node::getEdges() const {
    return edges;
}

void Node::addEdge(Edge* edge) {
    edges << edge;
    edge->adjust();
}

QString Node::getName() {
    return name;
}

QRectF Node::boundingRect() const {
    return QRectF(-radius, -radius, radius * 2, radius * 2);
}

QPainterPath Node::shape() const {
    QPainterPath path;
    path.addEllipse(-radius, -radius, radius * 2, radius * 2);
    return path;
}



void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void Node::setColor(QColor color){
    this->color = color;
}

QColor Node::getColor(){
    return this->color;
}

int Node::getPosDansEveryNode(){
    return posDansEveryNode;
}

void Node::setPosDansEveryNode(int pos){
    posDansEveryNode = pos;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event){
        Node *node = this;
        sigEmet->emitLastSelectedNodeSignal(node->getPosDansEveryNode());
}

/**
 * @brief Node::itemChange
 * @param change
 * @param value
 * Lorsque le noeud est sélectionné, il faut faire attention à ce qu'il ne puisse pas sortir de l'écran.
 * @return
 */
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged:
        if (this->scene() != nullptr) {
            if (pos().x() < radius) {
                this->setX(radius);
            }
            if (pos().y() < radius) {
                this->setY(radius);
            }
            qreal width = scene()->views().first()->width();
            qreal height = scene()->views().first()->height();

            /*if (pos().x() >= width * 1.2465 * Node::ratio - radius) {

                this->setX(width * 1.2465 * Node::ratio - radius);
            }
            if (pos().y() >= height * 1.2465 *  Node::ratio - radius) {
                this->setY(height  * 1.2465 * Node::ratio - radius);
            }*/

            for (Edge *edge : getEdges()) {
                edge->adjust();
            }
        }

        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}



qreal Node::getRadius() {
    return radius;
}

void Node::setRadius(qreal r){
    radius = r;
}

void Node::setPonderation(int n){
    ponderation = n;
}

int Node::getPonderation() const{
    return ponderation;
}
