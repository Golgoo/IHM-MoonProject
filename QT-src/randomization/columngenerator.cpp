#include "columngenerator.h"

#include <cmath>
#include <iostream>

ColumnGenerator::ColumnGenerator(DistributiveLaw *distributive_law, ValueConstraint *value_constraint):
    _distributive_law(distributive_law), _value_constraints(value_constraint)
{

}

ColumnGenerator::~ColumnGenerator(){
    if(_distributive_law != nullptr)
        delete _distributive_law;
    if(_value_constraints != nullptr)
        delete _value_constraints;
}

int ColumnGenerator::generate(int line)
{
    double random = _distributive_law->generate();
    int nb_values = _value_constraints->getLimitAt(line);
    return int(round(random * nb_values));
}

ValueConstraint& ColumnGenerator::getValueRestriction() const
{
    return *_value_constraints;
}
DistributiveLaw& ColumnGenerator::getDistributiveLaw() const
{
    return *_distributive_law;
}

void ColumnGenerator::setNewDistributiveLaw(DistributiveLaw* distributive_law)
{
    if(_distributive_law != nullptr) delete _distributive_law;
    _distributive_law = distributive_law;
}
void ColumnGenerator::setNewValueRestriction(ValueConstraint* value_constraint)
{
    if(_value_constraints != nullptr) delete _value_constraints;
    _value_constraints = value_constraint;
}
