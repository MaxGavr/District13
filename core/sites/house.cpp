#include "house.h"
#include "site.h"


House::House(Site* site)
    : Building(site, Building::Type::HOUSE, "house", true),
      mHappiness(getBaseHappiness())
{

}

std::vector<HappinessFactor> House::getFactors() const
{
    std::vector<HappinessFactor> factors;
    factors.push_back(mSite->getPollution());
    factors.push_back(getCondition());

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

