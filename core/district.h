#pragma once

#include <vector>

class Site;

class District
{
public:
    using DistrictMap = std::vector< std::vector<Site*> >;

    District(std::size_t districtSize);

private:
    std::size_t mSize;

    DistrictMap mMap;
};
