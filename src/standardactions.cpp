#include "standardactions.h"

#include <QAction>

#include "mainwindow.h"

StandardActions::StandardActions(MainWindow* mainWindow, QObject* parent) :
    QObject(parent)
{
    m_mainWindow = mainWindow;
}

void StandardActions::createStandardActions()
{
    QAction* exitAction = new QAction(tr("Exit"), m_mainWindow);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), m_mainWindow, SLOT(close()));
    m_mainWindow->actionCollection()->addAction("exit", exitAction);

    QAction* openAction = new QAction(tr("Open"), m_mainWindow);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    m_mainWindow->actionCollection()->addAction("open", openAction);

    QAction* playAction = new QAction(tr("Play"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("play", playAction);

    QAction* pauseAction = new QAction(tr("Pause"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("pause", pauseAction);

    QAction* stopAction = new QAction(tr("Stop"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("stop", stopAction);

    QAction* prevAction = new QAction(tr("Previous"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("prev", prevAction);

    QAction* nextAction = new QAction(tr("Next"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("next", nextAction);

    QAction* jumpForwardAction = new QAction(tr("Jump Forward"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("jump_forward", jumpForwardAction);

    QAction* jumpBackwardAction = new QAction(tr("Jump Backward"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("jump_backward", jumpBackwardAction);

    QAction* jumpToTimeAction = new QAction(tr("Jump to Time"), m_mainWindow);
    jumpToTimeAction->setShortcut(QKeySequence("Ctrl+T"));
    m_mainWindow->actionCollection()->addAction("jump_to_time", jumpToTimeAction);

    QAction* incrVolumeAction = new QAction(tr("Increase Volume"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("incr_volume", incrVolumeAction);

    QAction* decrVolumeAction = new QAction(tr("Decrease Volume"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("decr_volume", decrVolumeAction);

    QAction* muteAction = new QAction(tr("Mute"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("mute", muteAction);

    QAction* fullScreenAction = new QAction(tr("Full Screen"), m_mainWindow);
    fullScreenAction->setCheckable(true);
    fullScreenAction->setShortcut(tr("Ctrl+F"));
    m_mainWindow->actionCollection()->addAction("full_screen", fullScreenAction);

    QAction* playlistAction = new QAction(tr("Playlist"), m_mainWindow);
    playlistAction->setShortcut(QKeySequence("Ctrl+L"));
    m_mainWindow->actionCollection()->addAction("playlist", playlistAction);
}
