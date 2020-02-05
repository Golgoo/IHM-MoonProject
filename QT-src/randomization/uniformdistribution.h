#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H

#include "distributive_law.h"

class UniformDistribution: public DistributiveLaw
{
public:
    UniformDistribution();
    ~UniformDistribution();
    double generate() override;
private:
    std::uniform_real_distribution<> _distribution;
};

#endif // UNIFORMDISTRIBUTION_H
