#ifndef INVERTEDLINEARCONSTRAINT_H
#define INVERTEDLINEARCONSTRAINT_H

#include "valueconstraint.h"

class InvertedLinearConstraint: public ValueConstraint
{
public:
    InvertedLinearConstraint(int max_values, int max_lines);

    int getLimitAt(int line) override;
    int getUISection() const override;
private:
    double _max_l_d ;
    double _max_v_d ;
    const static int _ui_section = 2;
};

#endif // INVERTEDLINEARCONSTRAINT_H
