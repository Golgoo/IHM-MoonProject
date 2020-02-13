#ifndef INVERTEDLINEARDISTRIBUTION_H
#define INVERTEDLINEARDISTRIBUTION_H

#include "distributive_law.h"

class InvertedLinearDistribution: public DistributiveLaw
{
public:
    InvertedLinearDistribution();
    ~InvertedLinearDistribution();
    double generate() override;
    int getDistribUISection() const override;
private:
    std::piecewise_linear_distribution <double> *distribution;
    const static int ui_section = 3 ;
};

#endif // INVERTEDLINEARDISTRIBUTION_H
