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
    DataModel(QString filename, char col_delimiter = ',');
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
    /**
     * @brief setColorOfLine définit la couleur d'une ligne du modèle utilisé par la TableView
     * @param num_line : num de la ligne dont on veut modif la couleur
     * @param newcolor : la nouvelle couleur
     */
    void setColorOfLine(int num_line, QColor newcolor);
    /**
     * @brief getDistinctValuesOfColumn calcule les valeurs distinctes d'une colonne
     * @param indexOfColumn : la colonne dont on veut calculer les valeurs distinctes
     * @return un hash composé (des vals distinctes + leur nombre d'occurrences dans la colonne)
     */
    QHash<QString,int> getDistinctValuesOfColumn(int indexOfColumn) const;

    /*les 4 méthodes de l'interface QAbstractTableModel*/
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    inline int rowCount(const QModelIndex &parent = QModelIndex()) const { Q_UNUSED(parent) ;  return _row_count ;}
    inline int columnCount(const QModelIndex &parent = QModelIndex()) const { Q_UNUSED(parent) ; return _col_count;}

    /**
     * @brief isConform atteste de la conformité du modèle (dépend de la conformité du fichier
     * @return true si conforme false sinon
     */
    bool isConform() const;

    void export_csv(const QString filename);

signals:
    /**
     * @brief error_loading_file est un signal permettant d'envoyer un message d'erreur concernant l'ouverture d'un fichier csv
     * @param error_details
     */
    void error_loading_file(QString error_details) const;
    /**
     * @brief error_csv_not_valid est un signal permettant d'envoyer un message d'erreur concernant la conformité du fichier ouvert
     * @param error_details
     */
    void error_csv_not_valid(QString error_details) const;


private:
    QFile *f ; /*pointeur vers le fichier csv ouvert qui sert de modèle*/
    int _row_count = 0 ;
    int _col_count = 0 ;
    char _col_delimiter; /*le délimiteur de colonne des fichiers CSV "," */
    QVector<qint64> line_index ; /*index des lignes dans "f"(QFile)*/
    QVector<QColor> color; /*Vecteur contenant les couleurs des lignes du modèle*/
    QStringList _headers ; /*Liste avec les valeurs du header du modèle (de la TableView)*/
    QVector<int> _cols_shifter ;
    bool _valid = true; /*booléen indiquant si modèle correctement construit*/

    /**
     * @brief isValid vérifie la validité de "index" (si celui-ci pointe bien un index qui ne soit pas hors du modèle)
     * @param index
     * @return true si valide false sinon
     */
    bool isValid(QModelIndex index) const;
};

#endif // DATAMODEL_H
