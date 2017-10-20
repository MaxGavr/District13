#include "mainwindow.h"
#include "minimap.h"
#include "../core/game.h"
#include "../core/administration.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QTextEdit>


MainWindow::MainWindow(Game* game, QWidget *parent)
    : QWidget(parent),
      mGame(game)
{
    setWindowState(Qt::WindowMaximized);

    initializeWidgets();
    setupLayout();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onNextTurn()
{
    mGame->nextTurn();
    printMessage(tr("Ход ") + QString::number(mGame->getTurn()));
    updateTurnNumber();
}

void MainWindow::initializeWidgets()
{
    mMinimapWidget = new DistrictMinimap(mGame->getAdministration()->getDistrict(), this);

    mLogWidget = new QTextEdit(tr("Добро пожаловать в Район №13! Удачи, она вам понадобится..."));
    mLogWidget->setReadOnly(true);

    mNextTurnButton = new QPushButton(tr("Следующий ход"));
    mNextTurnButton->setToolTip(tr("Текущий ход - ") + QString::number(mGame->getTurn()));
    connect(mNextTurnButton, SIGNAL(clicked(bool)), this, SLOT(onNextTurn()));
}

void MainWindow::setupLayout()
{
    auto mainLayout = new QGridLayout();
    //mainLayout->setContentsMargins(5, 5, 5, 20);

    mainLayout->addWidget(mMinimapWidget, 0, 0, 1, 1);
    mainLayout->addWidget(mNextTurnButton, 1, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(mLogWidget, 1, 0, 1, 1);

    setLayout(mainLayout);
}

void MainWindow::updateTurnNumber()
{
    mNextTurnButton->setToolTip(tr("Текущий ход - ") + QString::number(mGame->getTurn()));
}

void MainWindow::printMessage(const QString& message)
{
    mLogWidget->append(message);
}

void MainWindow::printMessage(const EventLogger::EventSummary& summary)
{
    for (const QString& message : summary)
        printMessage(message);
}

void MainWindow::printTurnSummary()
{
    EventLogger logger;

    Game::EventQueue userEvents = mGame->getUserEvents();
    for (Event* event : userEvents)
        printMessage(logger.getEventLog(*event));

    Game::EventQueue events = mGame->getEvents();
    for (Event* event : events)
        printMessage(logger.getEventLog(*event));
}
