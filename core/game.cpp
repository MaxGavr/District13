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
    mAdmin->nextTurn();
    mAdmin->getDistrict()->nextTurn();
    ++mTurn;
}

