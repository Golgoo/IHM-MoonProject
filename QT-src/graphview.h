#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include "datamodel.h"

class Node;
class Edge;
/**
 * @brief La classe GraphView s'occupe de gérer tout ce qui va s'afficher sur le widget QGraphicsView qui va contenir le graphe
 */
class GraphView : public QGraphicsView
{
Q_OBJECT

private:

     QGraphicsScene *scene = new QGraphicsScene(this); /*Scène de la QGraphicsView*/
     int GRAPHICS_VIEW_DIMENSION = 400; /* Dimension de départ de la scène*/
     QList<Node*> everyNode; /*Liste de tous les noeuds du graphe*/
     QList<Edge*> everyEdge; /*Liste de toutes les arêtes du graphe*/
     int _numScheduledScalings = 0;
     qreal ratio = 1;
     qreal initial_ratio = 1;
     void wheelEvent ( QWheelEvent * event ) override; /* override pour traiter les scrolls de molette pour le zoom du graphe*/
private slots:

public:
    GraphView(QWidget *parent);
    DataModel *modelOfGraph; /*pointeur vers le modèle qui va servir à la génération du graphe*/
    void generateGraphUsingDatas(); /*Génère le graphe à partir du modèle*/
    /**
     * @brief setModel Définit le modèle du graphe
     * @param model : pointeur du modèle qui va servir au graphe
     */
    void setModel(DataModel *model);
    QGraphicsScene* getScene(); /*Récupère la scène affichant le graphe*/
    QList<Node*> getEveryNode(); /*Récupère tous les noeuds du graphe*/
    QList<Edge*> getEveryEdge(); /*Récupère toutes les arêtes du graphe*/
};

#endif // GRAPHVIEW_H
