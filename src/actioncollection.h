#ifndef ACTIONCOLLECTION_H
#define ACTIONCOLLECTION_H

#include <QObject>
#include <QAction>
#include <QHash>

class ActionCollection : public QObject
{
    Q_OBJECT
public:
    explicit ActionCollection(QObject *parent = 0);

    void addAction(QString key, QAction* action);
    QAction* action(QString key);

signals:

public slots:

private:
    QHash<QString, QAction*> m_actions;
};

#endif // ACTIONCOLLECTION_H
