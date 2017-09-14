#include "building.h"

Building::Building(Building::Type type, const std::string& name, bool populated)
    : mType(type), mName(name), mIsPopulated(populated)
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

