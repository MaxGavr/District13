#pragma once

#include "eventlogger.h"
#include <QWidget>

class DistrictMinimap;
class Game;
class QPushButton;
class QTextEdit;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(Game* game, QWidget *parent = 0);
    ~MainWindow();

    void printTurnSummary();

public slots:
    void onNextTurn();

    void onEnqueueEvent(Event* event);

private:
    void initializeWidgets();
    void setupLayout();

    void updateTurnNumber();

    void printMessage(const QString& message);
    void printMessage(const EventLogger::EventSummary& summary);

private:
    Game* mGame;

    DistrictMinimap* mMinimapWidget;
    QTextEdit* mLogWidget;
    QPushButton* mNextTurnButton;
};
