#pragma once

#include <string>
#include <map>

#include "building.h"

class Site
{
public:
    using Address = std::pair<int, int>;

    Site(int posX, int posY);

    Address getAddress() const;

    bool isOccupied() const;
    Building* getBuilding() const;

    bool constructBuilding(Building::Type type);

    void nextTurn();

    HappinessFactor getPollution() const;

private:
    Address mAddress;

    Building* mBuilding;

    HappinessFactor mPollution;
};
