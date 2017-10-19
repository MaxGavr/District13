#include "factor.h"


HappinessFactor::HappinessFactor(int minValue, int maxValue, int step, int baseValue, int happinessImpact)
    : mValue(minValue),
      mStep(step),
      mMaxValue(maxValue),
      mMinValue(minValue),
      mBaseValue(baseValue),
      mMaxHappinessImpact(happinessImpact)
{

}

HappinessFactor& HappinessFactor::operator++()
{
    mValue += mStep;
    if (mValue > mMaxValue)
        mValue = mMaxValue;
    return *this;
}

HappinessFactor& HappinessFactor::operator++(int)
{
    return ++(*this);
}

HappinessFactor& HappinessFactor::operator--()
{
    mValue -= mStep;
    if (mValue < mMinValue)
        mValue = mMinValue;
    return *this;
}

HappinessFactor& HappinessFactor::operator--(int)
{
    return --(*this);
}

int HappinessFactor::getValue() const
{
    return mValue;
}

void HappinessFactor::setValue(int value)
{
    if (value > mMaxValue)
        mValue = mMaxValue;
    else if (value > mMinValue)
        mValue = mMinValue;
    else
        mValue = value;
}

int HappinessFactor::getMaxValue() const
{
    return mMaxValue;
}

int HappinessFactor::getHappinessImpact() const
{
    const int difference = mValue - mBaseValue;
    const int maxDifference = difference < 0 ? mBaseValue - mMinValue : mMaxValue - mBaseValue;

    const int happinessImpact = (difference / maxDifference) * mMaxHappinessImpact;
    return happinessImpact;
}
