#include "mainwindow.h"
#include "minimap.h"

MainWindow::MainWindow(District* district, QWidget *parent) :
    QMainWindow(parent)
{
    mMinimapWidget = new DistrictMinimap(district, this);

    setCentralWidget(mMinimapWidget);
}

MainWindow::~MainWindow()
{

}
