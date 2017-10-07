#include "factor.h"


HappinessFactor::HappinessFactor(int minValue,int maxValue, int step, int baseValue, int hapinessImpact)
    : mValue(minValue),
      mStep(step),
      mMaxValue(maxValue),
      mMinValue(minValue),
      mBaseValue(baseValue),
      mMaxHappinessImpact(hapinessImpact)
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

int HappinessFactor::getHappinessImpact() const
{
    int difference = mValue - mBaseValue;
    int maxDifference = difference < 0 ? mBaseValue - mMinValue : mMaxValue - mBaseValue;

    int happinessImpact = (difference / maxDifference) * mMaxHappinessImpact;
    return happinessImpact;
}
