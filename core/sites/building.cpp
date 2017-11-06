#include "building.h"
#include "site.h"

const std::map<Building::Type, int> Building::buildCosts = {
    { Building::Type::NONE, 0},
    { Building::Type::HOUSE, 0},
    { Building::Type::SHOP, 10},
    { Building::Type::SCHOOL, 10},
    { Building::Type::PARK, 10},
    { Building::Type::FACTORY, 10}
};

int Building::getBuildCost(Building::Type type)
{
    return buildCosts.find(type)->second;
}

Building::Building(Site* site, Building::Type type, int influenceArea)
    : mSite(site),
      mType(type),
      mInfluenceArea(influenceArea),
      mCondition(0, 100, 5, 50, 30)
{
}

Building::Type Building::getType() const
{
    return mType;
}

Building::TypeList Building::getAllTypes()
{
    TypeList types = {Type::NONE,
                      Type::HOUSE,
                      Type::SHOP,
                      Type::SCHOOL,
                      Type::PARK,
                      Type::FACTORY};
    return types;
}

int Building::getInfluenceArea() const
{
    return mInfluenceArea;
}

HappinessFactor Building::getCondition() const
{
    return mCondition;
}

void Building::addNeighbour(Building* neighbour)
{
    if (neighbour->getType() == Type::PARK)
        mSite->getPollution().setStep(mSite->getPollution().getStep() * 0.5);
}

void Building::removeNeighbour(Building* neighbour)
{
    if (neighbour->getType() == Type::PARK)
        mCondition.setStep(mCondition.getStep() * 2);
}

void Building::nextTurn()
{
    --mCondition;
}

