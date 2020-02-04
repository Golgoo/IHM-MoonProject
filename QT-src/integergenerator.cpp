#include "integergenerator.h"

IntegerGenerator::IntegerGenerator(generator_s gen_s): Generator(gen_s)
{}

QString IntegerGenerator::generate()
{
    return QString::number( (qrand() % (_gen_s.borne_sup - _gen_s.borne_inf + 1 ) ) + _gen_s.borne_inf);
}

int IntegerGenerator::getUiSection() const
{
    return _ui_section ;
}

bool IntegerGenerator::valid() const
{
    return (_gen_s.borne_inf <= _gen_s.borne_sup);
}

QString IntegerGenerator::errorMessage() const
{
    return "La borne inférieure doit être plus petite que la borne supérieure";
}

