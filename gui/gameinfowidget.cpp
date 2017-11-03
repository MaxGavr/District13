#include "gameinfowidget.h"

#include <QLabel>
#include <QVBoxLayout>

GameInfoWidget::GameInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    mCurrentTurn = new QLabel();
    mHappiness = new QLabel();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(mCurrentTurn);
    layout->addWidget(mHappiness);
    setLayout(layout);
}

void GameInfoWidget::setCurrentTurn(int turn)
{
    mCurrentTurn->setText(tr("Ход №") + QString::number(turn));
}

void GameInfoWidget::setAverageHappiness(int happiness)
{
    mHappiness->setText("<b>" + tr("Уровень счастья: ") + QString::number(happiness) + "</b>");
}

