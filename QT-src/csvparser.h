#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "parser.h"
#include "datatable.h"

class CSVParser : public Parser
{
public:
    CSVParser(QString &content);
    /*DataTable parse() {
        DataTable table;
    }*/
    DataTable parse();

};

#endif // CSVPARSER_H
