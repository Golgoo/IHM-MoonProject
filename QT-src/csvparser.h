#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "parser.h"

class CSVParser : public Parser
{
public:
    CSVParser(QString &content);
    DataTable parse();

};

#endif // CSVPARSER_H
