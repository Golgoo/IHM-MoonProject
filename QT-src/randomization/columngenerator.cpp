#include "columngenerator.h"

#include <cmath>
#include <iostream>

ColumnGenerator::ColumnGenerator(DistributiveLaw &distributive_law, ValueConstraint &value_constraint):
    _distributive_law(distributive_law), _value_constraints(value_constraint)
{

}

int ColumnGenerator::generate(int line)
{
    double random = _distributive_law.generate();
    //std::cout << "Rand" << random ;
    int nb_values = _value_constraints.getLimitAt(line);
    return int(round(random * nb_values));
}
