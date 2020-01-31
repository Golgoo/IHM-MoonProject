#ifndef INTEGERGENERATOR_H
#define INTEGERGENERATOR_H

#include "generator.h"
#include <QString>

class IntegerGenerator : public Generator
{
public:
    IntegerGenerator(generator_s gen_s);
private :
    const static int _ui_section = 0 ;
public :
    QString generate() override;
    int getUiSection() const override;
    bool valid() const override;
    QString errorMessage() const override;
};

#endif // INTEGERGENERATOR_H
