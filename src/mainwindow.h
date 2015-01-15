#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "actioncollection.h"
#include "standardactions.h"
#include "videowidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    ActionCollection* actionCollection();

private:
    void createMenuBar();

signals:

public slots:

private:
    ActionCollection* m_actionCollection;
    StandardActions* m_standardActions;
    VideoWidget* m_videoWidget;
};

#endif // MAINWINDOW_H