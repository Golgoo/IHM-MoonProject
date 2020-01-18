#include "datacolumn.h"

DataColumn::DataColumn(std::string name, std::vector<std::string> values)
{
    this->name = name;
    this->values = values;
    //algo pour chercher les valeurs distinctes ici ?
}
