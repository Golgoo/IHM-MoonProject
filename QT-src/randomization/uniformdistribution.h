#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H

#include "distributive_law.h"

class UniformDistribution: public DistributiveLaw
{
public:
    UniformDistribution(int upper_bound = 0);
    ~UniformDistribution() override;
    int generate(int upper_bound) override;
private:
    std::uniform_int_distribution<int>* _distribution;
};

#endif // UNIFORMDISTRIBUTION_H
