#pragma once

class HappinessFactor
{
public:
    HappinessFactor(int minValue = 0,
                    int maxValue = 100,
                    int step = 1,
                    int baseValue = 50,
                    int happinessImpact = 20);

    HappinessFactor& operator++();
    HappinessFactor& operator++(int);

    HappinessFactor& operator--();
    HappinessFactor& operator--(int);

    int getValue() const;
    void setValue(int value);

    int getHappinessImpact() const;

private:
    int mValue;

    const int mStep;
    const int mMaxValue;
    const int mMinValue;

    const int mBaseValue;
    const int mMaxHappinessImpact;
};
