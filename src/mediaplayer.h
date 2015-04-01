#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>

class MainWindow;

class MediaPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    MediaPlayer(MainWindow* mainWindow);

    void playLocalFile(QUrl url);

public slots:
    void showErrorMessage();

private:
    MainWindow* m_mainWindow;
};

#endif // MEDIAPLAYER_H
