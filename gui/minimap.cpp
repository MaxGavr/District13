#include "minimap.h"
#include "siteinfodialog.h"
#include "../core/district.h"
#include "../core/sites/site.h"
#include "../core/sites/house.h"

#include <QIcon>
#include <QPushButton>
#include <QGridLayout>

using namespace std;

const DistrictMinimap::BuildingTypeToImageMap DistrictMinimap::mImageMap = {
    { Building::Type::NONE, ":/res/icons/empty" },
    { Building::Type::HOUSE, ":/res/icons/house" },
    { Building::Type::SHOP, ":/res/icons/shop" },
    { Building::Type::SCHOOL, ":/res/icons/school" }
};

const DistrictMinimap::BuildingTypeToTitleMap DistrictMinimap::mTitleMap = {
    { Building::Type::NONE, tr("Пустырь") },
    { Building::Type::HOUSE, tr("Жилой дом") },
    { Building::Type::SHOP, tr("Магазин") },
    { Building::Type::SCHOOL, tr("Школа") }
};

DistrictMinimap::DistrictMinimap(District* district, QWidget *parent)
    : QWidget(parent),
      mDistrict(district)

{
    Q_ASSERT(mDistrict);
    mMapSize = mDistrict->getSize();

    mMinimap = Minimap(mMapSize, MinimapRow(mMapSize, nullptr));

    setupLayout();
}

void DistrictMinimap::onSiteInfoShow()
{
    DistrictMinimapItem* item = qobject_cast<DistrictMinimapItem*>(QObject::sender());
    Site* site = item->getSite();

    SiteInfoDialog dialog(site, this);
    dialog.exec();
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
            mMinimap.at(i).at(j) = new DistrictMinimapItem(mDistrict->getSiteAt(i, j), this);
            layout->addWidget(mMinimap.at(i).at(j), i, j, 1, 1);
        }
    }
}

void DistrictMinimap::updateMinimap()
{
    for (size_t i = 0; i < mMapSize; ++i)
    {
        for (size_t j = 0; j < mMapSize; ++j)
        {
            Building* building = mDistrict->getBuildingAt(i, j);
            QIcon icon = QIcon(getBuildingImage(building));
            mMinimap.at(i).at(j)->setIcon(icon);
        }
    }
}

QPixmap DistrictMinimap::getBuildingImage(Building::Type type)
{
    BuildingTypeToImageMap::const_iterator it;
    it = mImageMap.find(type);
    if (it != mImageMap.cend())
        return QPixmap(it->second);
    else
        return QPixmap(mImageMap.find(Building::Type::NONE)->second);
}

QPixmap DistrictMinimap::getBuildingImage(const Building* building)
{
    return getBuildingImage(building ? building->getType() : Building::Type::NONE);
}

QString DistrictMinimap::getBuildingTitle(Building::Type type)
{
    BuildingTypeToTitleMap::const_iterator it;
    it = mTitleMap.find(type);
    if (it != mTitleMap.cend())
        return it->second;
    else
        return QString("");
}

DistrictMinimapItem::DistrictMinimapItem(Site* site, DistrictMinimap* minimap)
    : QPushButton(minimap), mMinimap(minimap), mSite(site)
{
    const QSize pictureSize = QSize(54, 54);

    setContentsMargins(0, 0, 0, 0);
    setMinimumSize(pictureSize);
    setMaximumSize(pictureSize);
    setIconSize(pictureSize);

    setIcon(getPicture());

    setFlat(true);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    connect(this, SIGNAL(clicked()), mMinimap, SLOT(onSiteInfoShow()));
}

Site* DistrictMinimapItem::getSite() const
{
    return mSite;
}

QPixmap DistrictMinimapItem::getPicture() const
{
    using Type = Building::Type;
    const Type type = mSite->getBuilding() ? mSite->getBuilding()->getType() : Type::NONE;

    return DistrictMinimap::getBuildingImage(type);
}
