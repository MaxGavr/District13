#pragma once

#include <QFrame>

class Site;
class Administration;
class Event;

class QGroupBox;
class QPushButton;

class ActionsWidget : public QFrame
{
    Q_OBJECT
public:
    ActionsWidget(Administration* admin, QWidget* parent = 0);

    void chooseActions(Site* targetSite);

signals:
    void initEvent(Event* event);

private slots:
    void onShowBuildDialog();
    void onRepairBuilding();
    void onCleanSite();

private:
    Site* mTargetSite;
    Administration* mAdmin;

    QGroupBox* mActionsGroupbox;

//    QPushButton* mBuildButton;
//    QPushButton* mRepairButton;
//    QPushButton* mCleanButton;

    QList<QPushButton*> mActions;
};
