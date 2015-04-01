#ifndef ACTIONHANDLERS_H
#define ACTIONHANDLERS_H

#include <QObject>

class MainWindow;

class ActionHandlers : public QObject
{
    Q_OBJECT
public:
    explicit ActionHandlers(MainWindow* mainWindow, QObject *parent = 0);

signals:

public slots:

private:
    MainWindow* m_mainWindow;
};

#endif // ACTIONHANDLERS_H
