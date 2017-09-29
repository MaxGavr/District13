#pragma once

#include <string>


class Building
{
public:
    enum class Type {
        NONE = 0,
        HOUSE
    };

    Building(Building::Type type, const std::string& name, bool populated = false);

    Building::Type getType() const;
    std::string getName() const;
    bool isPopulated() const;

private:
    Building::Type mType;
    std::string mName;

    bool mIsPopulated;
};
