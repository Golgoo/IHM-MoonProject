#include "datamodel.h"

#include <QTextStream>
#include <QStringList>
#include <QDebug>


DataModel::DataModel(QString filename, QChar col_delimiter) : _col_delimiter(col_delimiter)
{
    f = new QFile(filename);
    if(! f->open(QIODevice::ReadOnly | QFile::Text)){
        emit error_loading_file("Cannot read file \" " + filename + " \"");
    }else{
        QTextStream ts (f);
        QString tmp = ts.readLine();
        /* On se permet de garder les headers dans la RAM */
        _headers = tmp.split(col_delimiter);

        line_index.push_back(ts.pos());

        /*On récup nb de colonnes de la ligne*/
        _col_count = tmp.split(this->_col_delimiter).size();
        while(! ts.atEnd()){
            QString readedLine = ts.readLine();
            if(readedLine.isEmpty()) continue;

            /*On récupère index de la ligne par rapport au Stream du fichier ouvert*/
            line_index.push_back(ts.pos());
            _row_count++;
        }

        for(int i = 0 ; i < _col_count ; i ++) _cols_shifter.push_back(i);

        qDebug() << " Valeurs distinctes de la 1ère colonne " << getDistinctValuesOfColumn(0);
    }
}

DataModel::~DataModel()
{
    f->close();
    delete f;
    f = nullptr;
}

/*A quoi sert cette fonction, return QVariant (union) quand conditions pas satisfaites ?*/
QVariant DataModel::data (const QModelIndex & index, int role) const
{
    /*Test si index ne pointe pas hors de la matrice, une valeur inexistante*/
    if(! this->isValid(index)){
        return QVariant();
    }
    if(role == Qt::TextAlignmentRole){
        return int(Qt::AlignLeft | Qt::AlignCenter);
    }else if( role == Qt::DisplayRole){
        return getValue(index.row(), index.column());
    }
    return QVariant();
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }
    if( orientation == Qt::Horizontal) {
        return _headers[_cols_shifter[section]];
    }
    return section + 1 ;
}

/*!
* . QStringList * items ;
* . #OPT if ((items = cache.get(row)) == NULL )
* . f->fseek(SEEK_CUR, index[row]);
* . s <- f->getline() #define _GNU_SOURCE
* . *items = s.split();
* . #OPT ELSE
* . #OPT updateCache(row, items); => This operation should free QStringList not even in cache
* . return items[col];
* */
QString DataModel::getValue(int row, int col) const
{
    QStringList items ;
    if(! f->seek(line_index.at(row))){
        emit error_loading_file("Error during read of the file");
        return QString("ERR");
    }else{
        QString str = f->readLine();
        items = str.split(_col_delimiter);
        return (items)[_cols_shifter[col]];
    }
}

bool DataModel::isValid(QModelIndex index) const
{
    int r = index.row() ;
    int c = index.column();
    return ( 0 <= r && r < _row_count ) && ( 0 <= c && c < _col_count) ;
}

void DataModel::shiftColumn(int colNumber, int shift){
    int dst = colNumber + shift ;
    if((colNumber >= 0 && colNumber < _col_count) && (dst >= 0 && dst < _col_count)){
        _cols_shifter.move(colNumber, dst);
        qDebug() << _cols_shifter ;
    }else{
        // Signal or Exception
    }
}


QHash<QString,int> DataModel::getDistinctValuesOfColumn(int indexOfColumn){
    QHash<QString,int> dsHash;
    QString tmp ;
    for(int i=0; i<rowCount(); i++){
        tmp = getValue(i, indexOfColumn);
        if(! dsHash.contains(tmp)){
            dsHash.insert(tmp, 1);
        }else{
            dsHash.find(tmp).value()++;
        }
    }
    return dsHash;
}

