#include "minimap.h"
#include "siteinfodialog.h"

#include "../core/administration.h"
#include "../core/district.h"
#include "../core/sites/site.h"
#include "../core/sites/house.h"
#include "../core/events/event.h"

#include <QIcon>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

using namespace std;

const DistrictMinimap::BuildingTypeToImageMap DistrictMinimap::mImageMap = {
    { Building::Type::NONE, ":/res/icons/empty" },
    { Building::Type::HOUSE, ":/res/icons/house" },
    { Building::Type::SHOP, ":/res/icons/shop" },
    { Building::Type::SCHOOL, ":/res/icons/school" },
    { Building::Type::PARK, ":/res/icons/park" }
};

const DistrictMinimap::BuildingTypeToTitleMap DistrictMinimap::mTitleMap = {
    { Building::Type::NONE, tr("Пустырь") },
    { Building::Type::HOUSE, tr("Жилой дом") },
    { Building::Type::SHOP, tr("Магазин") },
    { Building::Type::SCHOOL, tr("Школа") },
    { Building::Type::PARK, tr("Парк") }
};

DistrictMinimap::DistrictMinimap(District* district, QWidget *parent)
    : QFrame(parent),
      mDistrict(district)

{
    Q_ASSERT(mDistrict);
    mMapSize = mDistrict->getSize();

    mMinimap = Minimap(mMapSize, MinimapRow(mMapSize, nullptr));

    setupLayout();
}

void DistrictMinimap::onSiteInfoShow()
{
    DistrictMinimapItem* mapItem = qobject_cast<DistrictMinimapItem*>(QObject::sender());
    Site* site = mapItem->getSite();

    SiteInfoDialog dialog(site, this);
    connect(&dialog, SIGNAL(buildEvent(Building::Type)), this, SLOT(onBuild(Building::Type)));

    Building* building = site->getBuilding();
    if (building && building->affectsNeighbours())
    {
        Site::Address addr = site->getAddress();
        int area = building->getInfluenceArea();
        highlightArea(addr.first, addr.second, area, true);

        dialog.exec();

        highlightArea(addr.first, addr.second, area, false);
    }
    else
        dialog.exec();
}

void DistrictMinimap::onBuild(Building::Type type)
{   
    const Site* site = qobject_cast<SiteInfoDialog*>(QObject::sender())->getSite();

    const Site::Address address = site->getAddress();
    Event* event = mDistrict->getAdministration()->constructBuilding(address.first, address.second, type);

    buildEvent(event);
}

void DistrictMinimap::setupLayout()
{
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetMaximumSize);

    QLabel* indexLabel;
    for (size_t i = 0; i < mMapSize; ++i)
    {
        indexLabel = new QLabel(QString::number(i));
        indexLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(indexLabel, i + 1, 0, 1, 1);

        indexLabel = new QLabel(QString::number(i));
        indexLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(indexLabel, 0, i + 1, 1, 1);
    }

    for (size_t i = 0; i < mMapSize; ++i)
    {
        for (size_t j = 0; j < mMapSize; ++j)
        {
            mMinimap.at(i).at(j) = new DistrictMinimapItem(mDistrict->getSiteAt(i, j), this);
            layout->addWidget(mMinimap.at(i).at(j), i + 1, j + 1, 1, 1);
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

void DistrictMinimap::highlightArea(int centerX, int centerY, int area, bool on)
{
    for (int i = centerX - area; i <= centerX + area; ++i)
        for (int j = centerY - area; j <= centerY + area; ++j)
        {
            if (i == centerX && j == centerY)
                continue;
            try
            {
                mMinimap.at(i).at(j)->highlight(on);
            }
            catch (std::out_of_range o)
            {
                continue;
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

void DistrictMinimapItem::highlight(bool on)
{
    if (on)
        setStyleSheet("border: 0px solid black; background-color: #A9F16C;");
    else
        setStyleSheet("");
}
