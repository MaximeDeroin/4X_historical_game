#include "mainwindow.h"
#include <QApplication>
#include "gui/userinterfacemanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    UserInterfaceManager guiManager;
    guiManager.show();
//    MainWindow w;
//    w.show();

    return app.exec();
}
