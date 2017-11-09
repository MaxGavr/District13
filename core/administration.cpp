#include "administration.h"
#include "district.h"
#include "events/event.h"
#include "sites/site.h"
#include "sites/house.h"
#include "sites/industrialbuilding.h"

Administration::Administration(District* district, int startMoney, int maxIncome)
    : mDistrict(district), mMoney(startMoney), mMaxIncome(maxIncome)
{
    if (mDistrict)
        mDistrict->setAdministration(this);
}

Administration::~Administration()
{
    if (mDistrict)
        delete mDistrict;
}

District* Administration::getDistrict() const
{
    return mDistrict;
}

int Administration::calcAverageHappiness() const
{
    int sumHappiness = 0;
    int totalHouses = 0;
    for (size_t i = 0; i < mDistrict->getSize(); ++i)
    {
        for (size_t j = 0; j < mDistrict->getSize(); ++j)
        {
            House* house = dynamic_cast<House*>(mDistrict->getBuildingAt(i, j));

            if (house)
            {
                sumHappiness += house->getHappiness();
                ++totalHouses;
            }
        }
    }

    return (double)sumHappiness / totalHouses;
}

int Administration::calcIncome() const
{
    int happiness = calcAverageHappiness();
    int maxHappiness = House::getMaxHappiness();

    int baseIncome = (double)happiness / maxHappiness * mMaxIncome;

    int factoryIncome = 0;
    for (size_t i = 0; i < mDistrict->getSize(); ++i)
    {
        for (size_t j = 0; j < mDistrict->getSize(); ++j)
        {
            auto factory = dynamic_cast<Factory*>(mDistrict->getBuildingAt(i, j));
            if (factory)
                factoryIncome += factory->calcIncome();
        }
    }

    return baseIncome + factoryIncome;
}

int Administration::getCurrentMoney() const
{
    return mMoney;
}

void Administration::changeMoney(int amount)
{
    mMoney += amount;

    if (mMoney < 0)
        mMoney = 0;
}

void Administration::nextTurn()
{
    changeMoney(calcIncome());
}

ConstructionEvent* Administration::constructBuilding(Site::Address address, Building::Type type)
{
    if (mMoney < Building::getBuildCost(type))
        return nullptr;

    Site* site = mDistrict->getSiteAt(address);
    auto event = new ConstructionEvent(site, type);

    changeMoney(-Building::getBuildCost(type));

    return event;
}

RepairingEvent* Administration::repairBuilding(Site::Address address)
{
    Building* building = mDistrict->getBuildingAt(address);
    if (!building || building->getCondition().getValue() == building->getCondition().getMaxValue())
        return nullptr;

    if (mMoney < building->calcRepairCost())
        return nullptr;

    auto event = new RepairingEvent(building);
    changeMoney(-building->calcRepairCost());

    return event;
}

CleaningEvent* Administration::cleanSite(Site::Address address)
{
    Site* site = mDistrict->getSiteAt(address);
    if (site->getCleanliness().getValue() == site->getCleanliness().getMaxValue())
        return nullptr;

    if (mMoney < site->calcCleaningCost())
        return nullptr;

    auto event = new CleaningEvent(site);
    changeMoney(-site->calcCleaningCost());

    return event;
}
