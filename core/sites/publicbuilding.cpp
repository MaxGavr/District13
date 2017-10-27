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
    : Building(site, getBuildingType(type))
{

}

HappinessFactor PublicBuilding::getFactor() const
{
    return mFactor;
}

void PublicBuilding::nextTurn()
{
    Building::nextTurn();
}
