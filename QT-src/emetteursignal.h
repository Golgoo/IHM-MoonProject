#ifndef EMETTEURSIGNAL_H
#define EMETTEURSIGNAL_H

#include <QObject>

class EmetteurSignal : public QObject
{
    Q_OBJECT
public:
    EmetteurSignal(QObject *parent = nullptr);
    void emitLastSelectedNodeSignal();

signals:
    void lastSelectedNode();
};

#endif // SIGNALEMITTER_H
