#ifndef RESTRICTIONCURVE_H
#define RESTRICTIONCURVE_H

#include "curve.h"
#include "../valueconstraint.h"

class RestrictionCurve : public Curve
{
public:
    RestrictionCurve(QString name);

public:
    virtual ValueConstraint* buildValueConstraint(int max_value, int nb_lines) const = 0 ;
};

#endif // RESTRICTIONCURVE_H
