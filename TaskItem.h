#ifndef TASKITEM_H
#define TASKITEM_H

#include <QMap>
#include "TaskItemInterface.h"

/**
*   \brief  Task item implementation. Object of this type represents task.
*/

class TaskItem : public TaskItemInterface
{
public:
    static QMap<QString, TaskPriority> PRIORITY_STRINGS;
    static QMap<QString, TaskState>    STATE_STRINGS;

    virtual ~TaskItem();

    TaskItem(int id, int intervalID, TaskPriority priority, TaskState state, QString name, QString description, QDateTime beginDate, QDateTime endDate);

    TaskItem(const TaskItem &) = default;
    TaskItem & operator=(const TaskItem &) = default;

    TaskItem(TaskItem &&) = default;
    TaskItem & operator=(TaskItem &&) = default;


    // Implements TaskItemInterface interface:
public:
    void         setName(QString name) override;
    void         setDescription(QString description) override;
    void         setBeginDate(QDateTime beginDate) override;
    void         setEndDate(QDateTime endDate) override;
    void         setPriority(TaskPriority priority) override;
    void         setState(TaskState state) override;
    int          getID() const override;
    int          getIntervalID() const override;
    TaskPriority getPriority() const override;
    TaskState    getState() const override;
    QString      getName() const override;
    QString      getDescription() const override;
    std::pair<QDateTime, QDateTime> getDates() const override;




protected:
    int          m_ID;
    int          m_IntervalID;
    TaskPriority m_Priority;
    TaskState    m_State;
    QString      m_Name;
    QString      m_Description;
    QDateTime    m_BeginDate;
    QDateTime    m_EndDate;

};

#endif // TASKITEM_H
