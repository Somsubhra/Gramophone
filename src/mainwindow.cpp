#include "mainwindow.h"

#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle(tr("Gramophone"));
    this->setWindowState(Qt::WindowMaximized);

    m_actionCollection = new ActionCollection(this);

    m_standardActions = new StandardActions(this, this);
    m_standardActions->createStandardActions();

    this->createMenuBar();
}

void MainWindow::createMenuBar()
{
    // File menu
    QMenu* fileMenu = this->menuBar()->addMenu(tr("Media"));
    fileMenu->addAction(m_actionCollection->action("open"));
    fileMenu->addSeparator();
    fileMenu->addAction(m_actionCollection->action("exit"));

    // Playback menu
    QMenu* playbackMenu = this->menuBar()->addMenu(tr("Playback"));
    playbackMenu->addAction(m_actionCollection->action("play"));
    playbackMenu->addAction(m_actionCollection->action("pause"));
    playbackMenu->addAction(m_actionCollection->action("stop"));
    playbackMenu->addSeparator();
    playbackMenu->addAction(m_actionCollection->action("prev"));
    playbackMenu->addAction(m_actionCollection->action("next"));
    playbackMenu->addSeparator();
    playbackMenu->addAction(m_actionCollection->action("jump_backward"));
    playbackMenu->addAction(m_actionCollection->action("jump_forward"));
    playbackMenu->addAction(m_actionCollection->action("jump_to_time"));
}

ActionCollection* MainWindow::actionCollection()
{
    return m_actionCollection;
}
