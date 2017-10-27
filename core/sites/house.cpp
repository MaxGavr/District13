#include "house.h"
#include "site.h"
#include "publicbuilding.h"
#include <algorithm>


House::House(Site* site)
    : Building(site, Building::Type::HOUSE),
      mHappiness(getBaseHappiness())
{

}

int House::getHappiness() const
{
    return mHappiness;
}

void House::addPublicBuilding(PublicBuilding* building)
{
    if (std::find(mNearestBuildings.cbegin(), mNearestBuildings.cend(), building)
             == mNearestBuildings.cend())
        mNearestBuildings.push_back(building);
}

std::vector<HappinessFactor> House::getFactors() const
{
    std::vector<HappinessFactor> factors;
    factors.push_back(mSite->getPollution());
    factors.push_back(getCondition());

    for (PublicBuilding* building : mNearestBuildings)
        factors.push_back(building->getFactor());

    return factors;
}

void House::calculateHappiness()
{
    std::vector<HappinessFactor> factors = getFactors();

    for (auto it = factors.cbegin(); it != factors.cend(); ++it)
        mHappiness += it->getHappinessImpact();

    if (mHappiness < getMinHappiness())
        mHappiness = getMinHappiness();
    if (mHappiness > getMaxHappiness())
        mHappiness = getMaxHappiness();
}

void House::nextTurn()
{
    Building::nextTurn();

    calculateHappiness();
}

