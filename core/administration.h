#pragma once

//#include "sites/building.h"
#include "sites/site.h"

class District;
class ConstructionEvent;
class RepairingEvent;
class CleaningEvent;

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
    ConstructionEvent* constructBuilding(Site::Address address, Building::Type type);
    RepairingEvent* repairBuilding(Site::Address address);
    CleaningEvent* cleanSite(Site::Address address);

private:
    District* mDistrict;

    int mMoney;
    const int mMaxIncome;
};
