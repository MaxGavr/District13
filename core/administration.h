#pragma once

class District;

class Administration
{
public:
    Administration(District* district);

    District* getDistrict() const;

private:
    District* mDistrict;
};
