#include "noconstraint.h"

NoConstraint::NoConstraint(int max_values, int max_lines): ValueConstraint (max_values, max_lines)
{

}

int NoConstraint::getLimitAt(int line)
{
    (void)line ;
    return _max_value;
}

NoConstraint::~NoConstraint() {}

int NoConstraint::getValueUISection() const
{
    return _ui_section;
}
