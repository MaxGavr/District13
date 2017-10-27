#include "building.h"

Building::Building(Site* site, Building::Type type, bool populated)
    : mSite(site),
      mType(type),
      mCondition(0, 100, 5, 50, 30)
{
}

Building::Type Building::getType() const
{
    return mType;
}

Building::TypeList Building::getAllTypes()
{
    TypeList types;
    types.push_back(Type::NONE);
    types.push_back(Type::HOUSE);
    types.push_back(Type::SHOP);
    types.push_back(Type::SCHOOL);
    types.push_back(Type::PARK);
    return types;
}

bool Building::isHouse() const
{
    return mType == Type::HOUSE;
}

bool Building::isPublic() const
{
    return mType == Type::SHOP ||
           mType == Type::SCHOOL ||
           mType == Type::PARK;
}

HappinessFactor Building::getCondition() const
{
    return mCondition;
}

void Building::nextTurn()
{
    --mCondition;
}

