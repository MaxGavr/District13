#include "actionswidget.h"
#include "../core/administration.h"
#include "../core/sites/site.h"
#include "../core/sites/building.h"
#include "../core/events/event.h"
#include "builddialog.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

ActionsWidget::ActionsWidget(Administration* admin, QWidget* parent)
    : QFrame(parent),
      mTargetSite(nullptr),
      mAdmin(admin)
{
    mActionsGroupbox = new QGroupBox(tr("Действия"), this);

    QVBoxLayout* mGroupboxLayout = new QVBoxLayout(mActionsGroupbox);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mActionsGroupbox);
}

void ActionsWidget::chooseActions(Site* targetSite)
{
    qDeleteAll(mActions);
    mActions.clear();

    mTargetSite = targetSite;

    if (!mTargetSite)
        return;

    Building* building = mTargetSite->getBuilding();

    // build action
    if (!building && !mTargetSite->isPendingConstruction())
    {
        QPushButton* buildButton = new QPushButton(tr("Построить"));
        connect(buildButton, SIGNAL(clicked(bool)), this, SLOT(onShowBuildDialog()));

        mActions.append(buildButton);
        layout()->addWidget(buildButton);
    }

    // repair action
    if (building &&
        building->getCondition().getValue() != building->getCondition().getMaxValue() &&
        !building->isPendingRepairing())
    {
        QPushButton* repairButton = new QPushButton(tr("Ремонт"));
        connect(repairButton, SIGNAL(clicked(bool)), this, SLOT(onRepairBuilding()));

        mActions.append(repairButton);
        layout()->addWidget(repairButton);
    }

    // clean action
    if (mTargetSite->getCleanliness().getValue() != mTargetSite->getCleanliness().getMaxValue() &&
        !mTargetSite->isPendingCleaning())
    {
        QPushButton* cleanButton = new QPushButton(tr("Уборка"));
        connect(cleanButton, SIGNAL(clicked(bool)), this, SLOT(onCleanSite()));

        mActions.append(cleanButton);
        layout()->addWidget(cleanButton);
    }
}

void ActionsWidget::onShowBuildDialog()
{
    BuildDialog dialog(mTargetSite);
    if (dialog.exec() == QDialog::Accepted)
    {
        Building::Type type = dialog.getChosenType();
        if (mAdmin->getCurrentMoney() < Building::getBuildCost(type))
        {
            QMessageBox::warning(this,
                                 tr("Строительство"),
                                 tr("Не хвататет средств!"));
            return;
        }

        initEvent(mAdmin->constructBuilding(mTargetSite->getAddress(), dialog.getChosenType()));

        chooseActions(mTargetSite);
    }
}

void ActionsWidget::onRepairBuilding()
{
    initEvent(mAdmin->repairBuilding(mTargetSite->getAddress()));
    chooseActions(mTargetSite);
}

void ActionsWidget::onCleanSite()
{
    initEvent(mAdmin->cleanSite(mTargetSite->getAddress()));
    chooseActions(mTargetSite);
}
