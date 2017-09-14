#pragma once

class District;

class Administration
{
public:
    Administration(District* district);

private:
    District* mDistrict;
};
