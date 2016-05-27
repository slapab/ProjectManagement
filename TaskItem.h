#ifndef TASKITEM_H
#define TASKITEM_H

#include "TaskItemInterface.h"

class TaskItem : public TaskItemInterface
{
public:
    TaskItem(int id, int intervalID, int priority, int state, QString name, QString description, QDateTime beginDate, QDateTime endDate);
    virtual ~TaskItem();

    // Implements TaskItemInterface interface:
public:
    void      setName(QString name) override;
    void      setDescription(QString description) override;
    void      setBeginDate(QDateTime beginDate) override;
    void      setEndDate(QDateTime endDate) override;
    void      setPriority(int priority) override;
    void      setState(int state) override;
    int       getID() const override;
    int       getIntervalID() const override;
    int       getPriority() const override;
    int       getState() const override;
    QString   getName() const override;
    QString   getDescription() const override;
    std::pair<QDateTime, QDateTime> getDateRange() const override;

protected:
    int       m_ID;
    int       m_IntervalID;
    int       m_Priority;
    int       m_State;
    QString   m_Name;
    QString   m_Description;
    QDateTime m_BeginDate;
    QDateTime m_EndDate;

};

#endif // TASKITEM_H
