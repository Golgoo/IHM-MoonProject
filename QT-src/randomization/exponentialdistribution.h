#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "distributive_law.h"

class ExponentialDistribution : public DistributiveLaw
{
public:
    ExponentialDistribution();

    int generate(int max_bound) override;

private:
    std::exponential_distribution<double> _distribution;
};

#endif // EXPONENTIALDISTRIBUTION_H
