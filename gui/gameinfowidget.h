#pragma once

#include <QWidget>

class QLabel;

class GameInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameInfoWidget(QWidget *parent = 0);

    void setCurrentTurn(int turn);
    void setAverageHappiness(int happiness);

private:
    QLabel* mCurrentTurn;
    QLabel* mHappiness;
};
