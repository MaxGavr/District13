#include "event.h"
#include "../sites/site.h"

Event::Event(bool calledByUser)
    : mUser(calledByUser)
{

}

bool Event::isInitializedByUser() const
{
    return mUser;
}

ConstructionEvent::ConstructionEvent(Site* site, Building::Type newBuilding)
    : Event(true), mSite(site), mBuildingType(newBuilding)
{

}

void ConstructionEvent::execute()
{
    mSite->constructBuilding(mBuildingType);
}

bool ConstructionEvent::canBeExecuted() const
{
    return mSite && !mSite->getBuilding();
}
