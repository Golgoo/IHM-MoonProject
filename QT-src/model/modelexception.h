#ifndef MODELEXCEPTION_H
#define MODELEXCEPTION_H
#include <QException>

class ModelExeption : public QException
{
public:
    void raise() const override { throw *this; }
    ModelExeption *clone() const override { return new ModelExeption(*this); }
};
#endif // MODELEXCEPTION_H
