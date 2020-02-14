#ifndef LINEARINVERTEDCURVE_H
#define LINEARINVERTEDCURVE_H

#include "restrictioncurve.h"
#include "distributioncurve.h"

class LinearInvertedCurve : public RestrictionCurve, public DistributionCurve
{
public:
    LinearInvertedCurve();
public:
    ValueConstraint * buildValueConstraint(int max_value, int nb_lines) const override;
    DistributiveLaw * buildDistributiveLaw() const override;
    double getY(double x) const override;
};

#endif // LINEARINVERTEDCURVE_H
