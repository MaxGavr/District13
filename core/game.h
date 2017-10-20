#pragma once

#include <forward_list>
#include "events/event.h"

class Administration;

class Game
{
public:
    using EventQueue = std::forward_list<Event*>;

    Game();

    Administration* getAdministration() const;

    unsigned getTurn() const;
    void nextTurn();

    EventQueue getEvents() const;
    EventQueue getUserEvents() const;

private:
    Administration* mAdmin;

    EventQueue mEvents;
    EventQueue mUserEvents;

    unsigned mTurn;
};
