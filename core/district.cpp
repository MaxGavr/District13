#include "district.h"
#include "sites/site.h"

using namespace std;

District::District(size_t districtSize)
    : mSize(districtSize)
{
    mMap = DistrictMap(mSize, vector<Site*>(mSize, nullptr));
}

