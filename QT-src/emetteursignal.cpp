#include "emetteursignal.h"
#include <QDebug>

EmetteurSignal::EmetteurSignal(QObject *parent) : QObject(parent)
{

}

void EmetteurSignal::emitLastSelectedNodeSignal(){
    qDebug() << "Mon émetteur émet";
    emit lastSelectedNode();
}
