#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include "datamodel.h"

class GraphView : public QGraphicsView
{
private:
     QGraphicsScene *scene = new QGraphicsScene(this);
     int GRAPHICS_VIEW_DIMENSION = 400;

public:
    GraphView(QWidget *parent);
    DataModel *modelOfGraph;
    void generateGraphUsingDatas();
    void setModel(DataModel *model);
    QGraphicsScene* getScene();
};

#endif // GRAPHVIEW_H
