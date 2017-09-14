#include "district.h"
#include "sites/site.h"

using namespace std;

District::District(size_t districtSize, float populatedPart)
    : mSize(districtSize), mPopulatedPart(populatedPart)
{
    mMap = DistrictMap(mSize, SiteRow(mSize, new Site()));

    generateDistrictMap();
}

District::~District()
{
    for (SiteRow row : mMap)
        row.clear();
    mMap.clear();
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
    int neededAmount = initialSize * mPopulatedPart;

    while ((initialSize - tempVector.size()) < neededAmount)
    {
        size_t index = rand() % tempVector.size();
        tempVector[index]->constructBuilding(Building::Type::HOUSE);
        tempVector.erase(tempVector.begin() + index);
    }
}

