#ifndef BACKGROUNDCSVREADER_H
#define BACKGROUNDCSVREADER_H


#include <QTextStream>
#include <QString>
#include <vector>
#include <algorithm>

/*!
 * \brief The BackgroundCSVReader Classe qui lit un CSV en arrière plan
 * \version 0.0
 *
 * Cette classe permet de lire un CSV en arrière plan et de retourner des informations sur la lecture en cours
 * Chaque ligne est représentée par un vector<QString>
 * L'ensemble des lignes est représenté par un vector<vector<QString>>
#include <QObject>
#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>

#pragma once

using namespace std;

/*!
 * \brief The BackgroundCSVReader lit un CSV en arrière plan
 * \version 0.0
 *
 * Cette classe lit un CSV en arrière plan et propose trois signaux :
 * Pour communiquer les erreurs / prévenir qu'un bloc de ligne a été lue, prévenir que la lecture est terminée
 *
 * Chaque ligne est représentée par un vector<QString>
 * L'ensemble des lignes est représenté par un vector<QListString>
 *
 * Ceci dans le but d'avoir un feedback recommandé pour l'IHM
 *
 */

using namespace std;

class BackgroundCSVReader
{
public:
    /**
     * \brief BackgroundCSVReader constructeur
     * \param in stream d'entrée
     * \param colParser chaine pour délimiter les champs du CSV entre deux colonnes
     * \param rowParser chaine pour délimiter les champs du CSV entre deux lignes
     * \param defaultValue valeur par défault utilisé pour les cases vides
     *
     * Le constructeur initialisera les paramètres _row_count et _col_count
     */
    BackgroundCSVReader(QTextStream &in, QString colParser = ",", QString rowParser = "\n", QString defaultValue = "");
    int getReadedRowCount();
    inline int getColCount() { return _col_count ;};
    inline int getRowCount(){ return _row_count ;};
private:
    int _row_count = 0;
    int _readed_row = 0 ;
    int _col_count = 0;
    QTextStream &_textStream ;
    QString _default_value ;
    QString _row_parser ;
    QString _col_parser ;
    vector<vector<QString>> _lines ;

    // Retourne un vecteur de taille _col_count rempli avec _default_value
    inline vector<QString> createEmptyLine() { vector<QString> v(_col_count, _default_value) ; return v ; } ;

public :
    /*!
     * \brief getProgressRatio
     * \return le ratio entre le nombre de ligne lue et le nombre de ligne total
     */
    inline float getProgressRatio(){ return (float)_readed_row / (float)_row_count ;}
    /*!
     * \brief startRead
     * Lance un thread qui :
     *  Pour chaque ligne :
     *    Lit une ligne en fonction de _row_parser
     *    Créer un vecteur vide v <- createEmptyLine()
     *    Parse la ligne en fonction de _col_parser
     *    Pour chaque item parse :
     *      v.push_back(item)
     *    Rajoute la ligne dans _lines : _lines.push_back(v);
     *    _readed_row <- _readed_row + 1
     *  Envoie un signal au slot(s) ( qui sera / seront ) passé(s) en arguments pour notifier la fin de la lecture.
     */
    void startRead();

    /*!
     * \brief getLines acesseur
     * \return la matrice
     *
     * Aux niveaux de la concurence : normalement l'utilisateur n'aura pas accès à la dernière ligne en cours de calcul et ne pourrat donc pas la modifier
     * Le comportement à adopter si un utilisateur souhaite créer une ligne alors que la lecture n'est pas terminée devra être défini :
     *          On pourrait créer la ligne à _row_count + 1 ( enfin _row_count + 0 ) pour ne pas géner la concurrence.
     */
    inline vector<vector<QString>> getLines() { return _lines ;}
};

#endif // BACKGROUNDCSVREADER_H

class BackgroundCSVReader : public QObject {
    Q_OBJECT
public:
    /**
     * \brief BackgroundCSVReader constructeur
     * \param filename nom du fichier à lire
     * \param colParser char pour délimiter les champs du CSV entre deux colonnes
     * \param line_buf_size nombre de lignes nécessaires pour emmetre le signal : "new_lines"
     *
     */
    BackgroundCSVReader(QString filename, QChar colParser = ',', int line_buf_size = 5);
    ~BackgroundCSVReader();
public slots:
    /*!
     * \brief process lance la lecture
     */
    void process();
signals:
    /*!
     * \brief finished signale quela lecture est terminée
     */
    void finished();
    /*!
     * \brief error signale qu'une erreur s'est produite lors de la lecture
     * \param err chaine expliquant l'erreur
     */
    void error(QString err);
    /*!
     * \brief new_lines indique qu'un nouveau bloc de lignes a été lu.
     * \param line_index numéro de la première ligne
     * \param lines lignes lues
     */
    void new_lines(int line_index, vector<QStringList> lines);
private:
    int _readed_row = 0 ;
    int _col_count = 0 ;
    int _lines_buff_size ;
    QFile *_file ;
    QChar _col_parser ;
    vector<QStringList> _lines ;
public:
    /*!
     * \brief getLines
     * \return retourne toutes les lignes lues jusqu'à présent.
     */
    inline vector<QStringList> getLines(){return _lines ;}
};

#endif
