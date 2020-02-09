#ifndef EXPONENTIALCURVE_H
#define EXPONENTIALCURVE_H

#include "distributioncurve.h"

class ExponentialCurve: public DistributionCurve
{
public:
    ExponentialCurve();
public:
    DistributiveLaw * buildDistributiveLaw() const override;
    double getY(double x) const override;
};

#endif // EXPONENTIALCURVE_H
