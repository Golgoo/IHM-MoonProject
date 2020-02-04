#include "customgenerator.h"

CustomGenerator::CustomGenerator(generator_s gen_s):Generator(gen_s)
{}

int CustomGenerator::getUiSection() const
{
return ui_section ;
}

QString CustomGenerator::generate()
{
    int rand_index = (qrand() % _gen_s.items.size());
    return _gen_s.items[rand_index];
}

bool CustomGenerator::valid() const
{
    return (! _gen_s.items.empty());
}

QString CustomGenerator::errorMessage() const
{
    return "Il doit au moins y a voir un item pour la génération automatique";
}
