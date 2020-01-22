#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QFile>
#include <QModelIndex>
#include <QObject>

/*!
 * \brief The DataModel class
 *
 *
 *
 * Optimisation possible : rajouter son propre cache.
 *
 */
class DataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /*!
     * \brief DataModel
     * \param filename nom du fichier
     *
     * Ouvre le fichier
     * Compte le nombre de lignes et de colonnes
     * Indèxe le numéro du caractère des débuts de ligne QVector<long>
     *
     */
    DataModel(QString filename, QChar col_delimiter = ',');
    ~DataModel();

public:
    /*!
     * \brief getValue
     * \param row .
     * \param col .
     * \return la valeur à row et col
     *
     * . QStringList * items ;
     * . #OPT if ((items = cache.get(row)) == NULL )
     * . f->fseek(SEEK_CUR, index[row]);
     * . s <- f->getline() #define _GNU_SOURCE
     * . *items = s.split();
     * . #OPT ELSE
     * . #OPT updateCache(row, items); => This operation should free QStringList not even in cache
     * . return items[col];
     *
     */
    QString getValue(int row, int col) const;

    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    inline int rowCount(const QModelIndex &parent = QModelIndex()) const { Q_UNUSED(parent) ;  return _row_count ;}
    inline int columnCount(const QModelIndex &parent = QModelIndex()) const { Q_UNUSED(parent) ; return _col_count;}

signals:
    void error_loading_file(QString error_details) const;


private:
    QFile *f ;
    int _row_count = 0 ;
    int _col_count = 0 ;
    QChar _col_delimiter ;
    QVector<qint64> line_idex ;
    bool isValid(QModelIndex index) const;

};

#endif // DATAMODEL_H
