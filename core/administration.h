#pragma once

class District;

class Administration
{
public:
    Administration(District* district);

    District* getDistrict() const;

    void nextTurn();

private:
    District* mDistrict;
};
