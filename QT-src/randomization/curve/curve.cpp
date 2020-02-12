#include "curve.h"

#include <QPainter>

#include <QDebug>

Curve::Curve(QString name): _name(name)
{
}

void Curve::loadPixMap()
{
    QSize m_size(150,150);
    _pix_map = new QPixmap(m_size);

    int curveScale = m_size.height();
    QPainter m_painter(_pix_map);
    m_painter.fillRect(QRect(QPoint(0, 0), m_size), QColor(255,255,255));
    QPoint m_start(0, m_size.height() - getY(0) * curveScale);
    m_painter.setBrush(Qt::blue);
    QPainterPath m_curvePath;
    m_curvePath.moveTo(m_start);
    for (qreal t = 0; t <= 1.0; t+=1.0/curveScale) {
        QPoint to;
        to.setX(t * curveScale);
        to.setY(m_size.height() - getY(t) * curveScale);
        m_curvePath.lineTo(to);
    }
    m_painter.setRenderHint(QPainter::Antialiasing, true);
    m_painter.strokePath(m_curvePath, QColor(30, 80, 240));
    m_painter.setRenderHint(QPainter::Antialiasing, false);
}

Curve::~Curve()
{
    delete _pix_map;
}
