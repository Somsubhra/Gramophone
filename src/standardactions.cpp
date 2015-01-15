#include "standardactions.h"

#include <QAction>
#include <QStyle>

#include "mainwindow.h"

StandardActions::StandardActions(MainWindow* mainWindow, QObject* parent) :
    QObject(parent)
{
    m_mainWindow = mainWindow;
}

void StandardActions::createStandardActions()
{
    // Exit action
    QAction* exitAction = new QAction(tr("Exit"), m_mainWindow);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), m_mainWindow, SLOT(close()));
    m_mainWindow->actionCollection()->addAction("exit", exitAction);

    // Open action
    QAction* openAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_DirOpenIcon),
                                      tr("Open"), m_mainWindow);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    m_mainWindow->actionCollection()->addAction("open", openAction);

    // Play action
    QAction* playAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaPlay),
                tr("Play"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("play", playAction);

    // Pause action
    QAction* pauseAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaPause),
                                       tr("Pause"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("pause", pauseAction);

    // Stop action
    QAction* stopAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaStop),
                                      tr("Stop"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("stop", stopAction);

    // Previous media action
    QAction* prevAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSkipBackward),
                                      tr("Previous"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("prev", prevAction);

    // Next media action
    QAction* nextAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSkipForward),
                                      tr("Next"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("next", nextAction);

    // Jump forward action
    QAction* jumpForwardAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSeekForward),
                                             tr("Jump Forward"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("jump_forward", jumpForwardAction);

    // Jump backward action
    QAction* jumpBackwardAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSeekBackward),
                                              tr("Jump Backward"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("jump_backward", jumpBackwardAction);

    // Jump to time action
    QAction* jumpToTimeAction = new QAction(tr("Jump to Time"), m_mainWindow);
    jumpToTimeAction->setShortcut(QKeySequence("Ctrl+T"));
    m_mainWindow->actionCollection()->addAction("jump_to_time", jumpToTimeAction);

    // Increase volume action
    QAction* incrVolumeAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaVolume),
                                            tr("Increase Volume"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("incr_volume", incrVolumeAction);

    // Decrease volume action
    QAction* decrVolumeAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaVolume),
                                            tr("Decrease Volume"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("decr_volume", decrVolumeAction);

    // Mute action
    QAction* muteAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaVolumeMuted),
                                      tr("Mute"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("mute", muteAction);

    // Full screen toggle action
    QAction* fullScreenAction = new QAction(tr("Full Screen"), m_mainWindow);
    fullScreenAction->setCheckable(true);
    fullScreenAction->setShortcut(tr("Ctrl+F"));
    m_mainWindow->actionCollection()->addAction("full_screen", fullScreenAction);

    // Playlist action
    QAction* playlistAction = new QAction(tr("Playlist"), m_mainWindow);
    playlistAction->setShortcut(QKeySequence("Ctrl+L"));
    m_mainWindow->actionCollection()->addAction("playlist", playlistAction);

    // Help action
    QAction* helpAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_DialogHelpButton),
                                      tr("Help"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("help", helpAction);

    // About action
    QAction* aboutAction = new QAction(tr("About"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("about", aboutAction);
}
