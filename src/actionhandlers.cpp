#include "actionhandlers.h"

#include "mainwindow.h"

ActionHandlers::ActionHandlers(MainWindow* mainWindow, QObject *parent) :
    QObject(parent)
{
    m_mainWindow = mainWindow;
}
