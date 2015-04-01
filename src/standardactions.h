#ifndef STANDARDACTIONS_H
#define STANDARDACTIONS_H

#include <QObject>

#include "actionhandlers.h"

class MainWindow;

class StandardActions : public QObject
{
    Q_OBJECT
public:
    explicit StandardActions(MainWindow* mainWindow, QObject* parent = 0);

    void createStandardActions();

signals:

public slots:

private:
    MainWindow* m_mainWindow;
    ActionHandlers* m_actionHandlers;
};

#endif // STANDARDACTIONS_H
