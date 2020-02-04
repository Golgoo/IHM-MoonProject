#include "exponentialdistribution.h"

ExponentialDistribution::ExponentialDistribution(): DistributiveLaw (),
    _distribution(std::exponential_distribution<double>(3.5))
{

}

int ExponentialDistribution::generate(int max_bound)
{
    double number ;
    do {
        number = _distribution(_generator);
    }while(number > 1.0);

    return int(number*max_bound);
}
