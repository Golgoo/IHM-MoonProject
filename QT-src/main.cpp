#include "mainwindow.h"

#include <QApplication>
#include <QColorDialog>

//#define Q_APP
#define RANDOM_TEST

#ifdef RANDOM_TEST


#include "randomization/uniformdistribution.h"
#include "randomization/exponentialdistribution.h"
#include "randomization/noconstraint.h"
#include "randomization/columngenerator.h"
#include "randomization/linearconstraint.h"
#include "randomization/generation_dialog.h"
#include <iostream>

#endif

int main(int argc, char *argv[])
{

#if defined Q_APP
    QApplication a(argc, argv); /*Crée l'objet application*/
    MainWindow w;
    w.show();
    return a.exec(); /*Mets l'application dans boucle*/
#elif defined RANDOM_TEST
    (void)argc ; (void)argv;
   /* int nlines = 100 ;
    int distinct_values = 80 ;

    UniformDistribution expDist;
    LinearConstraint valueConstraint(distinct_values, nlines);
    ColumnGenerator colGen(expDist, valueConstraint);

    for (int line=0; line<nlines; ++line) {
      int number = colGen.generate(line);
      std::cout << number << std::endl;
    }
*/
    QApplication a(argc, argv);
    generation_dialog dial;
    dial.setFixedSize(dial.width(),dial.height());
    dial.show();
    return a.exec();
#endif
}
