#include "mediaplayer.h"

#include <QMessageBox>

#include "mainwindow.h"

MediaPlayer::MediaPlayer(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;

    setVideoOutput(m_mainWindow->videoWidget());
    connect(this, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(showErrorMessage()));
}

void MediaPlayer::playLocalFile(QUrl url)
{
    setMedia(url);
    setVolume(90);
    play();
}

void MediaPlayer::showErrorMessage()
{
    QMessageBox errorBox;
    errorBox.critical(m_mainWindow, "Gramophone Error", errorString());
    errorBox.setFixedSize(500, 200);
}
