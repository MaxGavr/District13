#include "eventlogger.h"
#include "minimap.h"
#include "../core/sites/site.h"

EventLogger::EventLogger()
{

}

EventLogger::EventSummary EventLogger::getEventLog(const Event& event) const
{
    switch (event.getType())
    {
    case Event::Type::Undefined:
        return EventSummary();

    case Event::Type::Construction:
        return logConstructionEvent(dynamic_cast<const ConstructionEvent&>(event));

    default:
        return EventSummary();
    }
}

EventLogger::EventSummary EventLogger::logConstructionEvent(const ConstructionEvent& event) const
{
    EventSummary summary;

    Site* site = event.getSite();
    Site::Address address = site->getAddress();

    QString title = DistrictMinimap::getBuildingTitle(event.getBuildingType());
    summary.append(
                tr("На участке ") +
                QString::number(address.first) +
                "-" +
                QString::number(address.second) +
                tr("завершилось строительство ") +
                title);
    return summary;
}

