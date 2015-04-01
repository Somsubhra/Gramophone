#ifndef ACTIONHANDLERS_H
#define ACTIONHANDLERS_H

#include <QObject>

class MainWindow;

class ActionHandlers : public QObject
{
    Q_OBJECT
public:
    explicit ActionHandlers(MainWindow* mainWindow, QObject *parent = 0);

signals:

public slots:
    void slotExit();
    void slotOpen();

    void slotPlay();
    void slotPause();
    void slotStop();

    void slotPrevMedia();
    void slotNextMedia();

    void slotJumpForward();
    void slotJumpBackward();
    void slotJumpToTime();

    void slotIncrVolume();
    void slotDecrVolume();
    void slotMute();

    void slotFullScreenToggle();

    void slotPlaylist();

    void slotHelp();
    void slotAbout();

private:
    MainWindow* m_mainWindow;
};

#endif // ACTIONHANDLERS_H
