#include "game.h"
#include "administration.h"
#include "district.h"

Game::Game()
    : mAdmin(nullptr), mTurn(0)
{
    District* district = new District(10);

    mAdmin = new Administration(district);
}

Administration* Game::getAdministration() const
{
    return mAdmin;
}

unsigned Game::getTurn() const
{
    return mTurn;
}

void Game::nextTurn()
{
    mExecutedEvents.clear();

    mAdmin->nextTurn();
    mAdmin->getDistrict()->nextTurn();

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

    ++mTurn;
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
