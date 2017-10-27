#pragma once

#include <QDialog>
#include <QMap>
#include "../core/sites/building.h"

class BuildDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BuildDialog(Site* site);

    Building::Type getChosenType() const;

public slots:
    void onChooseBuilding();

private:
    Building::Type mChosenType;

    QMap<QPushButton*, Building::Type> mBuildButtons;
};
