#ifndef LINEARDISTRIBUTION_H
#define LINEARDISTRIBUTION_H

#include "distributive_law.h"

class LinearDistribution: public DistributiveLaw
{
public:
    LinearDistribution();
    ~LinearDistribution();
    double generate() override;
    int getDistribUISection() const override;
private:
    std::piecewise_linear_distribution <double> *distribution;
    const static int ui_section = 2 ;
};

#endif // LINEARDISTRIBUTION_H
