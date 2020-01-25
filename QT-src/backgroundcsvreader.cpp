#include "backgroundcsvreader.h"

    /* TODO Lire la première line pour déduire les champs _row_count et _col_count */
    // Lire une ligne est spécifier dans le .h de la fonction startRead();
#include <QDebug>
#include <QThread>

BackgroundCSVReader::BackgroundCSVReader(QString filename, QChar colParser, int line_buff_size) :
    _lines_buff_size(line_buff_size), _col_parser(colParser)
{
    _file = new QFile(filename);

}

BackgroundCSVReader::~BackgroundCSVReader() {
    _file->close();
    delete _file;
}

void BackgroundCSVReader::process() {
    QString str ;
    QStringList lineItems ;
    vector<QStringList> buffer ;
    if(!_file->open(QIODevice::ReadOnly | QFile::Text)){
        emit error("Impossible d'ouvrir le fichier :\" " + _file->fileName() + " \"");
    }else{
        QTextStream in(_file);
        while(!in.atEnd()){
            str = in.readLine();
            qDebug() << str ;
            lineItems = str.split(_col_parser);
            buffer.push_back(lineItems);

            //A voir si le champs _lines n'est pas optionnel
            _lines.push_back(lineItems);

            if((_readed_row + 1) % _lines_buff_size == 0){
                emit new_lines(_readed_row - _lines_buff_size + 1, buffer);

                //QThread::sleep(1); //Pour simuler une lecture longue

                buffer.clear();
            }

            _readed_row ++ ;
        }

        if(! buffer.empty()) {
            emit new_lines((int)((unsigned long)_readed_row - buffer.size()), buffer);
            buffer.clear();
        }
        emit finished();
    }
}
