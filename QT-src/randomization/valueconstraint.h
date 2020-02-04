#ifndef VALUECONSTRAINT_H
#define VALUECONSTRAINT_H

#include "plottable.h"

class ValueConstraint : public Plottable
{
public:
    ValueConstraint(int max_values);
    virtual ~ValueConstraint();

    virtual int getLimitAt(int line) = 0;

protected:
    int _max_value ;
};

#endif // VALUECONSTRAINT_H
