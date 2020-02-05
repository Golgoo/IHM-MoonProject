#include "linearconstraint.h"

#include <cmath>

LinearConstraint::LinearConstraint(int max_values, int max_lines): ValueConstraint(max_values, max_lines),
    _max_l_d(max_lines), _max_v_d(max_values)
{

}


int LinearConstraint::getLimitAt(int line)
{
    return round((double(line) * _max_v_d)/_max_l_d);
}
