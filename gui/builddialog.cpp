#include "builddialog.h"
#include "minimap.h"

#include <QPushButton>
#include <QVBoxLayout>

BuildDialog::BuildDialog(Site* site)
    : mChosenType(Building::Type::NONE)
{
    setWindowTitle(tr("Построить"));

    const Building::TypeList types = Building::getAllTypes();

    auto layout = new QVBoxLayout();

    for (const Building::Type type : types)
    {
        // TODO: remove if
        if (type != Building::Type::NONE && type != Building::Type::HOUSE)
        {
            auto buildButton = new QPushButton();
            buildButton->setIcon(DistrictMinimap::getBuildingImage(type));
            buildButton->setIconSize(QSize(40, 40));
            buildButton->setText(DistrictMinimap::getBuildingTitle(type));

            connect(buildButton, SIGNAL(clicked()), this, SLOT(onChooseBuilding()));

            layout->addWidget(buildButton);
            mBuildButtons.insert(buildButton, type);
        }
    }

    auto cancelButton = new QPushButton(tr("Назад"));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));

    layout->addWidget(cancelButton, 0, Qt::AlignRight);
    setLayout(layout);
}

void BuildDialog::onChooseBuilding()
{
    QPushButton* pushedButton = qobject_cast<QPushButton*>(QObject::sender());
    mChosenType = mBuildButtons[pushedButton];
    accept();
}

Building::Type BuildDialog::getChosenType() const
{
    return mChosenType;
}
