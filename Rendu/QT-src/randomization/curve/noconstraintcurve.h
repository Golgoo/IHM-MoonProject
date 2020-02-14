#ifndef NOCONSTRAINTCURVE_H
#define NOCONSTRAINTCURVE_H

#include "restrictioncurve.h"

class NoConstraintCurve: public RestrictionCurve
{
public:
    NoConstraintCurve();
public:
    ValueConstraint * buildValueConstraint(int max_value, int nb_lines) const override;
    double getY(double x) const override;
};

#endif // NOCONSTRAINTCURVE_H
