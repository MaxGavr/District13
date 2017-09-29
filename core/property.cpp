#include <stdlib.h>
#include "property.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))


Property::Property(int minValue, int maxValue, int step, int desiredValue, int hapinessDrop)
    : mValue(minValue),
      mMinValue(minValue),
      mMaxValue(maxValue),
      mStep(step),
      mDesiredValue(desiredValue),
      mMaxHappinessDrop(hapinessDrop)
{

}

Property& Property::operator++()
{
    mValue += mStep;
    if (mValue > mMaxValue)
        mValue = mMaxValue;
    return *this;
}

Property& Property::operator++(int)
{
    return ++(*this);
}

Property& Property::operator--()
{
    mValue -= mStep;
    if (mValue < mMinValue)
        mValue = mMinValue;
    return *this;
}

Property& Property::operator--(int)
{
    return --(*this);
}

int Property::getValue() const
{
    return mValue;
}

void Property::setValue(int value)
{
    if (value > mMaxValue)
        mValue = mMaxValue;
    else if (value > mMinValue)
        mValue = mMinValue;
    else
        mValue = value;
}

int Property::getHappinessDrop() const
{
    int maxDifference = MAX(abs(mMinValue - mDesiredValue), abs(mMaxValue - mDesiredValue));
    int difference = abs(mDesiredValue - mValue);

    int happinessDrop = ((double)difference / (double)maxDifference) * mMaxHappinessDrop;
    return happinessDrop;
}
