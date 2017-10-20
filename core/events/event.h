#pragma once

#include <list>
#include <string>

#include "../sites/building.h"

class Site;

class Event
{
public:
    friend class Game;

    enum class Type {
        Undefined,
        Construction
    };

    Event(Type type, bool calledByUser = false);

    Type getType() const;
    bool isInitializedByUser() const;

    virtual bool canBeExecuted() const = 0;

private:
    virtual void execute() = 0;

    const Type mType;
    const bool mUser;
};

class ConstructionEvent : public Event
{
public:
    ConstructionEvent(Site* site, Building::Type newBuilding);

    bool canBeExecuted() const;

    Site* getSite() const;
    Building::Type getBuildingType() const;

private:
    virtual void execute();

    Site* mSite;
    Building::Type mBuildingType;
};
