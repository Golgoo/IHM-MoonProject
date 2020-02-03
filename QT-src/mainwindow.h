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
#include "random_generation_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Edge;
class MainWindow : public QMainWindow
{
    /*Chaque Q_OBJECT QUE l'on déclare sera un objet qui s'éxécutera sur son propre thread*/
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); /*Ce widget n'a pas de parent si nullptr*/
    ~MainWindow();

    void set_status(QString status_text);

private slots:
    void on_actionGenerate_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExport_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionChanger_couleur_triggered();

    void onColorTabletChanged(const QColor &color);

    void updateLastSelectedNode(int id_sommet);
    void updateLastSelectedEdge(Edge &e);

    QList<Edge*> getEveryEdgeOfLine(int num_line);

    void on_actionTabulaire_triggered();

    void on_actionGraphique_triggered();

    void on_actionGlobale_triggered();

signals:
    void testSignal(const QColor &color);


protected:
    void on_read_operation_finished();

    void on_read_operation_error(QString error);

private:
    Ui::MainWindow *ui;
    /*On crée String contenant nom du fichier avec lequel on va travailler*/
    QString currentFile = "";
    QFile file ;
    int lastSelectedSommet =-1;
    Edge *lastSelectedEdge;

    QColorDialog *myTablet;

    enum LAST_SELECTED_OBJECT{VERTEX, EDGE, NOTHING};

    LAST_SELECTED_OBJECT lastSelect = NOTHING;

    DataModel * _model = nullptr;
    RandomGenerationDialog * _rdm_gene_dial = nullptr ;
    QActionGroup * _view_actions_group = nullptr;

    void hide_tabular_view() const ;
    void show_tabular_view() const ;
    void hide_graphic_view() const ;
    void show_graphic_view() const ;

    void reload_model(QString filename);
};
#endif // MAINWINDOW_H
