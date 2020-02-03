#include "mainwindow.h"

#include <QApplication>
#include <QColorDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); /*Crée l'objet application*/
    MainWindow w;
    w.show();
    return a.exec(); /*Mets l'application dans boucle*/
}
