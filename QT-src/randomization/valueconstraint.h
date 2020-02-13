#ifndef VALUECONSTRAINT_H
#define VALUECONSTRAINT_H


class ValueConstraint
{
public:
    ValueConstraint(int max_values, int max_lines);
    virtual ~ValueConstraint();

    virtual int getLimitAt(int line) = 0;

    virtual int getValueUISection() const = 0;

protected:
    int _max_value ;
    int _max_lines ;

public:
    inline void setMaxValues(int max_values){_max_value = max_values; };
    inline void setNbLines(int nb_lines){_max_lines = nb_lines;} ;
    inline int getMaxValues() const {return _max_value; } ;
};

#endif // VALUECONSTRAINT_H
