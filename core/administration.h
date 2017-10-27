#pragma once

#include "sites/building.h"

class District;
class ConstructionEvent;

class Administration
{
public:
    Administration(District* district);

    District* getDistrict() const;

    void nextTurn();
    ConstructionEvent* constructBuilding(std::size_t x, std::size_t y, Building::Type type);

private:
    District* mDistrict;
};
