#include "distributive_law.h"

using namespace std;

DistributiveLaw::DistributiveLaw()
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    _generator = new mint_generator(seed);
}

DistributiveLaw::~DistributiveLaw()
{
    delete _generator;
}
