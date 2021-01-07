#include "painterwidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

PainterWidget::PainterWidget(QWidget *parent)
    : QLabel(parent)
    , m_painter(new QPainter())
    , m_pixmap(new QPixmap(300,270))
{
    qDebug() << this->size();
    this->hide();
}

void PainterWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Pressed:" << event->x() <<  event->y();
    m_path = QPainterPath(QPoint(event->x(), event->y()));
}

void PainterWidget::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << "Moving:" << event->x() <<  event->y();
    m_path.lineTo(event->x(), event->y());
}

void PainterWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Released:" << event->x() <<  event->y();
    m_path.lineTo(event->x(), event->y());

    m_pixmap->fill(Qt::white);

    m_painter->begin(m_pixmap);
    m_painter->setRenderHints(QPainter::Antialiasing, true);
    m_painter->setPen(Qt::SolidLine);
    m_painter->drawPath(m_path);
    m_painter->end();

    this->setPixmap(*m_pixmap);
}
