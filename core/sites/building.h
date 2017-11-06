#pragma once

#include <string>
#include <list>
#include <map>
#include "../factor.h"

class Site;

class Building
{
public:
    enum class Type {
        NONE = 0,
        HOUSE,
        SHOP,
        SCHOOL,
        PARK,
        FACTORY
    };
    using TypeList = std::list<Building::Type>;

    Building::Type getType() const;
    static TypeList getAllTypes();

    Building(Site* site, Building::Type type, int influenceArea = 0);

    static int getBuildCost(Building::Type type);

    virtual bool isHouse() const = 0;
    virtual bool isPublic() const = 0;

    virtual bool affectsNeighbours() const = 0;
    int getInfluenceArea() const;

    HappinessFactor getCondition() const;

    virtual void addNeighbour(Building* neighbour);
    virtual void removeNeighbour(Building* neighbour);

    virtual void nextTurn();

protected:
    Site* mSite;

private:
    static const std::map<Building::Type, int> buildCosts;

    Building::Type mType;
    int mInfluenceArea;

    HappinessFactor mCondition;
};
