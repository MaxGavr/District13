#include "building.h"
#include "site.h"

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
    TypeList types = {Type::NONE, Type::HOUSE, Type::SHOP, Type::SCHOOL, Type::PARK, Type::FACTORY};
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
            mType == Type::PARK ||
            mType == Type::FACTORY;
}

bool Building::canBeBuild() const
{
    return isPublic();
}

bool Building::affectsNeighbours() const
{
    return mType == Type::SHOP ||
           mType == Type::SCHOOL ||
            mType == Type::PARK ||
            mType == Type::FACTORY;
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

