#ifndef EMETTEURSIGNAL_H
#define EMETTEURSIGNAL_H

#include <QObject>

class Edge;
class EmetteurSignal : public QObject
{
    Q_OBJECT
public:
    EmetteurSignal(QObject *parent = nullptr);
    void emitLastSelectedNodeSignal(int is_sommet);
    void emitLastSelectedEdgeSignal(Edge *e);
    void emitNewRatioForWindow(qreal x);

signals:
    void lastSelectedNode(int id_sommet);
    void lastSelectedEdge(Edge &e);
    void newRatioForWindow(qreal x );

};

#endif // SIGNALEMITTER_H
