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
        line_idex.push_back(ts.pos());
        QString tmp = ts.readLine();
        _col_count = tmp.split(this->_col_delimiter).size();
        while(! ts.atEnd()){
            if(ts.readLine().isEmpty()) continue;
            line_idex.push_back(ts.pos());
            _row_count++;
        }

        _row_count -- ;
    }
    qDebug() << line_idex ;
}

DataModel::~DataModel()
{
    f->close();
    delete f;
    f = nullptr;
}

QVariant DataModel::data (const QModelIndex & index, int role) const
{

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
        return QString("Headers") ;
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
    Q_UNUSED(row);
    QStringList items ;
    //index[row]
    if(! f->seek(line_idex.at(row))){
        emit error_loading_file("Error during read of the file");
        return QString("ERR");
    }else{
        QString str = f->readLine();
        items = str.split(_col_delimiter);
        return (items)[col];
    }
}

bool DataModel::isValid(QModelIndex index) const
{
    int r = index.row() ;
    int c = index.column();
    return ( 0 <= r && r < _row_count ) && ( 0 <= c && c < _col_count) ;
}

