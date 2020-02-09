#ifndef CURVE_H
#define CURVE_H


#include <QString>
#include <QPixmap>


class Curve
{
public:
    Curve(QString name);
    virtual ~Curve();
    void loadPixMap();
    inline const QPixmap& getPixMap() const {return *_pix_map ;};
    inline virtual const QString& getString() const {return _name;} ;

private:
    QString _name ;
    QPixmap *_pix_map;
protected:
    virtual double getY(const double x) const = 0;

};

#endif // CURVE_H
