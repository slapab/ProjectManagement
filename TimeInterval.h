#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include "TimeIntervalInterface.h"

class TimeInterval : public virtual TimeIntervalInterface
{
public:
    TimeInterval();
    TimeInterval(const QString name, const QDateTime beginDate, const QDateTime endDate);
    virtual ~TimeInterval();

    std::pair<QDateTime, QDateTime> GetDatesRange() const override;
    void setDatesRange(const QDateTime begin, const QDateTime end) override;
    void setBeginDate(const QDateTime begin) override;
    void setEndDate(const QDateTime end) override;
    void setName(const QString name) override;
    QString getName() const override;

protected:
    QString m_Name;
    QDateTime m_BeginDate;
    QDateTime m_EndDate;
};

#endif // TIMEINTERVAL_H
