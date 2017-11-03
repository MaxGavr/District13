#include "gui/mainwindow.h"
#include "core/game.h"
#include "core/administration.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);

    Game game(20);

    MainWindow w(&game);
    w.show();

    return a.exec();
}
