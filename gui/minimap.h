#pragma once

#include <QWidget>
#include <QPixmap>

#include "../core/sites/building.h"

class District;
class QPushButton;

class DistrictMinimap : public QWidget
{
    Q_OBJECT
public:
    using MinimapItem = QPushButton*;
    using MinimapRow = std::vector<MinimapItem>;
    using Minimap = std::vector<MinimapRow>;

    using BuildingTypeToImageMap = std::map<std::string, QPixmap>;

    DistrictMinimap(District* district, QWidget *parent = 0);

private:
    void setupLayout();
    void updateMinimapPictures();

    void initializeTypeToPictureMap();
    QPixmap getPictureByBuildingType(const std::string& type) const;

    size_t mMapSize;
    Minimap mMinimap;
    BuildingTypeToImageMap mTypeMap;

private:
    District* mDistrict;
};
