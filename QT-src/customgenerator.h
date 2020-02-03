#ifndef CUSTOMGENERATOR_H
#define CUSTOMGENERATOR_H

#include "generator.h"

class CustomGenerator : public Generator
{
public:
    CustomGenerator(generator_s gen_s);

private:
    const static int ui_section = 1 ;

public:
    int getUiSection() const override;
    QString generate() override;
    bool valid() const override;
    QString errorMessage() const override;
};

#endif // CUSTOMGENERATOR_H
