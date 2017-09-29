#include "district.h"
#include "sites/site.h"

using namespace std;

District::District(size_t districtSize, float populatedPart)
    : mSize(districtSize), mPopulatedPart(populatedPart)
{
    mMap = DistrictMap(mSize, SiteRow(mSize, nullptr));
    for (SiteRow& row : mMap)
        for (Site*& site : row)
            site = new Site();

    generateDistrictMap();
}

District::~District()
{
    for (SiteRow row : mMap)
        row.clear();
    mMap.clear();
}

size_t District::getSize() const
{
    return mSize;
}

Site* District::getSiteAt(size_t x, size_t y) const
{
    return mMap.at(x).at(y);
}

Building* District::getBuildingAt(size_t x, size_t y) const
{
    return getSiteAt(x, y)->getBuilding();
}

void District::generateDistrictMap()
{
    if (mPopulatedPart < 0)
        return;
    if (mPopulatedPart > 1)
        mPopulatedPart = 1;

    SiteRow tempVector;
    for (const SiteRow& siteRow : mMap)
        tempVector.insert(tempVector.end(), siteRow.begin(), siteRow.end());

    size_t initialSize = tempVector.size();
    int populatedNeeded = initialSize * mPopulatedPart;

    while ((initialSize - tempVector.size()) < populatedNeeded)
    {
        size_t index = rand() % tempVector.size();
        tempVector[index]->constructBuilding(Building::Type::HOUSE);
        tempVector.erase(tempVector.begin() + index);
    }
}

