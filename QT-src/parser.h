#ifndef PARSER_H
#define PARSER_H

#include "datatable.h"
#include <QString>

class Parser
{
protected:
    QString content;
public:
    Parser(QString& content);
    virtual DataTable parse() = 0;
};

#endif // PARSER_H
