#include "mainwindow.h"
#include "minimap.h"
#include "../core/game.h"
#include "../core/administration.h"
#include "../core/sites/site.h"
#include "../core/sites/building.h"
#include "gameinfowidget.h"
#include "siteinfodialog.h"
#include "actionswidget.h"

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
    if (!event)
        return;

    mGame->enqueueEvent(event);

    EventLogger logger;
    printMessage(logger.getEventLog(*event, true));

    updateGameInfo();
}

void MainWindow::onSelectSite(Site* site)
{
    DistrictMinimapItem* previouslySelected = mMinimapWidget->getSelectedItem();
    if (previouslySelected && previouslySelected->getSite()->isOccupied())
    {
        Site* site = previouslySelected->getSite();
        Site::Address addr = site->getAddress();
        mMinimapWidget->highlightArea(addr.first, addr.second, site->getBuilding()->getInfluenceArea(), false);
    }

    mSiteInfo->showSiteInfo(site);
    mActionsWidget->chooseActions(site);

    Building* building = site->getBuilding();
    if (building && building->affectsNeighbours())
    {
        Site::Address addr = site->getAddress();
        mMinimapWidget->highlightArea(addr.first, addr.second, building->getInfluenceArea());
    }
}

void MainWindow::initializeWidgets()
{
    mMinimapWidget = new DistrictMinimap(mGame->getAdministration()->getDistrict(), this);
    mMinimapWidget->setObjectName("minimap");
    mMinimapWidget->layout()->setSizeConstraint(QLayout::SetFixedSize);
    connect(mMinimapWidget, SIGNAL(siteSelected(Site*)), this, SLOT(onSelectSite(Site*)));

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

    mSiteInfo = new SiteInfoDialog(this);
    mSiteInfo->hide();

    mActionsWidget = new ActionsWidget(mGame->getAdministration(), this);
    connect(mActionsWidget, SIGNAL(initEvent(Event*)), this, SLOT(onEnqueueEvent(Event*)));
}

void MainWindow::setupLayout()
{
    auto mainLayout = new QGridLayout();
    //mainLayout->setContentsMargins(5, 5, 5, 20);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(mMinimapWidget, 0, 0, 3, 1);
    mainLayout->addWidget(mNextTurnButton, 3, 1, 1, 1, Qt::AlignVCenter | Qt::AlignLeft);
    mainLayout->addWidget(mLogWidget, 3, 0, 1, 1, Qt::AlignTop);
    mainLayout->addWidget(mGameInfo, 0, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(mSiteInfo, 1, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(mActionsWidget, 2, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft);

    setLayout(mainLayout);
}

void MainWindow::updateGameInfo()
{
    mNextTurnButton->setToolTip(tr("Текущий ход - ") + QString::number(mGame->getTurn()));

    Administration* admin = mGame->getAdministration();

    mGameInfo->setCurrentTurn(mGame->getTurn());
    mGameInfo->setAverageHappiness(admin->calcAverageHappiness());
    mGameInfo->setCurrentMoney(admin->getCurrentMoney(), admin->calcIncome());
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
    mMinimapWidget->setDistrict(mGame->getAdministration()->getDistrict());
    updateGameInfo();
}

void MainWindow::printTurnSummary()
{
    EventLogger logger;

    Game::EventQueue events = mGame->getExecutedEvents();
    for (Event* event : events)
        printMessage(logger.getEventLog(*event));
}
