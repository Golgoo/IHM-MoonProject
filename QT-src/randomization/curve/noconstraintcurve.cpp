#include "noconstraintcurve.h"

#include "../noconstraint.h"


NoConstraintCurve::NoConstraintCurve(): Curve("Aucune"), RestrictionCurve("Aucune")
{

}

ValueConstraint * NoConstraintCurve::buildValueConstraint(int max_value, int nb_lines) const
{
    return new NoConstraint(max_value, nb_lines);
}

double NoConstraintCurve::getY(double x) const
{
    Q_UNUSED(x);
    return 0.95;
}
