#include "uniformcurve.h"

#include "../uniformdistribution.h"

UniformCurve::UniformCurve():Curve("Uniforme"), DistributionCurve("Uniforme")
{

}


DistributiveLaw * UniformCurve::buildDistributiveLaw() const
{
    return new UniformDistribution();
}

//TODO c++ formule
double UniformCurve::getY(double x) const
{
    Q_UNUSED(x);
    return 0.5;
}
