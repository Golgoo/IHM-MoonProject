#include "emetteursignal.h"
#include <QDebug>
#include "edge.h"
#include "node.h"

EmetteurSignal::EmetteurSignal(QObject *parent) : QObject(parent)
{

}

void EmetteurSignal::emitLastSelectedNodeSignal(int id_sommet){
    qDebug() << "Mon émetteur émet";
    emit lastSelectedNode(id_sommet);
}

void EmetteurSignal::emitLastSelectedEdgeSignal(Edge *e){
    qDebug() << "Mon émetteur edge émet";
    Edge &xd = *e;

    emit lastSelectedEdge(xd);
}



