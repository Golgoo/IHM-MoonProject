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

#include <QColorDialog>

#include <vector>

#include "backgroundcsvreader.h"

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

signals:
    void testSignal(const QColor &color);

protected:
    void on_read_operation_finished();

    void on_read_operation_error(QString error);

    void on_read_operation_new_lines(int line_start, vector<QStringList> line);

private:
    Ui::MainWindow *ui;
    /*On crée String contenant nom du fichier avec lequel on va travailler*/
    QString currentFile = "";
    QFile file ;
    BackgroundCSVReader * csvReader = nullptr ;
    int lastSelectedSommet =-1;
    Edge *lastSelectedEdge;

    QColorDialog *myTablet;

    enum LAST_SELECTED_OBJECT{VERTEX, EDGE, NOTHING};

    LAST_SELECTED_OBJECT lastSelect = NOTHING;
};
#endif // MAINWINDOW_H
