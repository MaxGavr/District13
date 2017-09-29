#pragma once

class Administration;

class Game
{
public:
    Game();

    Administration* getAdministration() const;

private:
    Administration* mAdmin;
};
