#include "csvparser.h"
#include <QDebug>

CSVParser::CSVParser(QString& content):Parser(content)
{

}

DataTable CSVParser::parse() {

    DataTable table;
    std::vector<DataColumn> columns;
    std::string column_name;
    for (const auto &ch : this->content) {
        if (ch == '\n') {
            DataColumn column(column_name);
            columns.push_back(column);
            column_name.clear();
            break;
        }
        if (ch == ',') {
            DataColumn column(column_name);
            columns.push_back(column);
            column_name.clear();
        } else {
            column_name.append(1, ch.toLatin1());
        }
    }

    bool start = false;
    int column_index = 0;
    std::string column_value;
    for (const auto &ch : this->content) {
        if (!start && ch == '\n') {
            start = true;
            continue;
        }
        if (start) {
            if (ch == '\n') {
                columns.at(column_index).addValue(column_value);
                column_value.clear();
                column_index = 0;
            }
            else if (ch == ',') {
                columns.at(column_index).addValue(column_value);
                column_value.clear();
                ++column_index;
            }
            else {
                column_value.append(1, ch.toLatin1());
            }
        }
    }

    std::cout << "size : " << columns.size() << std::endl;
    for (DataColumn &c : columns) {
        std::cout << "dans tableau : " << c.getName() << std::endl;
        for (std::string &s : c.getValues()) {
            std::cout << " a pour valeur : " << s << std::endl;
        }
        table.addColumn(c);
    }
    return table;
}
