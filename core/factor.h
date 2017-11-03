#pragma once

class HappinessFactor
{
public:
    HappinessFactor(int minValue = 0,
                    int maxValue = 100,
                    int step = 1,
                    int baseValue = 50,
                    int happinessImpact = 20);
    HappinessFactor(const HappinessFactor& factor);

    HappinessFactor& operator++();
    HappinessFactor& operator++(int);

    HappinessFactor& operator--();
    HappinessFactor& operator--(int);

    int getValue() const;
    void setValue(int value);

    int getStep() const;
    void setStep(int step);

    int getMaxValue() const;

    int getHappinessImpact() const;

private:
    int mValue;

    int mStep;
    int mMaxValue;
    int mMinValue;

    int mBaseValue;
    int mMaxHappinessImpact;
};
