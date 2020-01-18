#ifndef DATATABLE_H
#define DATATABLE_H

#include "datacolumn.h"

class DataTable
{
private:

    std::vector<DataColumn> columns;

public:
    DataTable();
};

#endif // DATATABLE_H
