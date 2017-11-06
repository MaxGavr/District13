#include "game.h"
#include "administration.h"
#include "district.h"

int Game::getHappinessGoal() const
{
    return mHappinessGoal;
}

Game::Game(int happinessGoal)
    : mAdmin(nullptr), mHappinessGoal(happinessGoal), mTurn(0)
{
    District* district = new District(10);

    mAdmin = new Administration(district, 100, 10);
}

Administration* Game::getAdministration() const
{
    return mAdmin;
}

unsigned Game::getTurn() const
{
    return mTurn;
}

bool Game::nextTurn()
{
    if (isGameOver())
        return false;

    mExecutedEvents.clear();

    // execute environment events
    for (Event* event : mEvents)
        if (event->canBeExecuted())
        {
            event->execute();
            mExecutedEvents.push_front(event);
        }
    mEvents.clear();

    // execute user events
    for (Event* event : mUserEvents)
        if (event->canBeExecuted())
        {
            event->execute();
            mExecutedEvents.push_front(event);
        }
    mUserEvents.clear();

    mAdmin->nextTurn();
    mAdmin->getDistrict()->nextTurn();

    ++mTurn;
    return true;
}

void Game::restartGame()
{
    mEvents.clear();
    mUserEvents.clear();
    mExecutedEvents.clear();

    delete mAdmin;
    mAdmin = new Administration(new District(10), 100, 10);

    mTurn = 0;
}

bool Game::isGameOver() const
{
    return mAdmin->calcAverageHappiness() < mHappinessGoal;
}

Game::EventQueue Game::getExecutedEvents() const
{
    return mExecutedEvents;
}

void Game::enqueueEvent(Event* event)
{
    if (event->isInitializedByUser())
        mUserEvents.push_front(event);
    else
        mEvents.push_front(event);
}
