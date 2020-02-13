#include "linearinvertedcurve.h"

#include "../invertedlinearconstraint.h"
#include "../invertedlineardistribution.h"

LinearInvertedCurve::LinearInvertedCurve():Curve("Linéaire Inversée"), RestrictionCurve("Linéaire Inversée"), DistributionCurve("Linéaire Inversée")
{

}

ValueConstraint * LinearInvertedCurve::buildValueConstraint(int max_value, int nb_lines) const
{
    return new InvertedLinearConstraint(max_value, nb_lines);
}

DistributiveLaw * LinearInvertedCurve::buildDistributiveLaw() const
{
    return new InvertedLinearDistribution;
}

double LinearInvertedCurve::getY(double x) const
{
    return 1 - x ;
}
