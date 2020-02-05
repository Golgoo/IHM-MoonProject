#include "generation_dialog.h"

#include <QEasingCurve>
#include <QListWidgetItem>
#include <QPainter>
generation_dialog::generation_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generation_dialog)
{
    ui->setupUi(this);

    QSize m_iconSize(64,64);
    QPixmap pix(m_iconSize);
    QPainter painter(&pix);
    QLinearGradient gradient(0,0, 0, m_iconSize.height());
    gradient.setColorAt(0.0, QColor(240, 240, 240));
    gradient.setColorAt(1.0, QColor(224, 224, 224));
    QBrush brush(gradient);
    painter.fillRect(QRect(QPoint(0, 0), m_iconSize), brush);
    QEasingCurve curve((QEasingCurve::Type) 2);

    painter.setPen(QColor(0, 0, 255, 64));
    qreal xAxis = m_iconSize.height()/1.5;
    qreal yAxis = m_iconSize.width()/3;

    qreal curveScale = m_iconSize.height()/2;

    painter.setPen(Qt::NoPen);

    // start point
    QPoint start(yAxis, xAxis - curveScale * curve.valueForProgress(0));
    painter.setBrush(Qt::blue);


    QPainterPath curvePath;
    curvePath.moveTo(start);
    for (qreal t = 0; t <= 1.0; t+=1.0/curveScale) {
        QPoint to;
        to.setX(yAxis + curveScale * t);
        to.setY(xAxis - curveScale * curve.valueForProgress(t));
        curvePath.lineTo(to);
    }
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.strokePath(curvePath, QColor(32, 32, 32));
    painter.setRenderHint(QPainter::Antialiasing, false);
    QListWidgetItem *item = new QListWidgetItem;
    item->setIcon(QIcon(pix));
   // ui->listWidget->addItem(item);

    //Init
    QSize m_size(150,150);
    QPixmap m_pix(m_size);
    QPainter m_painter(&m_pix);

    m_painter.fillRect(QRect(QPoint(0, 0), m_size), QColor(255,255,255));

    curveScale = m_size.height();
    //Courbe
    double uniform = 0.5;
    QPoint m_start(0, m_size.height() - uniform * curveScale);
    m_painter.setBrush(Qt::blue);

    QPainterPath m_curvePath;
    m_curvePath.moveTo(m_start);
    for (qreal t = 0; t <= 1.0; t+=1.0/curveScale) {
        QPoint to;
        to.setX(t * curveScale);
        to.setY(m_size.height() - uniform * curveScale);
        m_curvePath.lineTo(to);
    }
    m_painter.setRenderHint(QPainter::Antialiasing, true);
    m_painter.strokePath(m_curvePath, QColor(30, 80, 240));
    m_painter.setRenderHint(QPainter::Antialiasing, false);

    //Affichage
    ui->restriction_graph_label->setPixmap(m_pix);
    ui->distributive_graph_label->setPixmap(m_pix);
}
