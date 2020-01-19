#include "csvparser.h"
#include <QDebug>

CSVParser::CSVParser(QString& content):Parser(content)
{

}

DataTable CSVParser::parse() {

    DataTable table;
    std::vector<DataColumn> columns;
    /*std::string column_name = "blabla";
    DataColumn column(column_name);
    columns.push_back(column);*/
    bool new_string = true;
    std::string column_name;
    for (const auto &ch : this->content) {
        std::cout << "caractere lu : " << ch.toLatin1() << std::endl;
        if (ch == '\n') {
            DataColumn column(column_name);
            columns.push_back(column);
            std::cout << "nom colonne : " << column_name << std::endl;
            column_name.clear();
            break;
        }
        if (ch == ',') {
            DataColumn column(column_name);
            columns.push_back(column);
            std::cout << "nom colonne : " << column_name << std::endl;
            column_name.clear();
        } else {
            column_name.append(1, ch.toLatin1());
        }
    }

    std::cout << "size : " << columns.size() << std::endl;
    for (DataColumn &i : columns) {
        std::cout << "dans tableau : " << i.getName() << std::endl;
    }
}
