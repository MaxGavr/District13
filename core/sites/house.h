#pragma once

#include "building.h"
#include <vector>

class House : public Building
{
public:
    House(Site* site);

    inline int getMinHappiness() const { return 0; }
    inline int getMaxHappiness() const { return 100; }
    inline int getBaseHappiness() const { return 50; }

    std::vector<HappinessFactor> getFactors() const;
    void calculateHappiness();

    void nextTurn();

private:
    int mBaseHappiness;
    int mHappiness;
};
