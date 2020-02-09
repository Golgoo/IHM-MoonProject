#include "invertedlinearconstraint.h"

#include <cmath>

InvertedLinearConstraint::InvertedLinearConstraint(int max_values, int max_lines): ValueConstraint(max_values, max_lines),
    _max_l_d(max_lines), _max_v_d(max_values)
{

}

int InvertedLinearConstraint::getLimitAt(int line)
{
    return _max_v_d - round((double(line) * _max_v_d)/_max_l_d);
}

int InvertedLinearConstraint::getUISection() const
{
    return _ui_section;
}
