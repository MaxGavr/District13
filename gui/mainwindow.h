#pragma once

#include <QMainWindow>

class DistrictMinimap;
class District;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(District* district, QWidget *parent = 0);
    ~MainWindow();

private:
    DistrictMinimap* mMinimapWidget;
};
