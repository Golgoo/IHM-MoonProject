#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QFile>
#include <QModelIndex>
#include <QObject>
#include <QSet>
#include <iterator>

/*!
 * \brief The DataModel class
 *
 * TODO :
 * Permettre de réutiliser le même objet
 * =>update(QString fileName) => clear all + indexer.
 * =>gérer l'inversions des colonnes. => array<int> _col_shake =>_col_shake[1] = 3 <=> la colonne 1 du modèle correspond à la colonne 3 du fichier
 * =>Option SVG ( à voir si ça devrait être une autre classe ), prose de garder la configuration des colonnes
 *          -> proto : void svg(QString filename, boolean shake_cols = false, QChar col_delim = ',');
 *
 * => Cherche comment customiser les WidgetHeaders ( + boutons gauche/droite pour déplacer les colonnes )
 *          -> Cherche fct AbstractTableModel pour forcer un refresh ( si les colonnes changent et que ça ne met pas à jour).
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

    void setColorOfLine(int num_line, QColor newcolor);

    QHash<QString,int> getDistinctValuesOfColumn(int indexOfColumn) const;

    /*les 4 méthodes de l'interface QAbstractTableModel*/
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
    QColor *color;

};

#endif // DATAMODEL_H
