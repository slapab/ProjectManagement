#ifndef DATASTORAGEACCESSINTERFACE_H
#define DATASTORAGEACCESSINTERFACE_H

#include <vector>
#include <memory>   // std::unique_ptr

#include "ProjectItemInterface.h"
#include "TaskItemInterface.h"
#include "TimeIntervalInterface.h"

#include <QString>

class DataStorageAccessInterface
{
public:
    DataStorageAccessInterface() = default;
    DataStorageAccessInterface(const DataStorageAccessInterface &) = default;
    DataStorageAccessInterface & operator=(const DataStorageAccessInterface &) = default;

    DataStorageAccessInterface(DataStorageAccessInterface &&) = default;
    DataStorageAccessInterface & operator=(DataStorageAccessInterface &&) = default;

    virtual ~DataStorageAccessInterface() = default;


    using project_ptr_type = std::unique_ptr<ProjectItemInterface>;
    using task_ptr_type    = std::unique_ptr<TaskItemInterface>;
    using timeint_ptr_type = std::unique_ptr<TimeIntervalInterface>;

    using ProjectsContainerType = std::vector<project_ptr_type>;
    using TasksContainerType = std::vector<task_ptr_type>;
    using TimeIntContainerType = std::vector<timeint_ptr_type>;

    virtual void open() = 0;
    virtual void close() = 0;

    virtual ProjectsContainerType getAllProjects() = 0;
    virtual TasksContainerType getTasks(const timeint_ptr_type & timeInterval) = 0;
    virtual TimeIntContainerType getTimeIntervals(const project_ptr_type & proj) = 0;

    virtual void upadteProject(const project_ptr_type & proj) = 0;
    virtual void updateTaskItem(const task_ptr_type & task) = 0;
    virtual void updateTimeInterval(const timeint_ptr_type & timeInterval) = 0;

    virtual project_ptr_type addProject(QString name, QString descr, QDateTime beginDate, QDateTime endDate) = 0;
    virtual task_ptr_type addTaskItem(
            int intervalID, int priority,
            int state, QString name,
            QString descr, QDateTime beginDate, QDateTime endDate) = 0;

    virtual timeint_ptr_type addTimeInterval(int projectID, QString name, QString description, QDateTime beginDate, QDateTime endDate) = 0;

    virtual void removeProjectItem(const project_ptr_type & proj) = 0;
    virtual void removeTaskItem(const task_ptr_type & task) = 0;
    virtual void removeTimeInterval(const timeint_ptr_type & timeInterval) = 0;
};

#endif // DATASTORAGEACCESSINTERFACE_H
