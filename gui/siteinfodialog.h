# pragma once

#include <QDialog>

class Site;
class QLabel;
class QPushButton;
class QGroupBox;

class SiteInfoDialog : public QDialog
{
    Q_OBJECT
public:
    SiteInfoDialog(Site* site, QWidget* parent = 0);

private:
    void fillPopulationInfo();
    void fillBuildingInfo();
    void fillSiteInfo();

    Site* mSite;

    QLabel* mHappinessLabel;
    QPushButton* mOkButton;

    QGroupBox* mPopulationInfo;
    QGroupBox* mBuildingInfo;
    QGroupBox* mSiteInfo;
};
