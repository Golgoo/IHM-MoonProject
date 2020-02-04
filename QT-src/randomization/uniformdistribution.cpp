#include "uniformdistribution.h"


UniformDistribution::UniformDistribution(int upper_bound):DistributiveLaw ()
{
    _distribution = new std::uniform_int_distribution<int>(0,upper_bound);
}

int UniformDistribution::generate(int upper_bound)
{
    if(upper_bound != _distribution->param().b()){
        delete _distribution;
        _distribution = new std::uniform_int_distribution<int>(0,upper_bound);
    }
    return (*_distribution)(_generator);
}

UniformDistribution::~UniformDistribution()
{
    if(_distribution != nullptr)
        delete _distribution;
}
