#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <memory>   // std::unique_ptr

#include "ProjectItemInterface.h"
#include "TimeInterval.h"


class ProjectItem : public virtual ProjectItemInterface
{
public:
    ProjectItem(int id, QString name, QString description, QDate beginDate, QDate endDate);
    //todo copy, move and assignment operator
    virtual ~ProjectItem();


    // Implements ProjectItemInterface interface
public:
    void    setBeginDate(QDate beginDate) override;
    void    setEndDate(QDate endDate) override;
    void    setDescription(QString descr) override;
    void    setName(QString name) override;

    QString getDescription() const override;
    QString getName() const override;
    int     getID() const override;
    std::pair<QDate, QDate> getDates() const override;

    void    setTimeIntervalsContainer(TimeIntervalsContainerType && storage) override;
    void    addTimeInterval(std::unique_ptr<TimeInterval> item) override;
    void    removeTimeInterval(int id) override;
    const TimeIntervalsContainerType & getTimeIntervalsContainer() const override;



protected:
    int     m_ID;
    QString m_Name;
    QString m_Description;
    QDate   m_CreationDate;
    QDate   m_EndDate;

    TimeIntervalsContainerType m_TimeIntervals;


};

#endif // PROJECTITEM_H
