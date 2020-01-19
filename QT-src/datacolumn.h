#ifndef DATA_COLUMN_H
#define DATA_COLUMN_H

#include<iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class DataColumn
{

private:
    std::string name;
    int size;
    std::vector<std::string> values;
    std::unordered_set<std::string> distinct_values;
    //std::unordered_map pour associer chaque valeur distincte à sa pondération ?

public:
    DataColumn(std::string& name, std::vector<std::string>& values);
    DataColumn(std::string& name);
    void find_distinct_values();

    void setValues(std::vector<std::string>& values);
    void addValue(std::string& value);

    std::string getName();

};

#endif // DATA_COLUMN_H
