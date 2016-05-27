#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include "TimeIntervalInterface.h"

class TimeInterval : public virtual TimeIntervalInterface
{
public:

    TimeInterval(int id, int projectID, QString name, QString description, QDateTime beginDate, QDateTime endDate);
    // todo: copy, move, assigment operator

    virtual ~TimeInterval();

    // Implements TimeInvervalInterface interface:
public:
    void setBeginDate(QDateTime begin) override;
    void setEndDate(QDateTime end) override;
    void setName(QString name) override;
    void setDescription(QString description) override;

    QString getName() const override;
    QString getDescription() const override;
    int  getProjectID() const override;
    int  getID() const override;
    std::pair<QDateTime, QDateTime> GetDates() const override;

    void setTasksContainer(TasksContainerType &&container) override;
    void addTask(std::unique_ptr<TaskItem> item) override;
    void removeTask(int id) override;
    const TasksContainerType & getTasksContainer() const override;


protected:
    int         m_ID;
    int         m_ProjectID;
    QString     m_Name;
    QString     m_Description;
    QDateTime   m_BeginDate;
    QDateTime   m_EndDate;

    TasksContainerType m_Tasks;
};

#endif // TIMEINTERVAL_H
