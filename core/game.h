#pragma once

class Administration;

class Game
{
public:
    Game();

    Administration* getAdministration() const;

    unsigned getTurn() const;
    void nextTurn();

private:
    Administration* mAdmin;

    unsigned mTurn;
};
