#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <cstdio>

/*!
 * \brief The DataModel class
 *
 *
 *
 * Optimisation possible : rajouter son propre cache.
 *
 */
class DataModel : QAbstractTableModel
{
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
    DataModel(QString filename);

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
    QString getValue(int row, int col);

    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;



private:
    FILE *f = nullptr; /*< fichier */

};

#endif // DATAMODEL_H
