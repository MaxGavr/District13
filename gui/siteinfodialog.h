# pragma once

#include <QFrame>
#include "../core/sites/building.h"

class Site;
class QLabel;
class QPushButton;
class QGroupBox;

class SiteInfoDialog : public QFrame
{
    Q_OBJECT
public:
    SiteInfoDialog(QWidget* parent = 0);

    Site* getSite() const;
    void showSiteInfo(Site* site);
    void clearSiteInfo();

private:
    void fillPopulationInfo();
    void fillBuildingInfo();
    void fillSiteInfo();

    void setupLayout();

    Site* mSite;

    QLabel* mHappinessLabel;
    QPushButton* mOkButton;

    QGroupBox* mPopulationInfo;
    QGroupBox* mBuildingInfo;
    QGroupBox* mSiteInfo;
};
