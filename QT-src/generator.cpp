#include "generator.h"

#include "integergenerator.h"

Generator::Generator(generator_s gen_s):_gen_s(gen_s)
{
    qsrand(time(NULL));
}

Generator::~Generator()
{

}

generator_s Generator::getGeneratorInfo() const
{
    return _gen_s;
}

generator_s Generator:: build_default_gen_s()
{
    generator_s gen_s ;

    gen_s.borne_inf = 0 ;
    gen_s.borne_sup = 0 ;

    return gen_s;
}

Generator* Generator::build_default_generator()
{
    return new IntegerGenerator(build_default_gen_s());
}

void Generator::updateFrom(const generator_s generator_s)
{
    _gen_s = generator_s;
}
