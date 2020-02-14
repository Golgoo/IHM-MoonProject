#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*Bibliothèque que je rajoute en plus*/
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QStringList>
#include <QPrintDialog>
#include <QActionGroup>

#include <QColorDialog>

#include <vector>

#include "datamodel.h"
#include "randomization/generation_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Edge;

class MainWindow : public QMainWindow
{
    /*Chaque Q_OBJECT QUE l'on déclare sera un objet qui s'éxécutera sur son propre thread*/
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief set_status affiche un message dans la barre de statut
     * @param status_text
     */
    void set_status(QString status_text);

private slots:
    /*Ouvre la fenêtre de dialogue servant à la génération de données aléatoire*/
    void on_actionGenerate_triggered();

   /* Ouvre la fenêtre de dialogue  pour sélectionner un fichier csv et ainsi générer les différentes représentations des données
    * si le fichier ouvert est valide */
    void on_actionOpen_triggered();

    /* Ouvre la fenêtre de dialogue  pour sélectionner le dossier de destination de l'export et son nom */
    void on_actionExport_triggered();

    /* ferme le logiciel*/
    void on_actionExit_triggered();

    /* Ouvre la palette de couleur pour changer couleur sommet/arête */
    void on_actionChanger_couleur_triggered();

    /* Lors que l'utilisateur sélectionne une couleur pendant que la palette est ouverte, ce slot la reçoit et mets à jour le graphe
     * en temps réel pour les sommets*/
    void onColorTabletChanged(const QColor &color);

    /* réceptionne id du dernier sommet sélectionné par l'utilisateur et mets à jour les données du programme*/
    void updateLastSelectedNode(int id_sommet);

    /* réceptionne la dernière arête sélectionnée par l'utilisateur et mets à jour les données du programme*/
    void updateLastSelectedEdge(Edge &e);

    /**
     * @brief getEveryEdgeOfLine retourne toutes les arêtes représentative de "num_line"
     * @param num_line : la ligne des données dont on veut l'arête représentative
     * @return une liste avec toutes les arêtes représentative de la ligne "num_line"
     */
    QList<Edge*> getEveryEdgeOfLine(int num_line);

    /* Les 3 slots permettant l'affichage de diverses vues, celle proposé par le menu "View"*/
    void on_actionTabulaire_triggered();
    void on_actionGraphique_triggered();
    void on_actionGlobale_triggered();

    /* sauvegarde CSV */
    void on_actionSaveTableur_triggered();

    /* Export du graphe */
    void on_actionGraphe_triggered();

signals:
    void testSignal(const QColor &color);


protected:

    /* traitement à la fin de la lecture du fichier csv : update statusBar*/
    void on_read_operation_finished();
    /* traitement lors erreur de lecture du fichier csv : update statusBar*/
    void on_read_operation_error(QString error);
    /* traitement lorsque fenêtre redimensionné*/
    void resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow *ui;
    /*On crée String contenant nom du fichier avec lequel on travaille*/
    QString currentFile = "";
    QFile file ;
    int lastSelectedSommet =-1; /*id du dernier sommet sélectionné par l'utilisateur*/
    Edge *lastSelectedEdge; /*pointeur vers la dernière arête sélectionné par utilisateur*/
    QColorDialog *myTablet; /* palette de couleur*/

    enum LAST_SELECTED_OBJECT{VERTEX, EDGE, NOTHING}; /*type du dernier objet sélectionné par l'utilisateur*/
    LAST_SELECTED_OBJECT lastSelect = NOTHING; /*dernier objet sélectionné*/

    DataModel * _model = nullptr;
    generation_dialog * _rdm_gene_dial = nullptr ;
    QActionGroup * _view_actions_group = nullptr;


    void hide_tabular_view() const ; /*cache vue tabulaire*/
    void show_tabular_view() const ; /*affiche vue tabulaire*/
    void hide_graphic_view() const ; /*cache vue du graphe*/
    void show_graphic_view() const ; /*cache vue du graphe*/

    /**
     * @brief reload_model recharge le modèle avec un nouveau fichier
     * @param filename chemin vers le nouveau fichier sur lequel va reposer le nouveau modèle
     */
    void reload_model(QString filename);
    /* cette fonction fait remonter toutes les sélections d'objets avec des slots et signaux*/
    void connectForlastSelectedObjects();
};
#endif // MAINWINDOW_H
