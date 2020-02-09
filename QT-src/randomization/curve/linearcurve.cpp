#include "linearcurve.h"

#include "../linearconstraint.h"

LinearCurve::LinearCurve(): RestrictionCurve("Linéaire")
{

}

ValueConstraint * LinearCurve::buildValueConstraint(int max_value, int nb_lines) const
{
    return new LinearConstraint(max_value, nb_lines);
}

double LinearCurve::getY(double x) const
{
    return x ;
}
