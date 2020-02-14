#include "emetteursignal.h"
#include <QDebug>
#include "edge.h"
#include "node.h"

EmetteurSignal::EmetteurSignal(QObject *parent) : QObject(parent)
{

}

void EmetteurSignal::emitLastSelectedNodeSignal(int id_sommet){
    emit lastSelectedNode(id_sommet);
}

void EmetteurSignal::emitLastSelectedEdgeSignal(Edge *e){
    Edge &edge = *e;
    emit lastSelectedEdge(edge);
}



