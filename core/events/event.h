#pragma once

#include <list>
#include <string>

#include "../sites/building.h"

class Site;

class Event
{
public:
    Event(bool calledByUser = false);

    virtual void execute() = 0;
    bool canBeExecuted() const = 0;

    bool isInitializedByUser() const;

private:
    bool mUser;
};

class ConstructionEvent : public Event
{
public:
    ConstructionEvent(Site* site, Building::Type newBuilding);

    virtual void execute();
    bool canBeExecuted() const;

private:
    Site* mSite;
    Building::Type mBuildingType;
};
