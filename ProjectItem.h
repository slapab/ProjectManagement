#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <memory>   // std::unique_ptr

#include "ProjectItemInterface.h"
#include "TimeInterval.h"


class ProjectItem : public virtual ProjectItemInterface
{
public:
    virtual ~ProjectItem();

    ProjectItem(int id, QString name, QString description, QDateTime beginDate, QDateTime endDate);


    //todo copy, move and assignment operator



    // Implements ProjectItemInterface interface
public:
    void    setBeginDate(QDateTime beginDate) override;
    void    setEndDate(QDateTime endDate) override;
    void    setDescription(QString descr) override;
    void    setName(QString name) override;

    QString getDescription() const override;
    QString getName() const override;
    int     getID() const override;
    std::pair<QDateTime, QDateTime> getDates() const override;

    void    setTimeIntervalsContainer(TimeIntervalsContainerType && storage) override;
    void    addTimeInterval(timeint_ptr_type item) override;
    void    removeTimeInterval(int id) override;
    const TimeIntervalsContainerType & getTimeIntervalsContainer() const override;



protected:
    int       m_ID;
    QString   m_Name;
    QString   m_Description;
    QDateTime m_CreationDate;
    QDateTime m_EndDate;

    TimeIntervalsContainerType m_TimeIntervals;


};

#endif // PROJECTITEM_H
