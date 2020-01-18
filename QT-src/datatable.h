#ifndef DATATABLE_H
#define DATATABLE_H

#include "datacolumn.h"

class DataTable
{
private:

    std::vector<DataColumn> columns;

public:
    DataTable();
    DataTable(std::vector<DataColumn> columns);
    void addColumn(DataColumn& column);
};

#endif // DATATABLE_H
