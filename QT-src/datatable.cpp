#include "datatable.h"

DataTable::DataTable() {

}

DataTable::DataTable(std::vector<DataColumn> columns)
{
    this->columns = columns;
}

void DataTable::addColumn(DataColumn& column) {
    this->columns.push_back(column);
}

std::vector<DataColumn> DataTable::getColumns() {
    return this->columns;
}
