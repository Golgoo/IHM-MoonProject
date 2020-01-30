#ifndef INTEGERGENERATOR_H
#define INTEGERGENERATOR_H

#include "generator.h"
#include <QString>

class IntegerGenerator : public Generator
{
public:
    IntegerGenerator(QString column_name, int borne_inf, int borne_sup);
private :
    int _borne_inf ;
    int _borne_sup ;
    const static int _ui_section = 2 ;
public :
    inline void set_borne_inf(int borne_inf){ _borne_inf = borne_inf ;}
    inline void set_borne_sup(int borne_sup){ _borne_sup = borne_sup ;}
    QString generate() override;
    int getUiSection() const override;
    void updateFrom(const generator_s generator_s) override;
    generator_s updateWidget() const override;
};

#endif // INTEGERGENERATOR_H
