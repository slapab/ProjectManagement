#ifndef TASKITEMINTERFACE_H
#define TASKITEMINTERFACE_H

#include <QString>
#include <QDateTime>
#include <utility> // std::pair


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
class TaskItemInterface
{
public:
    virtual ~TaskItemInterface() = default;
    TaskItemInterface() = default;

    TaskItemInterface(const TaskItemInterface &) = default;
    TaskItemInterface & operator=(const TaskItemInterface &) = default;

    TaskItemInterface(TaskItemInterface &&) = default;
    TaskItemInterface & operator=(TaskItemInterface &&) = default;

    /**
    *   \brief          Provides way to change new name.
    *   \param name     new name string which can not be empty.
    */
    virtual void setName(QString name) = 0;

    /**
    *   \brief          Provides way to change new description.
    *   \param description  new description string which can not be empty.
    */
    virtual void setDescription(QString description) = 0;

    /**
    *   \brief          Provides way to change the begin date.
    *   \param beginDate    object which represents the begin date.
    */
    virtual void setBeginDate(QDateTime beginDate) = 0;

    /**
    *   \brief          Provides way to change the end date.
    *   \param endDate  object which represents the end date.
    */
    virtual void setEndDate(QDateTime endDate) = 0;

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
    *   \brief          Returns task ID. This ID represents the primary key in database.
    *   \return         Task ID.
    */
    virtual int getID() const = 0;

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

    /**
    *   \brief          Return task name.
    *   \return         String which represents task name.
    */
    virtual QString getName() const = 0;

    /**
    *   \brief          Return task description.
    *   \return         String which represents task description.
    */
    virtual QString getDescription() const = 0;

    /**
    *   \brief          Return task begin and end dates.
    *   \return         Pair of begin and end date. The first is begin date. The second is end date.
    */
    virtual std::pair<QDateTime, QDateTime> getDates() const = 0;

};

#endif // TASKITEMINTERFACE_H
