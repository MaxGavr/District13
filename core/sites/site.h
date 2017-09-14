#pragma once

#include <string>
#include <map>

#include "building.h"

class Site
{
public:
    Site();

    bool isOccupied() const;
    Building* getBuilding() const;
    
    bool constructBuilding(Building::Type type);

private:
    Building* mBuilding;
};
