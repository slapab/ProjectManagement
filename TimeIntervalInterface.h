#ifndef TIMEINTERVALINTERFACE_H
#define TIMEINTERVALINTERFACE_H

#include <QDateTime>
#include <QString>
#include <utility> //std::pair
#include <memory>  //std::memory

#include "TaskItemInterface.h"

#include "ItemInterface.h"

class TimeIntervalInterface : public ItemInterface
{
public:
    using timeint_ptr_type = std::unique_ptr<TimeIntervalInterface>;
    using TimeIntervalsContainerType = std::vector<timeint_ptr_type>;

    using task_ptr_type = std::unique_ptr<TaskItemInterface>;
    using TasksContainerType = std::vector<task_ptr_type>;

    TimeIntervalInterface() = default;
    virtual ~TimeIntervalInterface() {}

    virtual int  getProjectID() const = 0;

    virtual void setTasksContainer(TasksContainerType && container) = 0;
    virtual void addTask(task_ptr_type item) = 0;
    virtual void removeTask(int id) = 0;
    virtual const TasksContainerType & getTasksContainer() const = 0;
};

#endif // TIMEINTERVALINTERFACE_H
