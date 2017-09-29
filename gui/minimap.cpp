#include "minimap.h"
#include "../core/district.h"

#include <QIcon>
#include <QPushButton>
#include <QGridLayout>

using namespace std;

DistrictMinimap::DistrictMinimap(District* district, QWidget *parent)
    : QWidget(parent),
      mDistrict(district)

{
    Q_ASSERT(mDistrict);
    mMapSize = mDistrict->getSize();

    initializeTypeToPictureMap();

    mMinimap = Minimap(mMapSize, MinimapRow(mMapSize, nullptr));

    setupLayout();
    updateMinimapPictures();
}

void DistrictMinimap::setupLayout()
{
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetMaximumSize);

    for (size_t i = 0; i < mMapSize; ++i)
    {
        for (size_t j = 0; j < mMapSize; ++j)
        {
            MinimapItem& item = mMinimap.at(i).at(j);

            item = new QPushButton();
            QSize pictureSize = QSize(64, 64);
            item->setContentsMargins(0, 0, 0, 0);
            item->setMinimumSize(pictureSize);
            item->setMaximumSize(pictureSize);
            item->setFlat(true);
            item->setIconSize(pictureSize);
            item->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            layout->addWidget(item, i, j, 1, 1);
        }
    }
}

void DistrictMinimap::updateMinimapPictures()
{
    for (size_t i = 0; i < mMapSize; ++i)
    {
        for (size_t j = 0; j < mMapSize; ++j)
        {
            Building* building = mDistrict->getBuildingAt(i, j);
            string type = building ? building->getName() : "";
            QPixmap sitePicture = getPictureByBuildingType(type);
            mMinimap.at(i).at(j)->setIcon(QIcon(sitePicture));
        }
    }
}

QPixmap DistrictMinimap::getPictureByBuildingType(const std::string& type) const
{
    BuildingTypeToImageMap::const_iterator it;
    it = mTypeMap.find(type);
    if (it != mTypeMap.cend())
        return it->second;
    else
        return mTypeMap.find("")->second;
}

void DistrictMinimap::initializeTypeToPictureMap()
{
    mTypeMap.clear();

    QPixmap pixmap;
    pixmap.load(":/res/icons/empty");
    mTypeMap.insert(pair<string, QPixmap>("", pixmap));
    QPixmap pix;
    pix.load(":/res/icons/house");
    mTypeMap.insert(pair<string, QPixmap>("house", pix));
}
