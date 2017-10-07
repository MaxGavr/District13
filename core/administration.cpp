#include "administration.h"
#include "district.h"

Administration::Administration(District* district)
    : mDistrict(district)
{

}

District* Administration::getDistrict() const
{
    return mDistrict;
}

void Administration::nextTurn()
{

}

