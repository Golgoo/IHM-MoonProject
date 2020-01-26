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

#include <vector>

#include "backgroundcsvreader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

protected:
    void on_read_operation_finished();

    void on_read_operation_error(QString error);

private:
    Ui::MainWindow *ui;
    /*On crée String contenant nom du fichier avec lequel on va travailler*/
    QString currentFile = "";
    QFile file ;
};
#endif // MAINWINDOW_H
