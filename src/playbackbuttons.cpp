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
}
