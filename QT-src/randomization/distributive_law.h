#ifndef DISTRIBUTIVE_LAW_H
#define DISTRIBUTIVE_LAW_H

#include <random>
#include <chrono>
#include <memory>


typedef std::linear_congruential_engine<uint_fast32_t, 27653, 0, 2147483647> mint_generator;

class DistributiveLaw
{
public:
    DistributiveLaw();
    virtual ~DistributiveLaw();

    /**
     * @brief generate
     * @return a double between 0.0 and 1.0
     */
    virtual double generate() = 0;
protected:
    mint_generator* _generator = nullptr;
};

#endif // DISTRIBUTIVE_LAW_H
