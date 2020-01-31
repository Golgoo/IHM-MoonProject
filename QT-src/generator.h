#ifndef GENERATOR_H
#define GENERATOR_H

#include <QString>
#include <QTabWidget>

struct generator_s
{
    // Add any field for any generation // basicly act like an union

    /**Integer generator model**/
    int borne_inf ;
    int borne_sup ;

    /**Custom generator model **/
    QStringList items ;
};

class Generator
{
public:
    Generator(generator_s gen_s);
    virtual ~Generator();

protected:
    generator_s _gen_s ;

public :
    virtual int getUiSection() const = 0;
    virtual QString generate() = 0;
    virtual bool valid() const = 0;
    virtual QString errorMessage() const = 0 ;
    generator_s getGeneratorInfo() const ;
    void updateFrom(const generator_s generator_s) ;

public:
    static generator_s build_default_gen_s();
};

#endif // GENERATOR_H
