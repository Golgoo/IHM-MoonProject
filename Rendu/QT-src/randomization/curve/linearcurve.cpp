#include "linearcurve.h"

#include "../linearconstraint.h"
#include "../lineardistribution.h"

LinearCurve::LinearCurve():Curve("Linéaire"), RestrictionCurve("Linéaire"), DistributionCurve("Linéaire")
{

}

ValueConstraint * LinearCurve::buildValueConstraint(int max_value, int nb_lines) const
{
    return new LinearConstraint(max_value, nb_lines);
}

DistributiveLaw * LinearCurve::buildDistributiveLaw() const
{
    return new  LinearDistribution();
}

double LinearCurve::getY(double x) const
{
    return x ;
}
