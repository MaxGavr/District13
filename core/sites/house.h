#pragma once

#include "building.h"
#include <vector>
#include <list>

class PublicBuilding;

class House : public Building
{
public:
    House(Site* site);

    inline int getMinHappiness() const { return 0; }
    inline int getMaxHappiness() const { return 100; }
    inline int getBaseHappiness() const { return 50; }

    int getHappiness() const;

    std::vector<HappinessFactor> getFactors() const;
    void calculateHappiness();

    void addNeighbour(Building* neighbour);
    virtual void removeNeighbour(Building* neighbour);

    void nextTurn();

private:
    std::list<PublicBuilding*> mNearestBuildings;

    int mBaseHappiness;
    int mHappiness;
};
