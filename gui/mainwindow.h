#pragma once

#include <QWidget>

class DistrictMinimap;
class Game;
class QPushButton;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(Game* game, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onNextTurn();

private:
    void initializeWidgets();
    void setupLayout();

    void updateTurnNumber();

    Game* mGame;

    DistrictMinimap* mMinimapWidget;

    QPushButton* mNextTurnButton;
};
