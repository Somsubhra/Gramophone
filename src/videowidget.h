#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

class MainWindow;

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(MainWindow* mainWindow, QWidget *parent = 0);

signals:

public slots:

private:
    MainWindow* m_mainWindow;
};

#endif // VIDEOWIDGET_H
