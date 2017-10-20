#pragma once

#include <queue>
#include "events/event.h"

class Administration;

class Game
{
public:
    using EventQueue = std::queue<Event>;

    Game();

    Administration* getAdministration() const;

    unsigned getTurn() const;
    void nextTurn();

private:
    Administration* mAdmin;

    EventQueue mEvents;
    EventQueue mUserEvents;

    unsigned mTurn;
};
