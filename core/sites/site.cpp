#include "site.h"

#include "house.h"

using namespace std;

Site::Site()
    : mBuilding(nullptr),
      mPollution(0, 100, 5, 0, 20)
{
}

bool Site::isOccupied() const
{
    return mBuilding;
}

Building* Site::getBuilding() const
{
    return mBuilding;
}

bool Site::constructBuilding(Building::Type type)
{
    if (!isOccupied())
    {
        // TODO: replace with Factory
        switch (type)
        {
        case Building::Type::NONE:
            mBuilding = nullptr;
            return true;
        case Building::Type::HOUSE:
            mBuilding = new House(this);
            return true;
        default:
            return false;
        }
    }
    return false;
}

void Site::nextTurn()
{
    ++mPollution;
}

HappinessFactor Site::getPollution() const
{
    return mPollution;
}
