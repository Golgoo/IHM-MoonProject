#ifndef COLUMNGENERATOR_H
#define COLUMNGENERATOR_H


#include "distributive_law.h"
#include "valueconstraint.h"

class ColumnGenerator
{
public:
    ColumnGenerator(DistributiveLaw *distributive_law, ValueConstraint *value_constraint);
    ~ColumnGenerator();
private:
    DistributiveLaw* _distributive_law ;
    ValueConstraint* _value_constraints ;
public:
    int generate(int line);
    ValueConstraint* getValueRestriction() const;
    DistributiveLaw* getDistributiveLaw() const;
    void setNewDistributiveLaw(DistributiveLaw* distributive_law);
    void setNewValueRestriction(ValueConstraint* value_constraint);
};

#endif // COLUMNGENERATOR_H
