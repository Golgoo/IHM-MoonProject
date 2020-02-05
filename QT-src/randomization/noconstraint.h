#ifndef NOCONSTRAINT_H
#define NOCONSTRAINT_H

#include "valueconstraint.h"

class NoConstraint : public ValueConstraint
{
public:
    NoConstraint(int max_values, int max_lines);
    ~NoConstraint();
    int getLimitAt(int line) override ;
};

#endif // NOCONSTRAINT_H
