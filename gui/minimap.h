#pragma once

#include <QFrame>
#include <QPixmap>
#include <QPushButton>

#include "../core/sites/building.h"

class District;
class DistrictMinimapItem;
class Site;
class Event;


class DistrictMinimap : public QFrame
{
    Q_OBJECT
public:
    using MinimapRow = std::vector<DistrictMinimapItem*>;
    using Minimap = std::vector<MinimapRow>;

    using BuildingTypeToImageMap = std::map<Building::Type, QString>;
    using BuildingTypeToTitleMap = std::map<Building::Type, QString>;

    DistrictMinimap(District* district, QWidget *parent = 0);

    static QPixmap getBuildingImage(Building::Type type);
    static QPixmap getBuildingImage(const Building* building);
    static QString getBuildingTitle(Building::Type type);

    void updateMinimap();
    void highlightArea(int centerX, int centerY, int area, bool on = true);

signals:
    void buildEvent(Event* event);

public slots:
    void onSiteInfoShow();
    void onBuild(Building::Type type);

private:
    void setupLayout();

    static const BuildingTypeToImageMap mImageMap;
    static const BuildingTypeToTitleMap mTitleMap;

    size_t mMapSize;
    Minimap mMinimap;

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

    void highlight(bool on = true);

private:
    DistrictMinimap* mMinimap;
    Site* mSite;
};
