#include "administration.h"
#include "district.h"
#include "events/event.h"
#include "sites/site.h"
#include "sites/house.h"

Administration::Administration(District* district)
    : mDistrict(district)
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
    for (int i = 0; i < mDistrict->getSize(); ++i)
    {
        for (int j = 0; j < mDistrict->getSize(); ++j)
        {
            Building* building = mDistrict->getSiteAt(i, j)->getBuilding();

            if (building && building->isHouse())
            {
                sumHappiness += dynamic_cast<House*>(building)->getHappiness();
                ++totalHouses;
            }
        }
    }

    return (double)sumHappiness / totalHouses;
}

void Administration::nextTurn()
{

}

ConstructionEvent* Administration::constructBuilding(std::size_t x, std::size_t y, Building::Type type)
{
    Site* site = mDistrict->getSiteAt(x, y);
    auto event = new ConstructionEvent(site, type);
    return event;
}

