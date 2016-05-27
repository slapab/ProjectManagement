#ifndef TASKITEMINTERFACE_H
#define TASKITEMINTERFACE_H

#include <QString>
#include <QDateTime>
#include <utility> // std::pair

class TaskItemInterface
{
public:
    TaskItemInterface() {}
    virtual ~TaskItemInterface() {}

    virtual void setName(QString name) = 0;
    virtual void setDescription(QString description) = 0;
    virtual void setBeginDate(QDateTime beginDate) = 0;
    virtual void setEndDate(QDateTime endDate) = 0;
    virtual void setPriority(int priority) = 0;
    virtual void setState(int state) = 0;

    virtual int getID() const = 0;
    virtual int getIntervalID() const = 0;
    virtual int getPriority() const = 0;
    virtual int getState() const = 0;
    virtual QString getName() const = 0;
    virtual QString getDescription() const = 0;
    virtual std::pair<QDateTime, QDateTime> getDateRange() const = 0;

};

#endif // TASKITEMINTERFACE_H
