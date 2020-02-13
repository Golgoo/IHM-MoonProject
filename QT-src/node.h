#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

class Edge;
class EmetteurSignal;

/**
  Cette classe regroupe toutes les données d'un noeud du graphe, notamment des données graphiques
  mais aussi les arêtes à laquelles il est lié.
 * @brief The Node class
 */
class Node : public QGraphicsItem
{

private:

    /**
     * @brief name : Le nom du noeud
     */
    QString name;

    /**
     * @brief radius : Le rayon du noeud à l'affichage
     */
    qreal radius = 10;

    qreal thickness;

    /**
     * @brief color La couleur du noeud RGB à l'affichage
     */
    QColor color;

    /**
     * @brief edges Les arêtes liées au noeud
     */
    QVector<Edge*> edges;

    //inutilisé ?
    QPointF newPos;
    int posDansEveryNode;


public:

    /**
     * @brief ratio : le ratio de zoom / dezoom pour pouvoir drag la node dans la limite de la GraphView visible à l'écran.
     */
    static qreal ratio;
    Node(QString name = "");
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setColor(QColor color);
    QColor getColor();

    EmetteurSignal *sigEmet;

    void adjust();
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void setPosDansEveryNode(int pos);
    int getPosDansEveryNode();

    /**
     * @brief getEdges
     * @return les arêtes liées au noeud
     */
    QVector<Edge*> getEdges() const;

    /**
     * @brief getName
     * @return le nom du noeud
     */
    QString getName();

    /**
     * @brief getRadius
     * @return le rayon du noeud
     */
    qreal getRadius();

    /**
     * @brief addEdge ajoute une arête à un noeud
     * @param edge l'arête à lier au noeud
     */
    void addEdge(Edge* edge);
};

#endif // NODE_H
