#include "actioncollection.h"

ActionCollection::ActionCollection(QObject *parent) :
    QObject(parent)
{

}

void ActionCollection::addAction(QString key, QAction *action)
{
    m_actions[key] = action;
}

QAction* ActionCollection::action(QString key)
{
    if(m_actions.contains(key)) {
        return m_actions[key];
    } else {
        return 0;
    }
}
