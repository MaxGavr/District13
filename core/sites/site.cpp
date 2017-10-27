#include "site.h"

#include "house.h"
#include "publicbuilding.h"

using namespace std;

Site::Site(int posX, int posY)
    : mAddress({posX, posY}),
      mBuilding(nullptr),
      mPollution(0, 100, 5, 0, 20)
{
}

Site::Address Site::getAddress() const
{
    return mAddress;
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
        bool success;

        // TODO: replace with Factory
        switch (type)
        {
        case Building::Type::NONE:
            mBuilding = nullptr;
            success = true;
            break;
        case Building::Type::HOUSE:
            mBuilding = new House(this);
            success = true;
            break;
        case Building::Type::SHOP:
            mBuilding = new PublicBuilding(this, PublicBuilding::Type::SHOP);
            success = true;
            break;
        case Building::Type::SCHOOL:
            mBuilding = new PublicBuilding(this, PublicBuilding::Type::SCHOOL);
            success = true;
            break;
        case Building::Type::PARK:
            mBuilding = new PublicBuilding(this, PublicBuilding::Type::PARK);
            success = true;
            break;
        default:
            success = false;
            break;
        }
        return success;
    }
    return false;
}

void Site::nextTurn()
{
    if (mBuilding)
        mBuilding->nextTurn();
    ++mPollution;
}

HappinessFactor Site::getPollution() const
{
    return mPollution;
}
