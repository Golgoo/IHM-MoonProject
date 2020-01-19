#include "backgroundcsvreader.h"

BackgroundCSVReader::BackgroundCSVReader(QTextStream &in, QString colParser , QString rowParser , QString defaultValue ) :
    _textStream(in), _default_value(defaultValue), _row_parser(rowParser), _col_parser(colParser)
{
    /* TODO Lire la première line pour déduire les champs _row_count et _col_count */
    // Lire une ligne est spécifier dans le .h de la fonction startRead();
}
