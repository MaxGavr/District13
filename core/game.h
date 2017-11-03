#pragma once

#include <forward_list>
#include "events/event.h"

class Administration;

class Game
{
public:
    using EventQueue = std::forward_list<Event*>;

    int getHappinessGoal() const;

    Game(int happinessGoal);

    Administration* getAdministration() const;

    unsigned getTurn() const;
    bool nextTurn();

    void restartGame();
    bool isGameOver() const;

    EventQueue getExecutedEvents() const;
    void enqueueEvent(Event* event);

private:
    Administration* mAdmin;

    EventQueue mEvents;
    EventQueue mUserEvents;

    EventQueue mExecutedEvents;

    int mHappinessGoal;
    unsigned mTurn;
};
