#ifndef TIMEINTERVALINTERFACE_H
#define TIMEINTERVALINTERFACE_H

#include <QDateTime>
#include <QString>
#include <utility> //std::pair
#include <memory>  //std::memory

#include "TaskItemInterface.h"

class TimeIntervalInterface
{
public:
    using timeint_ptr_type = std::unique_ptr<TimeIntervalInterface>;
    using TimeIntervalsContainerType = std::vector<timeint_ptr_type>;

    using task_ptr_type = std::unique_ptr<TaskItemInterface>;
    using TasksContainerType = std::vector<task_ptr_type>;

    TimeIntervalInterface() = default;
    virtual ~TimeIntervalInterface() {}

    virtual void setBeginDate(QDateTime begin) = 0;
    virtual void setEndDate(QDateTime end) = 0;
    virtual void setName(QString name) = 0;
    virtual void setDescription(QString description) = 0;

    virtual std::pair<QDateTime, QDateTime> getDates() const = 0;
    virtual QString getName() const = 0;
    virtual QString getDescription() const = 0;
    virtual int  getProjectID() const = 0;
    virtual int  getID() const = 0;

    virtual void setTasksContainer(TasksContainerType && container) = 0;
    virtual void addTask(task_ptr_type item) = 0;
    virtual void removeTask(int id) = 0;
    virtual const TasksContainerType & getTasksContainer() const = 0;
};

#endif // TIMEINTERVALINTERFACE_H
