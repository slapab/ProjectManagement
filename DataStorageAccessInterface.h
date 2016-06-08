#ifndef DATASTORAGEACCESSINTERFACE_H
#define DATASTORAGEACCESSINTERFACE_H

#include <vector>
#include <memory>   // std::unique_ptr

#include "ProjectItemInterface.h"
#include "TaskItemInterface.h"
#include "TimeIntervalInterface.h"

#include <QString>

/**
*   \brief  Interface which represents the public API to getting data from local or remote
*           data storage. The class which implements this interface must connect to this data
*           storage and retrieve desired information and returns container with read data.
*/
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


    /**
    *   \brief  Opens data storage to has access to read, write and update.
    */
    virtual void open() = 0;

    /**
    *   \brief Closes data storage.
    */
    virtual void close() = 0;

    /**
    *   \brief  Returns container with allocated on heap objects that represents
    *           project items read from data storage. Returned projects objects
    *           don't have attached time intervals and tasks that are assigned to it.
    *   \note   This method transfers ownership of allocated objects. These objects
    *           are managed by unique_ptr.
    */
    virtual ProjectsContainerType getAllProjects() = 0;

    /**
    *   \brief  Returns container with allocated on heap objects that represents
    *           task items belongs to given time interval - referenced by passed
    *           input parameter.
    *   \note   This method transfers ownership of allocated objects. These objects
    *           are managed by unique_ptr.
    *   \param timeInterval reference to time interval which tasks need to be read.
    */
    virtual TasksContainerType getTasks(const timeint_ptr_type & timeInterval) = 0;

    /**
    *   \brief  Returns container with allocated on heap objects that represents
    *           time interval items belongs to given project referenced by passed
    *           input parameter. Returned time intervals don't have attached tasks
    *           that are assigned to these time intervals.
    *   \note   This method transfers ownership of allocated objects. These objects
    *           are managed by unique_ptr.
    *   \param proj reference to project which time intervals need to be read.
    */
    virtual TimeIntContainerType getTimeIntervals(const project_ptr_type & proj) = 0;

    /**
    *   \brief  Performs project's data update in data storage. The data to be updated
    *           are stored inside pointer to project item object passed by reference.
    */
    virtual void updateProject(const project_ptr_type & proj) = 0; //TODO remove this (cppiso standard)
    virtual void updateProject(const ProjectItemInterface * proj) = 0;

    /**
    *   \brief  Performs task's data update in data storage. The data to be updated
    *           are stored inside pointer to task item object passed by reference.
    */
    virtual void updateTaskItem(const task_ptr_type & task) = 0; //TODO remove this (cppiso standard)
    virtual void updateTaskItem(const TaskItemInterface * task) = 0;

    /**
    *   \brief  Performs time interval's data update in data storage. The data to be updated
    *           are stored inside pointer to time interval item object passed by reference.
    */
    virtual void updateTimeInterval(const timeint_ptr_type & timeInterval) = 0; //TODO remove this (cppiso standard)
    virtual void updateTimeInterval(const TimeIntervalInterface * timeInterval) = 0;

    /**
    *   \brief  Adds new project data to data storage and returns the object filled with
    *           these data.
    *   \note   This method transfers ownership of allocated object. This object is 
    *           managed by unique_ptr.
    */
    virtual project_ptr_type addProject(QString name, QString descr, QDateTime beginDate, QDateTime endDate) = 0;
    
    /**
    *   \brief  Adds new task data to data storage and returns the object filled with
    *           these data.
    *   \note   This method transfers ownership of allocated object. This object is
    *           managed by unique_ptr.
    */
    virtual task_ptr_type addTaskItem(
            int intervalID, TaskPriority priority,
            TaskState state, QString name,
            QString descr, QDateTime beginDate, QDateTime endDate) = 0;

    /**
    *   \brief  Adds new time interval data to data storage and returns the object filled with
    *           these data.
    *   \note   This method transfers ownership of allocated object. This object is
    *           managed by unique_ptr.
    */
    virtual timeint_ptr_type addTimeInterval(int projectID, QString name, QString description, QDateTime beginDate, QDateTime endDate) = 0;

    /**
    *   \brief Removes project data from data storage.
    *   \param proj reference to pointer to object of project item which need to be deleted.
    */
    virtual void removeProjectItem(const project_ptr_type & proj) = 0;

    /**
    *   \brief Removes task data from data storage.
    *   \param task reference to pointer to object of task item which need to be deleted.
    */
    virtual void removeTaskItem(const task_ptr_type & task) = 0;

    /**
    *   \brief Removes time interval data from data storage.
    *   \param timeInterval reference to pointer to object of project item which need to be deleted.
    */
    virtual void removeTimeInterval(const timeint_ptr_type & timeInterval) = 0;
};

#endif // DATASTORAGEACCESSINTERFACE_H
