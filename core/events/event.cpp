#include "event.h"
#include "../sites/site.h"

/////////////////////////////////////////////////////////////////
// Event
/////////////////////////////////////////////////////////////////

Event::Event(Type type, bool calledByUser)
    : mType(type), mUser(calledByUser)
{

}

Event::Type Event::getType() const
{
    return mType;
}

bool Event::isInitializedByUser() const
{
    return mUser;
}

/////////////////////////////////////////////////////////////////
// ConstructionEvent
/////////////////////////////////////////////////////////////////

ConstructionEvent::ConstructionEvent(Site* site, Building::Type newBuilding)
    : Event(Event::Type::Construction, true),
      mSite(site),
      mBuildingType(newBuilding)
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

Site* ConstructionEvent::getSite() const
{
    return mSite;
}

Building::Type ConstructionEvent::getBuildingType() const
{
    return mBuildingType;
}
