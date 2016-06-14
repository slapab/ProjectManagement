#ifndef TASKITEMINTERFACE_H
#define TASKITEMINTERFACE_H

#include <QString>
#include <QDateTime>

#include <ItemInterface.h>


enum class TaskPriority
{
    Low = 1,
    Normal,
    Urgent
};


enum class TaskState
{
    Originated = 1, /// Default state on task creation.
    Investigation,  /// Task is being investigated.
    Blocked,        /// Task can not be accomplished because something it blocks.
    InProgress,     /// Work on task is in progress.
    Done            /// Task has been completed.
};


/**
*   \brief              This an interface for task item.
*/
class TaskItemInterface : public ItemInterface
{
public:
    virtual ~TaskItemInterface() = default;
    TaskItemInterface() = default;

    TaskItemInterface(const TaskItemInterface &) = default;
    TaskItemInterface & operator=(const TaskItemInterface &) = default;

    TaskItemInterface(TaskItemInterface &&) = default;
    TaskItemInterface & operator=(TaskItemInterface &&) = default;

    /**
    *   \brief          Provides way to change the task priority.
    *   \param priority the priority value which must be one of these defined in \ref TaskPriority enum.
    */
    virtual void setPriority(TaskPriority priority) = 0;

    /**
    *   \brief          Provides way to change the task state.
    *   \param state    the state value which must be one of these defined in \ref TaskState enum.
    */
    virtual void setState(TaskState state) = 0;

    /**
    *   \brief          Returns interval time ID to which task is assigned to. This ID represents
    *                   the primary key in database.
    *   \return         Interval time ID to which task is assigned to.
    */
    virtual int getIntervalID() const = 0;

    /**
    *   \brief          Returns task priority.
    *   \return         Value of \ref TaskPriority enum.
    */
    virtual TaskPriority getPriority() const = 0;

    /**
    *   \brief          Returns task state.
    *   \return         Value of \ref TaskState enum.
    */
    virtual TaskState getState() const = 0;

};

#endif // TASKITEMINTERFACE_H
