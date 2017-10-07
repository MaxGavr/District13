#pragma once

#include <string>
#include "../factor.h"

class Site;

class Building
{
public:
    enum class Type {
        NONE = 0,
        HOUSE
    };

    Building(Site* site, Building::Type type, const std::string& name, bool populated = false);

    Building::Type getType() const;
    std::string getName() const;
    bool isPopulated() const;

    HappinessFactor getCondition() const;

    virtual void nextTurn();

protected:
    Site* mSite;

private:
    Building::Type mType;
    std::string mName;

    bool mIsPopulated;

    HappinessFactor mCondition;
};
