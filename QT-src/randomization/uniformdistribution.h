#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H

#include "distributive_law.h"

class UniformDistribution: public DistributiveLaw
{
public:
    UniformDistribution();
    ~UniformDistribution();
    double generate() override;
    int getDistribUISection() const override;
private:
    std::uniform_real_distribution<> _distribution;
    const static int ui_section = 0 ;
};

#endif // UNIFORMDISTRIBUTION_H
