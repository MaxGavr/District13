#include "site.h"

#include "house.h"

using namespace std;

Site::Site()
    : mBuilding(nullptr)
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
            mBuilding = new House();
            return true;
        default:
            return false;
        }
    }
}
