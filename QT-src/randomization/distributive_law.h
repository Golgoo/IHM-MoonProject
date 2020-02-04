#ifndef DISTRIBUTIVE_LAW_H
#define DISTRIBUTIVE_LAW_H

#include <random>
#include <chrono>
#include <memory>

#include "plottable.h"

using namespace std;

typedef linear_congruential_engine<uint_fast32_t, 27653, 0, 2147483647> mint_generator;

class DistributiveLaw : public Plottable
{
public:
    DistributiveLaw();
    virtual ~DistributiveLaw();

    virtual int generate(int upper_bound) = 0;
protected:
    mint_generator* _generator = nullptr;
};

#endif // DISTRIBUTIVE_LAW_H
