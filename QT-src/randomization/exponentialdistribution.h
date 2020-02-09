#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "distributive_law.h"

class ExponentialDistribution : public DistributiveLaw
{
public:
    ExponentialDistribution();

    double generate() override;
    int getUISection() const override;

private :
    const static int ui_section = 1;

private:
    std::exponential_distribution<double> _distribution;
};

#endif // EXPONENTIALDISTRIBUTION_H
