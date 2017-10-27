#include "administration.h"
#include "district.h"
#include "events/event.h"

Administration::Administration(District* district)
    : mDistrict(district)
{
    if (mDistrict)
        mDistrict->setAdministration(this);
}

District* Administration::getDistrict() const
{
    return mDistrict;
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

