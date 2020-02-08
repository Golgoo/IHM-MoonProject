#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include "datamodel.h"

class Node;
class Edge;
class GraphView : public QGraphicsView
{
Q_OBJECT

private:
     QGraphicsScene *scene = new QGraphicsScene(this);
     int GRAPHICS_VIEW_DIMENSION = 400;
     QList<Node*> everyNode;
     QList<Edge*> everyEdge;
     void wheelEvent ( QWheelEvent * event ) override;

     int _numScheduledScalings = 0;

private slots:
    void scalingTime(qreal x);
    void animFinished();

public:
    GraphView(QWidget *parent);
    DataModel *modelOfGraph;
    void generateGraphUsingDatas();
    void setModel(DataModel *model);
    QGraphicsScene* getScene();
    QList<Node*> getEveryNode();
    QList<Edge*> getEveryEdge();
};

#endif // GRAPHVIEW_H
