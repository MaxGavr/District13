#include "building.h"

Building::Building(Site* site, Building::Type type, bool populated)
    : mSite(site),
      mType(type),
      mIsPopulated(populated),
      mCondition(0, 100, 5, 50, 30)
{
}

Building::Type Building::getType() const
{
    return mType;
}

bool Building::isPopulated() const
{
    return mIsPopulated;
}

HappinessFactor Building::getCondition() const
{
    return mCondition;
}

void Building::nextTurn()
{
    --mCondition;
}

