#include "publicbuilding.h"

Building::Type PublicBuilding::getBuildingType(PublicBuilding::Type type)
{
    switch (type)
    {
    case PublicBuilding::Type::SHOP:
        return Building::Type::SHOP;
    case PublicBuilding::Type::SCHOOL:
        return Building::Type::SCHOOL;
    case PublicBuilding::Type::PARK:
        return Building::Type::PARK;
    default:
        return Building::Type::NONE;
    }
}

PublicBuilding::PublicBuilding(Site* site, PublicBuilding::Type type)
    : Building(site, getBuildingType(type), chooseInfluenceArea(type))
{
    mFactor = HappinessFactor(1, 1, 0, 0, 20);
    mFactor.setValue(mFactor.getMaxValue());
}

HappinessFactor PublicBuilding::getFactor() const
{
    return mFactor;
}

void PublicBuilding::nextTurn()
{
    Building::nextTurn();
}

int PublicBuilding::chooseInfluenceArea(PublicBuilding::Type type) const
{
    switch (type)
    {
    case Type::PARK:
        return 3;
    case Type::SHOP:
        return 2;
    case Type::SCHOOL:
        return 3;
    default:
        return 0;
    }
}
