#ifndef STANDARDACTIONS_H
#define STANDARDACTIONS_H

#include <QObject>

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

};

#endif // STANDARDACTIONS_H
