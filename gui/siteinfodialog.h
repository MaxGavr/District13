# pragma once

#include <QDialog>
#include "../core/sites/building.h"

class Site;
class QLabel;
class QPushButton;
class QGroupBox;

class SiteInfoDialog : public QDialog
{
    Q_OBJECT
public:
    SiteInfoDialog(Site* site, QWidget* parent = 0);

    Site* getSite() const;

signals:
    void buildEvent(Building::Type type);

private slots:
    void onShowBuildDialog();

private:
    void fillPopulationInfo();
    void fillBuildingInfo();
    void fillSiteInfo();

    Site* mSite;

    QLabel* mHappinessLabel;
    QPushButton* mOkButton;
    QPushButton* mBuildButton;

    QGroupBox* mPopulationInfo;
    QGroupBox* mBuildingInfo;
    QGroupBox* mSiteInfo;
};
