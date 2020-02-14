#ifndef LINEARCONSTRAINT_H
#define LINEARCONSTRAINT_H

#include "valueconstraint.h"

class LinearConstraint : public ValueConstraint
{
public:
    LinearConstraint(int max_values, int max_lines);

    int getLimitAt(int line) override;
    int getValueUISection() const override;
private:
    double _max_l_d ;
    double _max_v_d ;
    const static int _ui_section = 1;
};

#endif // LINEARCONSTRAINT_H
