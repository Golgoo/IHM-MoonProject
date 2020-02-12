#ifndef UNIFORMCURVE_H
#define UNIFORMCURVE_H

#include "distributioncurve.h"

class UniformCurve: public DistributionCurve
{
public:
    UniformCurve();
public:
    DistributiveLaw * buildDistributiveLaw() const override;
    double getY(double x) const override;
};

#endif // UNIFORMCURVE_H
