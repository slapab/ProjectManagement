#ifndef DATASTORAGEACCESSINTERFACE_H
#define DATASTORAGEACCESSINTERFACE_H

#include <vector>
#include <memory>   // std::unique_ptr

#include "ProjectItem.h"
#include "TaskItem.h"
#include "TimeInterval.h"

class DataStorageAccessInterface
{
public:
    DataStorageAccessInterface() {}
    virtual ~DataStorageAccessInterface() {}

    using ProjectsContainerType = std::vector<std::unique_ptr<ProjectItem>>;
    using project_type = std::unique_ptr<ProjectItem>;
    using task_type    = std::unique_ptr<TaskItem>;
    using timeint_type = std::unique_ptr<TimeInterval>;

    virtual void open() = 0;
    virtual void close() = 0;

    virtual ProjectsContainerType getAllProjects() = 0;
    virtual task_type getTaskItem(const timeint_type & timeInterval) = 0;
    virtual timeint_type getTimeInterval(const project_type & proj) = 0;

    virtual void upadteProject(const project_type & proj) = 0;
    virtual void updateTaskItem(const task_type & task) = 0;
    virtual void updateTimeInterval(const timeint_type & timeInterval) = 0;

    virtual void addProject(const project_type & proj) = 0;
    virtual void addTaskItem(const task_type & task) = 0;
    virtual void addTimeInterval(const timeint_type & timeInterval) = 0;

    virtual void removeProjectItem(const project_type & proj) = 0;
    virtual void removeTaskItem(const task_type & task) = 0;
    virtual void removeTimeInterval(const timeint_type & timeInterval) = 0;
};

#endif // DATASTORAGEACCESSINTERFACE_H
