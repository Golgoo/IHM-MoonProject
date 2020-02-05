#include "exponentialdistribution.h"

ExponentialDistribution::ExponentialDistribution(): DistributiveLaw (),
    _distribution(std::exponential_distribution<double>(3.5))
{

}

double ExponentialDistribution::generate()
{
    double number ;
    do {
        number = _distribution(*_generator);
    }while(number > 1.0);

    return 1.0 - number ;
}
