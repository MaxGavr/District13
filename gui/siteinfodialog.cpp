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

SiteInfoDialog::SiteInfoDialog(Site* site, QWidget* parent)
    : QDialog(parent),
      mSite(site),
      mPopulationInfo(nullptr),
      mBuildingInfo(nullptr),
      mSiteInfo(nullptr)
{   
    Building::Type type = site->isOccupied() ? site->getBuilding()->getType() : Building::Type::NONE;
    setWindowTitle(DistrictMinimap::getBuildingTitle(type));

    fillSiteInfo();
    fillBuildingInfo();
    fillPopulationInfo();



    auto buttonsLayout = new QHBoxLayout();

    mOkButton = new QPushButton(tr("Ок"));
    mOkButton->setDefault(true);
    connect(mOkButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    if (!mSite->isOccupied())
    {
        mBuildButton = new QPushButton(tr("Построить"));
        connect(mBuildButton, SIGNAL(clicked(bool)), this, SLOT(onShowBuildDialog()));
        buttonsLayout->addWidget(mBuildButton, 0, Qt::AlignLeft);
    }
    buttonsLayout->addWidget(mOkButton, 0, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout();
    if (mPopulationInfo)
        mainLayout->addWidget(mPopulationInfo);
    mainLayout->addWidget(mBuildingInfo);
    mainLayout->addWidget(mSiteInfo);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}

Site* SiteInfoDialog::getSite() const
{
    return mSite;
}

void SiteInfoDialog::onShowBuildDialog()
{
    if (mSite->isPendingConstruction())
    {
        QMessageBox::information(this,
                                 tr("Строительство"),
                                 tr("Строительство уже началось"));
        return;
    }

    BuildDialog dialog(mSite);
    if (dialog.exec() == QDialog::Accepted)
        buildEvent(dialog.getChosenType());
}

void SiteInfoDialog::fillPopulationInfo()
{
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
                    tr("Состояние:") +
                    QString::number(condition.getValue()) +
                    QString("/") +
                    QString::number(condition.getMaxValue()));
    }

    layout->addWidget(buildingInfo);
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
