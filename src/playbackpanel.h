#ifndef PLAYBACKPANEL_H
#define PLAYBACKPANEL_H

#include <QWidget>
#include "playbackbuttons.h"

class MainWindow;

class PlaybackPanel : public QWidget
{
    Q_OBJECT
public:
    explicit PlaybackPanel(MainWindow* mainWindow, QWidget *parent = 0);

signals:

public slots:

private:
    MainWindow* m_mainWindow;
    PlaybackButtons* m_playbackButtons;
};

#endif // PLAYBACKPANEL_H
