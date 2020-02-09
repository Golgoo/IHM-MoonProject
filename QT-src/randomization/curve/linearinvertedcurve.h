#ifndef LINEARINVERTEDCURVE_H
#define LINEARINVERTEDCURVE_H

#include "restrictioncurve.h"

class LinearInvertedCurve : public RestrictionCurve
{
public:
    LinearInvertedCurve();
public:
    ValueConstraint * buildValueConstraint(int max_value, int nb_lines) const override;
    double getY(double x) const override;
};

#endif // LINEARINVERTEDCURVE_H
