#ifndef TIMEINTERVALINTERFACE_H
#define TIMEINTERVALINTERFACE_H

#include <QDateTime>
#include <QString>
#include <utility> //std::pair
#include <memory>  //std::memory

#include "TaskItem.h"

class TimeIntervalInterface
{
public:
    using TasksContainerType = std::vector<std::unique_ptr<TaskItem>>;

    TimeIntervalInterface() = default;
    virtual ~TimeIntervalInterface() {}

    virtual void setBeginDate(QDateTime begin) = 0;
    virtual void setEndDate(QDateTime end) = 0;
    virtual void setName(QString name) = 0;
    virtual void setDescription(QString description) = 0;

    virtual std::pair<QDateTime, QDateTime> GetDates() const = 0;
    virtual QString getName() const = 0;
    virtual QString getDescription() const = 0;
    virtual int  getProjectID() const = 0;
    virtual int  getID() const = 0;

    virtual void setTasksContainer(TasksContainerType && container) = 0;
    virtual void addTask(std::unique_ptr<TaskItem> item) = 0;
    virtual void removeTask(int id) = 0;
    virtual const TasksContainerType & getTasksContainer() const = 0;
};

#endif // TIMEINTERVALINTERFACE_H
