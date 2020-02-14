#include "invertedlineardistribution.h"


InvertedLinearDistribution::InvertedLinearDistribution()
{
    std::array<double, 2> intervals{0.0, 1.0};
    std::array<double, 2> weights{1.0, 0.0};

    distribution = new std::piecewise_linear_distribution<double>(intervals.begin(), intervals.end(), weights.begin());
}

InvertedLinearDistribution::~InvertedLinearDistribution()
{
    delete distribution;
}

double InvertedLinearDistribution::generate()
{
    return (*distribution)(*_generator);
}
int InvertedLinearDistribution::getDistribUISection() const
{
    return ui_section;
}
