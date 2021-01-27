#include "common.h"

void common::cardStyle(QWidget* parent, QWidget* widget)
{
    parent->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect* ef  = new QGraphicsDropShadowEffect;
    ef->setColor(QColor(180,180,180));
    ef->setBlurRadius(20);
    ef->setOffset(1,3);
    widget->setGraphicsEffect(ef);
}