#include "uniformdistribution.h"


UniformDistribution::UniformDistribution():DistributiveLaw (), _distribution(0.0, 1.0)
{

}

double UniformDistribution::generate()
{
    return _distribution(*_generator);
}

UniformDistribution::~UniformDistribution()
{

}

int UniformDistribution::getUISection() const
{
    return ui_section;
}

