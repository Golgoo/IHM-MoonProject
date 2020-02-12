#include "datamodel.h"

#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QColor>
#include <QIdentityProxyModel>
#include <QBrush>
#include <QMessageBox>
#include <QString>

#include "model/modelexception.h"
#include <fstream>
#include <sstream>


DataModel::DataModel(QString filename, char col_delimiter) : _col_delimiter(col_delimiter)
{
    Valid = true;
    qDebug() << "Starting to read model";
    f = new QFile(filename);
    if(! f->open(QIODevice::ReadOnly | QFile::Text)){
        emit error_loading_file("Cannot read file \" " + filename + " \"");
    }else{
        std::ifstream stream(filename.toStdString());
        std::string tmp ;
        std::getline(stream, tmp);
        std::stringstream ss(tmp);

        int nb_row = 0;
        /* On se permet de garder les headers dans la RAM */
        for (std::string item; std::getline(ss, item, _col_delimiter); ) {
            qDebug() << "bbbbbbbbb " << QString::fromStdString(item);
            _headers.push_back(QString(item.c_str()));
        }
        _col_count = _headers.size();
        line_index.push_back(stream.tellg());

        for (std::string line; std::getline(stream, line); ) {
            qint64 indexOfLine = stream.tellg();
            qDebug() << " uuuuuuuuuu" << QString::fromStdString(line);
            std::stringstream iss(line);
            int nb_elem_on_line =0;
            for (std::string item; std::getline(iss, item, _col_delimiter); ) {
                nb_elem_on_line++;
            }
            qDebug() << "woooooooooooooooooooooooooo";
            if(nb_elem_on_line!=_col_count){
                qDebug() << nb_elem_on_line << "yo " << _col_count;
                Valid = false;

            }

            line_index.push_back(indexOfLine);
            _row_count ++ ;
        }

        for(int i = 0 ; i < _col_count ; i ++) _cols_shifter.push_back(i);
        double origin = (255.0/_row_count);
        double step = 0.0 ;
        for(int l = 0 ; l < _row_count ; l ++) {
            color.push_back(QColor::fromHsl(step,255,175,180));
            step += origin ;
        }
    }
    qDebug() << "Finish to read model : " << _row_count << " ligne(s) - " << _col_count << " colonne(s)" ;
    qDebug() << "isConform ?" << isConform();
}

DataModel::~DataModel()
{
    f->close();
    delete f;
    f = nullptr;
}

bool DataModel::isConform() const{
    return Valid;
}

/*A quoi sert cette fonction, return QVariant (union) quand conditions pas satisfaites ?*/
//QVariant(void) <=> Invalide
QVariant DataModel::data (const QModelIndex & index, int role) const
{
    //qDebug() << "Need Data " << index.row() << " - " << index.column() ;
    /*Test si index ne pointe pas hors de la matrice, une valeur inexistante*/
    if(! this->isValid(index)){
        return QVariant();
    }
    if(role == Qt::TextAlignmentRole){
        return int(Qt::AlignLeft | Qt::AlignCenter);
    }else if( role == Qt::DisplayRole){
        return getValue(index.row(), index.column());
    }else if (role == Qt::BackgroundRole) {
        /*TODO:Change couleur tableur mais à associer avec les arêtes plus tard*/
        return color.at(index.row());
     }
    return QVariant();
}

void DataModel::setColorOfLine(int num_line, QColor newcolor){
    color.insert(num_line,newcolor);
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
    QString value ;
    if(! f->seek(line_index.at(row))){
        emit error_loading_file("Error during read of the file");
        return QString("ERR");
    }else{
        QString str = f->readLine();
        items = str.split(_col_delimiter);
        value = (items)[_cols_shifter[col]];
        value.remove('\n');
        return value;
    }
}

bool DataModel::isValid(QModelIndex index) const
{
    if(!isConform())
        return false;
    int r = index.row() ;
    int c = index.column();
    return ( 0 <= r && r < _row_count ) && ( 0 <= c && c < _col_count) ;
}

//---------------------------------------------------------
void DataModel::shiftColumn(int colNumber, int shift){
    int dst = colNumber + shift ;
    if((colNumber >= 0 && colNumber < _col_count) && (dst >= 0 && dst < _col_count)){
        _cols_shifter.move(colNumber, dst);
        //qDebug() << _cols_shifter ;
    }else{
        // Signal or Exception
    }
}

QHash<QString,int> DataModel::getDistinctValuesOfColumn(int indexOfColumn) const{
    QHash<QString,int> dsHash;
    QString tmp ;
    for(int i=0; i<rowCount(); i++){
        tmp = getValue(i, indexOfColumn);
        //tmp = tmp+"-"+indexOfColumn;
        QString numCol = QString("-%1").arg(indexOfColumn);
        tmp += numCol;

        qDebug() << "SOMMET : " << tmp;
        if(! dsHash.contains(tmp)){
            dsHash.insert(tmp, 1);
        }else{
            dsHash.find(tmp).value()++;
        }
    }
    return dsHash;
}

