#pragma once

#include "building.h"

class PublicBuilding : public Building
{
public:
    enum class Type {
        SHOP,
        SCHOOL,
        PARK,
        FACTORY
    };

    static Building::Type getBuildingType(PublicBuilding::Type type);

    PublicBuilding(Site* site, Type type);

    HappinessFactor getFactor() const;

    virtual void nextTurn();

protected:
    HappinessFactor mFactor;

private:
    int chooseInfluenceArea(PublicBuilding::Type type) const;
};
