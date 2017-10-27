#pragma once

#include "building.h"

class PublicBuilding : public Building
{
public:
    enum class Type {
        SHOP,
        SCHOOL,
        PARK
    };

    static Building::Type getBuildingType(PublicBuilding::Type type);

    PublicBuilding(Site* site, Type type);

    HappinessFactor getFactor() const;

    virtual void nextTurn();

private:
    HappinessFactor mFactor;
    int mArea;
};
