#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "distributive_law.h"

class ExponentialDistribution : public DistributiveLaw
{
public:
    ExponentialDistribution();

    double generate() override;

private:
    std::exponential_distribution<double> _distribution;
};

#endif // EXPONENTIALDISTRIBUTION_H
