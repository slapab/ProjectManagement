#ifndef PROJECTINTERFACE_H
#define PROJECTINTERFACE_H

#include <utility> //std::pair
#include <QDate>
#include <QString>
#include <vector>

#include "TimeInterval.h"

class ProjectItemInterface
{
public:
    using TimeIntervalsContainerType = std::vector<std::unique_ptr<TimeInterval>>;

    ProjectItemInterface() = default;
    virtual ~ProjectItemInterface() {}

    virtual void setBeginDate(QDate beginDate) = 0;
    virtual void setEndDate(QDate endDate) = 0;
    virtual void setDescription(QString descr) = 0;
    virtual void setName(QString name) = 0;

    virtual std::pair<QDate, QDate> getDates() const = 0;
    virtual QString getDescription() const = 0;
    virtual QString getName() const = 0;
    virtual int     getID() const = 0;

    virtual void setTimeIntervalsContainer(TimeIntervalsContainerType && container) = 0;
    virtual void addTimeInterval(std::unique_ptr<TimeInterval> item) = 0;
    virtual void removeTimeInterval(int id) = 0;
    virtual const TimeIntervalsContainerType & getTimeIntervalsContainer() const = 0;
};

#endif // PROJECTINTERFACE_H
