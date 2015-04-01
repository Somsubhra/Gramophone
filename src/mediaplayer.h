#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>

class MainWindow;

class MediaPlayer : public QMediaPlayer
{
public:
    MediaPlayer(MainWindow* mainWindow);

private:
    MainWindow* m_mainWindow;
};

#endif // MEDIAPLAYER_H
