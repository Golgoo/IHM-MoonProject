#include "lineardistribution.h"

LinearDistribution::LinearDistribution()
{
    std::array<double, 2> intervals{0.0, 1.0};
    std::array<double, 2> weights{0.0, 1.0};

    distribution = new std::piecewise_linear_distribution<double>(intervals.begin(), intervals.end(), weights.begin());
}

LinearDistribution::~LinearDistribution()
{
    delete distribution;
}

double LinearDistribution::generate()
{
    return (*distribution)(*_generator);
}
int LinearDistribution::getDistribUISection() const
{
    return ui_section;
}
