#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include "TimeIntervalInterface.h"

class TimeInterval : public virtual TimeIntervalInterface
{
public:
    TimeInterval();
    TimeInterval(QString name, QDateTime beginDate, QDateTime endDate);
    virtual ~TimeInterval();

    std::pair<QDateTime, QDateTime> GetDatesRange() const override;
    void setDatesRange(QDateTime begin, QDateTime end) override;
    void setBeginDate(QDateTime begin) override;
    void setEndDate(QDateTime end) override;
    void setName(QString name) override;
    QString getName() const override;

protected:
    QString m_Name;
    QDateTime m_BeginDate;
    QDateTime m_EndDate;
};

#endif // TIMEINTERVAL_H
