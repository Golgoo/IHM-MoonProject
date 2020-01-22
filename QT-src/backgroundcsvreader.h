#ifndef BACKGROUNDCSVREADER_H
#define BACKGROUNDCSVREADER_H

#include <QTextStream>
#include <QString>
#include <vector>
#include <algorithm>
#include <QFile>

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
