#ifndef GENERATOR_H
#define GENERATOR_H

#include <QString>
#include <QTabWidget>

struct generator_s
{
    int borne_inf ;
    int borne_sup ;
    // Add every item for any generation // basicly act like an union
};

class Generator
{
public:
    Generator(QString column_name);
    virtual ~Generator();

private :
    QString _column_name ;

public :
    virtual int getUiSection() const = 0;
    virtual QString generate() = 0;
    virtual void updateFrom(const generator_s generator_s) = 0 ;
    virtual generator_s updateWidget() const = 0 ;
    inline QString name(){return _column_name ;}
};

#endif // GENERATOR_H
