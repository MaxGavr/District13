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

    printTurnSummary();
    mMinimapWidget->updateMinimap();
}

void MainWindow::onEnqueueEvent(Event* event)
{
    mGame->enqueueEvent(event);

    EventLogger logger;
    printMessage(logger.getEventPreview(*event));
}

void MainWindow::initializeWidgets()
{
    mMinimapWidget = new DistrictMinimap(mGame->getAdministration()->getDistrict(), this);
    connect(mMinimapWidget, SIGNAL(buildEvent(Event*)), this, SLOT(onEnqueueEvent(Event*)));

    mLogWidget = new QTextEdit(tr("Добро пожаловать в Район №13!"));
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

    Game::EventQueue events = mGame->getExecutedEvents();
    for (Event* event : events)
        printMessage(logger.getEventLog(*event));
}
