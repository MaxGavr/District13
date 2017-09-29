#pragma once

#include <vector>

class Site;
class Building;

class District
{
public:
    using SiteRow = std::vector<Site*>;
    using DistrictMap = std::vector<SiteRow>;

    District(std::size_t districtSize, float populatedPart = 0.5);
    ~District();

    std::size_t getSize() const;

    Site* getSiteAt(std::size_t x, std::size_t y) const;
    Building* getBuildingAt(std::size_t x, std::size_t y) const;

private:
    void generateDistrictMap();

    std::size_t mSize;
    float mPopulatedPart;

    DistrictMap mMap;
};
