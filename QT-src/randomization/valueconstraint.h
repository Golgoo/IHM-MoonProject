#ifndef VALUECONSTRAINT_H
#define VALUECONSTRAINT_H

class ValueConstraint
{
public:
    ValueConstraint(int max_values, int max_lines);
    virtual ~ValueConstraint();

    virtual int getLimitAt(int line) = 0;

protected:
    int _max_value ;
    int _max_lines ;
};

#endif // VALUECONSTRAINT_H
