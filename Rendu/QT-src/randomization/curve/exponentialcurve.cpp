#include "exponentialcurve.h"

#include "../exponentialdistribution.h"

#include "curve.h"

ExponentialCurve::ExponentialCurve():  Curve("Exponentielle"), DistributionCurve("Exponentielle")
{

}

DistributiveLaw * ExponentialCurve::buildDistributiveLaw() const
{
    return new ExponentialDistribution();
}

//TODO c++ formule
double ExponentialCurve::getY(double x) const
{
    return (exp(x) - 1)/1.5 ;
}
