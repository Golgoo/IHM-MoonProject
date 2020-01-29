#ifndef EMETTEURSIGNAL_H
#define EMETTEURSIGNAL_H

#include <QObject>

class EmetteurSignal : public QObject
{
    Q_OBJECT
public:
    EmetteurSignal(QObject *parent = nullptr);
    void emitLastSelectedNodeSignal(int is_sommet);

signals:
    void lastSelectedNode(int id_sommet);
};

#endif // SIGNALEMITTER_H
