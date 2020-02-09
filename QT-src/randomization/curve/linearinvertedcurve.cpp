#include "linearinvertedcurve.h"

#include "../invertedlinearconstraint.h"

LinearInvertedCurve::LinearInvertedCurve():RestrictionCurve("Linéaire Inversée")
{

}

ValueConstraint * LinearInvertedCurve::buildValueConstraint(int max_value, int nb_lines) const
{
    return new InvertedLinearConstraint(max_value, nb_lines);
}

double LinearInvertedCurve::getY(double x) const
{
    return 1 - x ;
}
