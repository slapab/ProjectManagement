#ifndef PROJECTINTERFACE_H
#define PROJECTINTERFACE_H

#include <utility> //std::pair
#include <QDateTime>
#include <QString>
#include <vector>

#include "TimeIntervalInterface.h"
#include "ItemInterface.h"

class ProjectItemInterface : public ItemInterface
{
public:
    using project_ptr_type = std::unique_ptr<ProjectItemInterface>;
    using TimeIntervalsContainerType = TimeIntervalInterface::TimeIntervalsContainerType;
    using timeint_ptr_type = TimeIntervalInterface::timeint_ptr_type;

    ProjectItemInterface() = default;
    virtual ~ProjectItemInterface() {}

    virtual void setTimeIntervalsContainer(TimeIntervalsContainerType && container) = 0;
    virtual void addTimeInterval(timeint_ptr_type item) = 0;
    virtual void removeTimeInterval(int id) = 0;
    virtual const TimeIntervalsContainerType & getTimeIntervalsContainer() const = 0;
};

#endif // PROJECTINTERFACE_H
