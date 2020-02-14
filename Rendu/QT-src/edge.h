#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include "qgraphicsitem.h"
#include <cmath>

class Node;
class EmetteurSignal;

/**
 * @brief The Edge class
 * Cette classe représente une arête, elle contient deux noeuds et des données d'affichage.
 */
class Edge : public QGraphicsItem
{

private:

    /**
     * @brief source, dest
     * Ce sont les deux noeuds liés à l'arête
     */
    Node *source, *dest;

    /**
     * @brief sourcePoint Le point d'intersection entre l'arête et le contour du cercle représentant le noeud source
     */
    QPointF sourcePoint;

    /**
     * @brief destPoint Le point d'intersection entre l'arête et le contour du cercle représentant le noeud destination
     */
    QPointF destPoint;

    /**
     * @brief arrowSize La taille de la flèche au bout de l'arête
     */
    qreal arrowSize = 10;

    qreal thickness;

    /**
     * @brief color La couleur de l'arête
     */
    QColor color;

    QPointF oldValue;

    /**
     * @brief name Le nom de l'arête
     */
    QString name;

    /**
     * @brief correspondingLine la ligne des données à laquelle appartient l'arête
     */
    int correspondingLine;

public:
    EmetteurSignal *sigEmet; /*Emetteur permettant à une arête d'indiquer qu'elle est la dernière arête sélectionnée */

    /**
     * @brief Edge
     * @param sourceNode le noeud source de l'arête
     * @param destNode le noeud destination de l'arête
     */
    Edge(Node *sourceNode, Node *destNode);

    /**
     * @brief getSource
     * @return le noeud source de l'arête
     */
    Node *getSource() const;

    /**
     * @brief getDest
     * @return  le noeud destination de l'arête
     */
    Node *getDest() const;

    /**
     * @brief getName
     * @return le nom de l'arête
     */
    QString getName() const;

    /**
     * @brief adjust
     * Fonction permettant d'ajuster la position, la longueur, l'angle de l'arête à l'affichage
     * lorsqu'un noeud de l'arête ou l'arête elle-même est déplacée.
     */
    void adjust();

    /**
     * @brief setColor
     * @param color : la nouvelle couleur de l'arête
     */
    void setColor(QColor color);

    /**
     * @brief getColor
     * @return la couleur de l'arête RGB
     */
    QColor getColor();

    /**
     * @brief getCorrespondingLine
     * @return renvoie le numéro de la ligne des données à laquelle appartient l'arête
     */
    int getCorrespondingLine() const;

    /**
     * @brief setCorrespondingLine
     * @param num_line définit le numéro de la ligne des données à laquelle appartient l'arête
     */
    void setCorrespondingLine(int num_line);

    /*OVERRIDE*/
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EDGE_H
