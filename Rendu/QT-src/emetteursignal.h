#ifndef EMETTEURSIGNAL_H
#define EMETTEURSIGNAL_H

#include <QObject>

class Edge;
/**
 * @brief La classe EmetteurSignal permet de lancer des signaux à partir d'objets ne pouvant hériter de Q_OBJECT (nécessaire pour utiliser signaux/slots)
 */
class EmetteurSignal : public QObject
{
    Q_OBJECT
public:
    EmetteurSignal(QObject *parent = nullptr);
    /**
     * @brief emitLastSelectedNodeSignal envoie un signal avec l'id du dernier sommet sélectionné par un l'utilisateur
     * @param id_sommet : id du dernier sommet sélectionné
     */
    void emitLastSelectedNodeSignal(int id_sommet);
    /**
     * @brief emitLastSelectedEdgeSignal envoie un signal avec la référence de la dernière arête sélectionné par un l'utilisateur
     * @param e : pointeur sur l'objet Edge correspondant à la dernière arête sélectionné
     */
    void emitLastSelectedEdgeSignal(Edge *e);

signals:
    /**
     * @brief lastSelectedNode : signal utilisé par la fonction "emitLastSelectedNodeSignal"
     * @param id_sommet
     */
    void lastSelectedNode(int id_sommet);
    /**
     * @brief lastSelectedEdge : signal utilisé par la fonction "emitLastSelectedEdgeSignal"
     * @param e
     */
    void lastSelectedEdge(Edge &e);

};

#endif // SIGNALEMITTER_H
