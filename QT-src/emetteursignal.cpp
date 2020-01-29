#include "emetteursignal.h"
#include <QDebug>

EmetteurSignal::EmetteurSignal(QObject *parent) : QObject(parent)
{

}

void EmetteurSignal::emitLastSelectedNodeSignal(int id_sommet){
    qDebug() << "Mon émetteur émet";
    emit lastSelectedNode(id_sommet);
}
