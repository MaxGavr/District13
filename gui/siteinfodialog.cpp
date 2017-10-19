#include "siteinfodialog.h"
#include "../core/sites/house.h"
#include "../core/sites/site.h"
#include "minimap.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>

SiteInfoDialog::SiteInfoDialog(Site* site, QWidget* parent)
    : QDialog(parent),
      mSite(site),
      mPopulationInfo(nullptr),
      mBuildingInfo(nullptr),
      mSiteInfo(nullptr)
{   
    Building::Type type = site->getBuilding() ? site->getBuilding()->getType() : Building::Type::NONE;
    setWindowTitle(DistrictMinimap::getBuildingTitle(type));

    fillSiteInfo();
    fillBuildingInfo();
    fillPopulationInfo();

    auto mainLayout = new QVBoxLayout();
    if (mPopulationInfo)
        mainLayout->addWidget(mPopulationInfo);
    mainLayout->addWidget(mBuildingInfo);
    mainLayout->addWidget(mSiteInfo);

    mOkButton = new QPushButton(tr("Ок"));
    mOkButton->setDefault(true);
    connect(mOkButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    mainLayout->addWidget(mOkButton, 0, Qt::AlignRight);
    setLayout(mainLayout);
}

void SiteInfoDialog::fillPopulationInfo()
{
    Building* building = mSite->getBuilding();
    if (!building || building->getType() != Building::Type::HOUSE)
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
    mBuildingInfo = new QGroupBox(tr("Здание"));

    QVBoxLayout* layout = new QVBoxLayout();

    Building* building = mSite->getBuilding();
    if (!building)
    {
        auto noBuildingLabel = new QLabel(tr("На этом участке нет здания"));
        layout->addWidget(noBuildingLabel);
    }
    else
    {
        const HappinessFactor condition = building->getCondition();
        auto conditionLabel = new QLabel();
        conditionLabel->setText(
                    tr("Состояние:") +
                    QString::number(condition.getValue()) +
                    QString("/") +
                    QString::number(condition.getMaxValue()));
        layout->addWidget(conditionLabel);
    }

    mBuildingInfo->setLayout(layout);
}

void SiteInfoDialog::fillSiteInfo()
{
    mSiteInfo = new QGroupBox(tr("Территория"));

    QVBoxLayout* layout = new QVBoxLayout();

    const HappinessFactor pollution = mSite->getPollution();
    auto pollutionLabel = new QLabel();
    pollutionLabel->setText(
                tr("Загрязнение: ") +
                QString::number(pollution.getValue()) +
                QString("/") +
                QString::number(pollution.getMaxValue()));

    layout->addWidget(pollutionLabel);
    mSiteInfo->setLayout(layout);
}

