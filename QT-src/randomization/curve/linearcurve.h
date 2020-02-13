#ifndef LINEARCURVE_H
#define LINEARCURVE_H

#include "restrictioncurve.h"
#include "distributioncurve.h"

class LinearCurve: public RestrictionCurve, public DistributionCurve
{
public:
    LinearCurve();
public:
    ValueConstraint * buildValueConstraint(int max_value, int nb_lines) const override;
    DistributiveLaw * buildDistributiveLaw() const override;
    double getY(double x) const override;
};

#endif // LINEARCURVE_H
