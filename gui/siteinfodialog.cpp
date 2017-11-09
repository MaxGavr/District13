#include "siteinfodialog.h"
#include "../core/sites/house.h"
#include "../core/sites/site.h"
#include "minimap.h"
#include "builddialog.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>

SiteInfoDialog::SiteInfoDialog(QWidget* parent)
    : QFrame(parent),
      mSite(nullptr),
      mPopulationInfo(nullptr),
      mBuildingInfo(nullptr),
      mSiteInfo(nullptr)
{   
    //mOkButton = new QPushButton(tr("Ок"));
    //mOkButton->setDefault(true);
    //connect(mOkButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

Site* SiteInfoDialog::getSite() const
{
    return mSite;
}

void SiteInfoDialog::showSiteInfo(Site* site)
{
    if (!site)
        return;

    show();

    mSite = site;

    Building::Type type = mSite->isOccupied() ? mSite->getBuilding()->getType() : Building::Type::NONE;
    setWindowTitle(DistrictMinimap::getBuildingTitle(type));

    fillSiteInfo();
    fillBuildingInfo();
    fillPopulationInfo();

    setupLayout();
}

void SiteInfoDialog::fillPopulationInfo()
{
    if (mPopulationInfo)
    {
        delete mPopulationInfo;
        mPopulationInfo = nullptr;
    }

    Building* building = mSite->getBuilding();
    if (!building || !building->isHouse())
        return;

    House* house = dynamic_cast<House*>(building);

    mPopulationInfo = new QGroupBox(tr("Жители"));
    QVBoxLayout* layout = new QVBoxLayout();

    auto happinessLabel = new QLabel();
    happinessLabel->setText(tr("Уровень счастья: ") + QString::number(house->getHappiness()));
    layout->addWidget(happinessLabel);

    mPopulationInfo->setLayout(layout);
}

void SiteInfoDialog::fillBuildingInfo()
{
    if (mBuildingInfo)
    {
        delete mBuildingInfo;
        mBuildingInfo = nullptr;
    }

    mBuildingInfo = new QGroupBox(tr("Здание"));

    QVBoxLayout* layout = new QVBoxLayout();

    Building* building = mSite->getBuilding();

    QLabel* buildingInfo = new QLabel();
    if (mSite->isPendingConstruction())
    {
        buildingInfo->setText(tr("На участке ведется строительство"));
    }
    else if (!building)
    {
        buildingInfo->setText(tr("На этом участке нет здания"));
    }
    else
    {
        const HappinessFactor condition = building->getCondition();
        buildingInfo->setText(
                    tr("Состояние: ") +
                    QString::number(condition.getValue()) +
                    QString("/") +
                    QString::number(condition.getMaxValue()));
    }

    layout->addWidget(buildingInfo);
    mBuildingInfo->setLayout(layout);
}

void SiteInfoDialog::fillSiteInfo()
{
    if (mSiteInfo)
    {
        delete mSiteInfo;
        mSiteInfo = nullptr;
    }

    mSiteInfo = new QGroupBox(tr("Территория"));

    QVBoxLayout* layout = new QVBoxLayout();

    const HappinessFactor pollution = mSite->getCleanliness();
    auto pollutionLabel = new QLabel();
    pollutionLabel->setText(
                tr("Чистота: ") +
                QString::number(pollution.getValue()) +
                QString("/") +
                QString::number(pollution.getMaxValue()));

    layout->addWidget(pollutionLabel);
    mSiteInfo->setLayout(layout);
}

void SiteInfoDialog::setupLayout()
{
    if (layout())
        delete layout();

    auto buttonsLayout = new QHBoxLayout();
    //buttonsLayout->addWidget(mOkButton, 0, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout();
    if (mPopulationInfo)
        mainLayout->addWidget(mPopulationInfo);
    if (mBuildingInfo)
        mainLayout->addWidget(mBuildingInfo);
    if (mSiteInfo)
        mainLayout->addWidget(mSiteInfo);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}
