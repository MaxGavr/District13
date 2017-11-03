#include "mainwindow.h"
#include "minimap.h"
#include "../core/game.h"
#include "../core/administration.h"
#include "gameinfowidget.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QTextEdit>
#include <QLabel>


MainWindow::MainWindow(Game* game, QWidget *parent)
    : QWidget(parent),
      mGame(game)
{
    setWindowTitle(tr("Район №13"));

    initializeWidgets();
    setupLayout();
    setStyleSheet("#minimap { border: 1px solid DarkGrey }");

    updateGameInfo();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onNextTurn()
{   
    if (!mGame->nextTurn())
        gameOver();

    printMessage(tr("Ход ") + QString::number(mGame->getTurn()));
    updateGameInfo();
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
    mMinimapWidget->setObjectName("minimap");
    connect(mMinimapWidget, SIGNAL(buildEvent(Event*)), this, SLOT(onEnqueueEvent(Event*)));

    mLogWidget = new QTextEdit(tr("Добро пожаловать в Район №13!"));
    mLogWidget->setReadOnly(true);

    mNextTurnButton = new QPushButton(tr("Следующий ход"));
    mNextTurnButton->setToolTip(tr("Текущий ход - ") + QString::number(mGame->getTurn()));
    mNextTurnButton->setIcon(QIcon(":/res/icons/time"));
    mNextTurnButton->setIconSize(QSize(20, 20));
    connect(mNextTurnButton, SIGNAL(clicked(bool)), this, SLOT(onNextTurn()));

    mGameInfo = new GameInfoWidget(this);
    mGameInfo->setObjectName("gameinfo");
    mGameInfo->setCurrentTurn(mGame->getTurn());
}

void MainWindow::setupLayout()
{
    auto mainLayout = new QGridLayout();
    //mainLayout->setContentsMargins(5, 5, 5, 20);

    mainLayout->addWidget(mMinimapWidget, 0, 0, 1, 1);
    mainLayout->addWidget(mNextTurnButton, 1, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(mLogWidget, 1, 0, 1, 1);
    mainLayout->addWidget(mGameInfo, 0, 1, 1, 1, Qt::AlignTop);

    setLayout(mainLayout);
}

void MainWindow::updateGameInfo()
{
    mNextTurnButton->setToolTip(tr("Текущий ход - ") + QString::number(mGame->getTurn()));
    mGameInfo->setCurrentTurn(mGame->getTurn());

    mGameInfo->setAverageHappiness(mGame->getAdministration()->calcAverageHappiness());
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

void MainWindow::gameOver()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Конец игры"));
    msgBox.setText(tr("Вы проиграли! Ваши жители слишком несчастны!\nНачать игру заново?"));
    msgBox.setIconPixmap(QPixmap(":/res/icons/sad_face"));
    msgBox.addButton(tr("Закончить игру"), QMessageBox::RejectRole);
    msgBox.addButton(tr("Начать заново"), QMessageBox::AcceptRole);

    if (msgBox.exec() == QMessageBox::Rejected)
        close();

    restart();
}

void MainWindow::restart()
{
    mLogWidget->clear();
    printMessage(tr("Новая игра началась"));
    printMessage(tr("Добро пожаловать в Район №13"));

    mGame->restartGame();
    updateGameInfo();
}

void MainWindow::printTurnSummary()
{
    EventLogger logger;

    Game::EventQueue events = mGame->getExecutedEvents();
    for (Event* event : events)
        printMessage(logger.getEventLog(*event));
}
