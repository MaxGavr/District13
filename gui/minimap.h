#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPushButton>

#include "../core/sites/building.h"

class District;
class DistrictMinimapItem;
class Site;


class DistrictMinimap : public QWidget
{
    Q_OBJECT
public:
    using MinimapRow = std::vector<DistrictMinimapItem*>;
    using Minimap = std::vector<MinimapRow>;

    using BuildingTypeToImageMap = std::map<std::string, QPixmap>;

    DistrictMinimap(District* district, QWidget *parent = 0);

    QPixmap getPictureByBuildingType(const std::string& type);

public slots:
    void onSiteInfoShow();

private:
    void setupLayout();
    void updateMinimapPictures();

    void initializeTypeToPictureMap();

    size_t mMapSize;
    Minimap mMinimap;
    BuildingTypeToImageMap mTypeMap;

private:
    District* mDistrict;
};



class DistrictMinimapItem : public QPushButton
{
    Q_OBJECT
public:
    DistrictMinimapItem(Site* site, DistrictMinimap* minimap);

    Site* getSite() const;
    QPixmap getPicture() const;

private:
    DistrictMinimap* mMinimap;
    Site* mSite;
};
