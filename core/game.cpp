#include "game.h"
#include "administration.h"
#include "district.h"

Game::Game()
    : mAdmin(nullptr)
{
    District* district = new District(10);

    mAdmin = new Administration(district);
}

Administration* Game::getAdministration() const
{
    return mAdmin;
}

