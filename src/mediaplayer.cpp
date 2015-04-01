#include "mediaplayer.h"

#include "mainwindow.h"

MediaPlayer::MediaPlayer(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;

    this->setVideoOutput(m_mainWindow->videoWidget());
}
