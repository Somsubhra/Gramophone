#include <QtGui>

#include "gramophone.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Gramophone");
    app.setQuitOnLastWindowClosed(true);
    app.setApplicationVersion("1.0");

    Gramophone window;
    window.showMaximized();
    window.show();
    return app.exec();
}


