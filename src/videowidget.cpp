#include "videowidget.h"

#include "mainwindow.h"

VideoWidget::VideoWidget(MainWindow *mainWindow, QWidget *parent) :
    QVideoWidget(parent)
{
    m_mainWindow = mainWindow;

    QPalette pa = this->palette();
    pa.setColor(QPalette::Window, Qt::black);
    this->setPalette(pa);

    this->setAttribute(Qt::WA_OpaquePaintEvent);
}
