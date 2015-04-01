#include "actionhandlers.h"

#include <QFileDialog>
#include <QStringList>
#include <QStandardPaths>

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
    QString mediaDir = QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0);
    QString filter = tr("Media Files (*.3gp *.mp4 *.avi *.mp3);;All Files (*.*)");

    QStringList fileList = QFileDialog::getOpenFileNames(m_mainWindow,
                                                         tr("Select Media Files to play"),
                                                         mediaDir,
                                                         filter);

    m_mainWindow->player()->playLocalFile(QUrl::fromLocalFile(fileList.at(0)));
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
