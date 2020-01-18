#include "datacolumn.h"

DataColumn::DataColumn(std::string& name, std::vector<std::string>& values)
{
    this->name = name;
    this->values = values;
    //algo pour chercher les valeurs distinctes ici ?

}

DataColumn::DataColumn(std::string& name)
{
    this->name = name;
    //algo pour chercher les valeurs distinctes ici ?

}

void DataColumn::setValues(std::vector<std::string>& values) {
    this->values = values;
}

void DataColumn::addValue(std::string& value) {
    this->values.push_back(value);
}
