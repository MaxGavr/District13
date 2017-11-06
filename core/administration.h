#pragma once

#include "sites/building.h"

class District;
class ConstructionEvent;

class Administration
{
public:
    explicit Administration(District* district, int startMoney, int maxIncome);
    ~Administration();

    District* getDistrict() const;

    int calcAverageHappiness() const;
    int calcIncome() const;

    int getCurrentMoney() const;
    void changeMoney(int amount);

    void nextTurn();
    ConstructionEvent* constructBuilding(std::size_t x, std::size_t y, Building::Type type);

private:
    District* mDistrict;

    int mMoney;
    const int mMaxIncome;
};
