#pragma once

#include <vector>
#include "sites/building.h"

class Site;
class Building;
class ConstructionEvent;
class Administration;

class District
{
public:
    using SiteRow = std::vector<Site*>;
    using DistrictMap = std::vector<SiteRow>;

    District(std::size_t districtSize, float populatedPart = 0.5);
    ~District();

    std::size_t getSize() const;

    void setAdministration(Administration* admin);
    Administration* getAdministration() const;

    Site* getSiteAt(std::size_t x, std::size_t y) const;
    Building* getBuildingAt(std::size_t x, std::size_t y) const;

    void nextTurn();

private:
    void updateBuildingsInfluenceAreas();

    void generateDistrictMap();

    Administration* mAdmin;

    std::size_t mSize;
    float mPopulatedPart;

    DistrictMap mMap;
};
