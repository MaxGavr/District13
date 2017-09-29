#pragma once

class Property
{
public:
    Property(int minValue = 0,
             int maxValue = 100,
             int step = 1,
             int desiredValue = 100,
             int hapinessDrop = 20);

    Property& operator++();
    Property& operator++(int);

    Property& operator--();
    Property& operator--(int);

    int getValue() const;
    void setValue(int value);

    int getHappinessDrop() const;

private:
    int mValue;

    const int mStep;
    const int mMaxValue;
    const int mMinValue;

    const int mDesiredValue;
    const int mMaxHappinessDrop;
};
