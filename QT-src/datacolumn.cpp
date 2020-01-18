#include "data_column.h"

DataColumn::data_column(std::string name, std::vector<std::string> values)
{
    this->name = name;
    this->values = values;
    //algo pour chercher les valeurs distinctes ici ?
}
