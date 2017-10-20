#include "mainwindow.h"
#include "minimap.h"
#include "../core/game.h"
#include "../core/administration.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow(Game* game, QWidget *parent)
    : QWidget(parent), mGame(game)
{
    initializeWidgets();
    setupLayout();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onNextTurn()
{
    mGame->nextTurn();
    updateTurnNumber();
}

void MainWindow::initializeWidgets()
{
    mMinimapWidget = new DistrictMinimap(mGame->getAdministration()->getDistrict(), this);

    mNextTurnButton = new QPushButton(tr("Следующий ход"));
    mNextTurnButton->setToolTip(tr("Текущий ход - ") + QString::number(mGame->getTurn()));
    connect(mNextTurnButton, SIGNAL(clicked(bool)), this, SLOT(onNextTurn()));
}

void MainWindow::setupLayout()
{
    auto mainLayout = new QVBoxLayout();

    mainLayout->addWidget(mMinimapWidget);
    mainLayout->addWidget(mNextTurnButton, 0, Qt::AlignRight);

    setLayout(mainLayout);
}

void MainWindow::updateTurnNumber()
{
    mNextTurnButton->setToolTip(tr("Текущий ход - ") + QString::number(mGame->getTurn()));
}
