#pragma once

#include <list>
#include <string>

#include "../sites/building.h"

class Site;

class Event
{
public:
    enum class Type {
        Undefined,
        Construction
    };

    Event(Type type, bool calledByUser = false);

    Type getType() const;
    bool isInitializedByUser() const;

    virtual bool canBeExecuted() const = 0;
    virtual void execute() = 0;

private:
    const Type mType;
    const bool mUser;
};

class ConstructionEvent : public Event
{
public:
    ConstructionEvent(Site* site, Building::Type newBuilding);

    virtual void execute();
    bool canBeExecuted() const;

    Site* getSite() const;
    Building::Type getBuildingType() const;

private:
    Site* mSite;
    Building::Type mBuildingType;
};
