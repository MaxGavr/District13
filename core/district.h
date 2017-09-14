#pragma once

#include <vector>

class Site;

class District
{
public:
    using SiteRow = std::vector<Site*>;
    using DistrictMap = std::vector<SiteRow>;

    District(std::size_t districtSize, float populatedPart = 0.5);
    ~District();

private:
    void generateDistrictMap();

    std::size_t mSize;
    float mPopulatedPart;

    DistrictMap mMap;
};
