#include "playbackpanel.h"

#include <QGridLayout>

#include "mainwindow.h"

PlaybackPanel::PlaybackPanel(MainWindow* mainWindow, QWidget *parent) :
    QWidget(parent)
{
    m_mainWindow = mainWindow;

    this->setMaximumHeight(50);

    QGridLayout* mainLayout = new QGridLayout(this);

    m_playbackButtons = new PlaybackButtons(m_mainWindow, this);
    mainLayout->addWidget(m_playbackButtons, 0, 0);

    this->setLayout(mainLayout);
}
