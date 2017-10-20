#include "gui/mainwindow.h"
#include "core/game.h"
#include "core/administration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;

    MainWindow w(&game);
    w.show();

    return a.exec();
}
