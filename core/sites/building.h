#pragma once

#include <string>
#include <list>
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

    Building(Site* site, Building::Type type, int influenceArea = 0);

    Building::Type getType() const;
    static TypeList getAllTypes();

    bool isHouse() const;
    bool isPublic() const;
    bool canBeBuild() const;

    bool affectsNeighbours() const;
    int getInfluenceArea() const;

    HappinessFactor getCondition() const;

    virtual void addNeighbour(Building* neighbour);
    virtual void removeNeighbour(Building* neighbour);

    virtual void nextTurn();

protected:
    Site* mSite;

private:
    Building::Type mType;
    int mInfluenceArea;

    HappinessFactor mCondition;
};
