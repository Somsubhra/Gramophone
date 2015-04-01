#include "standardactions.h"

#include <QAction>
#include <QStyle>

#include "mainwindow.h"

StandardActions::StandardActions(MainWindow* mainWindow, QObject* parent) :
    QObject(parent)
{
    m_mainWindow = mainWindow;
    m_actionHandlers = new ActionHandlers(mainWindow, this);
}

void StandardActions::createStandardActions()
{
    // Exit action
    QAction* exitAction = new QAction(tr("Exit"), m_mainWindow);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    m_mainWindow->actionCollection()->addAction("exit", exitAction);
    connect(exitAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotExit()));

    // Open action
    QAction* openAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_DirOpenIcon),
                                      tr("Open"), m_mainWindow);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    m_mainWindow->actionCollection()->addAction("open", openAction);
    connect(openAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotOpen()));

    // Play action
    QAction* playAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaPlay),
                tr("Play"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("play", playAction);
    connect(playAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotPlay()));

    // Pause action
    QAction* pauseAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaPause),
                                       tr("Pause"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("pause", pauseAction);
    connect(pauseAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotPause()));

    // Stop action
    QAction* stopAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaStop),
                                      tr("Stop"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("stop", stopAction);
    connect(stopAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotStop()));

    // Previous media action
    QAction* prevAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSkipBackward),
                                      tr("Previous"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("prev", prevAction);
    connect(prevAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotPrevMedia()));

    // Next media action
    QAction* nextAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSkipForward),
                                      tr("Next"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("next", nextAction);
    connect(nextAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotNextMedia()));

    // Jump forward action
    QAction* jumpForwardAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSeekForward),
                                             tr("Jump Forward"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("jump_forward", jumpForwardAction);
    connect(jumpForwardAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotJumpForward()));

    // Jump backward action
    QAction* jumpBackwardAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaSeekBackward),
                                              tr("Jump Backward"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("jump_backward", jumpBackwardAction);
    connect(jumpBackwardAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotJumpBackward()));

    // Jump to time action
    QAction* jumpToTimeAction = new QAction(tr("Jump to Time"), m_mainWindow);
    jumpToTimeAction->setShortcut(QKeySequence("Ctrl+T"));
    m_mainWindow->actionCollection()->addAction("jump_to_time", jumpToTimeAction);
    connect(jumpToTimeAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotJumpToTime()));

    // Increase volume action
    QAction* incrVolumeAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaVolume),
                                            tr("Increase Volume"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("incr_volume", incrVolumeAction);
    connect(incrVolumeAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotIncrVolume()));

    // Decrease volume action
    QAction* decrVolumeAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaVolume),
                                            tr("Decrease Volume"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("decr_volume", decrVolumeAction);
    connect(decrVolumeAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotDecrVolume()));

    // Mute action
    QAction* muteAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_MediaVolumeMuted),
                                      tr("Mute"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("mute", muteAction);
    connect(muteAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotMute()));

    // Full screen toggle action
    QAction* fullScreenAction = new QAction(tr("Full Screen"), m_mainWindow);
    fullScreenAction->setCheckable(true);
    fullScreenAction->setShortcut(tr("Ctrl+F"));
    m_mainWindow->actionCollection()->addAction("full_screen", fullScreenAction);
    connect(fullScreenAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotFullScreenToggle()));

    // Playlist action
    QAction* playlistAction = new QAction(tr("Playlist"), m_mainWindow);
    playlistAction->setShortcut(QKeySequence("Ctrl+L"));
    m_mainWindow->actionCollection()->addAction("playlist", playlistAction);
    connect(playlistAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotPlaylist()));

    // Help action
    QAction* helpAction = new QAction(m_mainWindow->style()->standardIcon(QStyle::SP_DialogHelpButton),
                                      tr("Help"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("help", helpAction);
    connect(helpAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotHelp()));

    // About action
    QAction* aboutAction = new QAction(tr("About"), m_mainWindow);
    m_mainWindow->actionCollection()->addAction("about", aboutAction);
    connect(aboutAction, SIGNAL(triggered()), m_actionHandlers, SLOT(slotAbout()));
}
