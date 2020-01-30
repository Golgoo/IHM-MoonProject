#include "integergenerator.h"

IntegerGenerator::IntegerGenerator(QString column_name,int borne_inf, int borne_sup): Generator(column_name), _borne_inf(borne_inf), _borne_sup(borne_sup)
{}

QString IntegerGenerator::generate()
{
    return QString::number( (qrand() % (_borne_sup - _borne_inf + 1 ) ) + _borne_inf);
}

int IntegerGenerator::getUiSection() const
{
    return _ui_section ;
}

void IntegerGenerator::updateFrom(generator_s generator_s)
{
    _borne_sup = generator_s.borne_sup;
    _borne_inf = generator_s.borne_inf;
}
generator_s IntegerGenerator::updateWidget() const
{
    generator_s gen_s ;
    gen_s.borne_inf = _borne_inf ;
    gen_s.borne_sup = _borne_sup ;
    return gen_s ;
}
