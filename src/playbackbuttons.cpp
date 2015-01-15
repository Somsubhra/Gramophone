#include "playbackbuttons.h"

#include "mainwindow.h"

PlaybackButtons::PlaybackButtons(MainWindow *mainWindow, QWidget *parent) :
    QToolBar(parent)
{
    m_mainWindow = mainWindow;
    this->setupActions();
}

void PlaybackButtons::setupActions()
{
    this->addAction(m_mainWindow->actionCollection()->action("play"));
    this->addAction(m_mainWindow->actionCollection()->action("stop"));

    this->addSeparator();

    this->addAction(m_mainWindow->actionCollection()->action("prev"));
    this->addAction(m_mainWindow->actionCollection()->action("jump_backward"));
    this->addAction(m_mainWindow->actionCollection()->action("jump_forward"));
    this->addAction(m_mainWindow->actionCollection()->action("next"));
}
