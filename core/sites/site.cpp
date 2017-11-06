#include "site.h"

#include "house.h"
#include "publicbuilding.h"
#include "industrialbuilding.h"

using namespace std;

Site::Site(int posX, int posY)
    : mAddress({posX, posY}),
      mBuilding(nullptr),
      mPendingConstruction(false),
      mCleanliness(0, 100, 5, 100, 20)
{
    mCleanliness.setValue(100);
}

Site::Address Site::getAddress() const
{
    return mAddress;
}

bool Site::isOccupied() const
{
    return mBuilding;
}

bool Site::isPendingConstruction() const
{
    return mPendingConstruction;
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
        case Building::Type::FACTORY:
            mBuilding = new IndustrialBuilding(this);
            success = true;
            break;
        default:
            success = false;
            break;
        }

        if (success)
            mPendingConstruction = false;

        return success;
    }
    return false;
}

void Site::nextTurn()
{
    if (mBuilding)
        mBuilding->nextTurn();
    --mCleanliness;
}

HappinessFactor& Site::getPollution()
{
    return mCleanliness;
}
