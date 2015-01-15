#include "mainwindow.h"

#include <QMenuBar>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle(tr("Gramophone"));
    this->setWindowState(Qt::WindowMaximized);

    m_actionCollection = new ActionCollection(this);

    m_standardActions = new StandardActions(this, this);
    m_standardActions->createStandardActions();

    this->createMenuBar();

    QWidget* mainWidget = new QWidget(this);
    QGridLayout* mainLayout = new QGridLayout(mainWidget);

    m_videoWidget = new VideoWidget(this, mainWidget);
    mainLayout->addWidget(m_videoWidget, 0, 0);

    m_playbackPanel = new PlaybackPanel(this, mainWidget);
    mainLayout->addWidget(m_playbackPanel, 1, 0);

    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
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

    // Audio menu
    QMenu* audioMenu = this->menuBar()->addMenu(tr("Audio"));
    audioMenu->addAction(m_actionCollection->action("incr_volume"));
    audioMenu->addAction(m_actionCollection->action("decr_volume"));
    audioMenu->addAction(m_actionCollection->action("mute"));

    // Video menu
    QMenu* videoMenu = this->menuBar()->addMenu(tr("Video"));
    videoMenu->addAction(m_actionCollection->action("full_screen"));

    // View menu
    QMenu* viewMenu = this->menuBar()->addMenu(tr("View"));
    viewMenu->addAction(m_actionCollection->action("playlist"));

    // Help menu
    QMenu* helpMenu = this->menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(m_actionCollection->action("help"));
    helpMenu->addSeparator();
    helpMenu->addAction(m_actionCollection->action("about"));
}

ActionCollection* MainWindow::actionCollection()
{
    return m_actionCollection;
}
