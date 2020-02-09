#ifndef DISTRIBUTIONCURVE_H
#define DISTRIBUTIONCURVE_H

#include "curve.h"
#include "../distributive_law.h"

class DistributionCurve: public Curve
{
public:
    DistributionCurve(QString name);
public:
    virtual DistributiveLaw* buildDistributiveLaw() const = 0;
};

#endif // DISTRIBUTIONCURVE_H
