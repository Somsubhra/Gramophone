#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) :
    QVideoWidget(parent)
{
    QPalette pa = this->palette();
    pa.setColor(QPalette::Window, Qt::black);
    this->setPalette(pa);

    this->setAttribute(Qt::WA_OpaquePaintEvent);
}
