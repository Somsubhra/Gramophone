#ifndef PLAYBACKBUTTONS_H
#define PLAYBACKBUTTONS_H

#include <QToolBar>

class MainWindow;

class PlaybackButtons : public QToolBar
{
    Q_OBJECT
public:
    explicit PlaybackButtons(MainWindow* mainWindow, QWidget *parent = 0);

private:
    void setupActions();

signals:

public slots:

private:
    MainWindow* m_mainWindow;
};

#endif // PLAYBACKBUTTONS_H
