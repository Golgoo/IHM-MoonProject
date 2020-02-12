#ifndef LINEARCURVE_H
#define LINEARCURVE_H

#include "restrictioncurve.h"

class LinearCurve: public RestrictionCurve
{
public:
    LinearCurve();
public:
    ValueConstraint * buildValueConstraint(int max_value, int nb_lines) const override;
    double getY(double x) const override;
};

#endif // LINEARCURVE_H
