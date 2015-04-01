#include "actionhandlers.h"

#include "mainwindow.h"

ActionHandlers::ActionHandlers(MainWindow* mainWindow, QObject *parent) :
    QObject(parent)
{
    m_mainWindow = mainWindow;
}

void ActionHandlers::slotExit()
{
    m_mainWindow->close();
}

void ActionHandlers::slotOpen()
{

}

void ActionHandlers::slotPlay()
{

}

void ActionHandlers::slotPause()
{

}

void ActionHandlers::slotStop()
{

}

void ActionHandlers::slotPrevMedia()
{

}

void ActionHandlers::slotNextMedia()
{

}

void ActionHandlers::slotJumpForward()
{

}

void ActionHandlers::slotJumpBackward()
{

}

void ActionHandlers::slotJumpToTime()
{

}

void ActionHandlers::slotIncrVolume()
{

}

void ActionHandlers::slotDecrVolume()
{

}

void ActionHandlers::slotMute()
{

}

void ActionHandlers::slotFullScreenToggle()
{

}

void ActionHandlers::slotPlaylist()
{

}

void ActionHandlers::slotHelp()
{

}

void ActionHandlers::slotAbout()
{

}
