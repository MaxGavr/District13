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
        PARK
    };
    using TypeList = std::list<Building::Type>;

    Building(Site* site, Building::Type type, bool populated = false);

    Building::Type getType() const;
    static TypeList getAllTypes();
    bool isHouse() const;
    bool isPublic() const;

    HappinessFactor getCondition() const;

    virtual void nextTurn();

protected:
    Site* mSite;

private:
    Building::Type mType;

    HappinessFactor mCondition;
};
