#pragma once

#include "../core/events/event.h"

#include <QObject>
#include <QStringList>

// TODO: do not inherit from QObject
class EventLogger : public QObject
{
    Q_OBJECT
public:
    using EventSummary = QStringList;

    EventLogger();

    EventSummary getEventLog(const Event& event) const;

private:
    EventSummary logConstructionEvent(const ConstructionEvent& event) const;
};
