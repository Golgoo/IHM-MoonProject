#include "noconstraint.h"

NoConstraint::NoConstraint(int max_values): ValueConstraint (max_values)
{

}

int NoConstraint::getLimitAt(int line)
{
    (void)line ;
    return _max_value;
}
