#include "building.h"

Building::Building(Site* site, Building::Type type, const std::string& name, bool populated)
    : mSite(site),
      mType(type),
      mName(name),
      mIsPopulated(populated),
      mCondition(0, 100, 5, 50, 30)
{
}

Building::Type Building::getType() const
{
    return mType;
}

std::string Building::getName() const
{
    return mName;
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

