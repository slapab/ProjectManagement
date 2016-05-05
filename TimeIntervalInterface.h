#ifndef TIMEINTERVALINTERFACE_H
#define TIMEINTERVALINTERFACE_H

#include <QDateTime>
#include <QString>
#include <utility> //std::pair

class TimeIntervalInterface
{
public:
    TimeIntervalInterface() = default;
    virtual ~TimeIntervalInterface() {}

    virtual std::pair<QDateTime, QDateTime> GetDatesRange() const = 0;
    virtual void setDatesRange(const QDateTime begin, const QDateTime end) = 0;
    virtual void setBeginDate(const QDateTime begin) = 0;
    virtual void setEndDate(const QDateTime end) = 0;
    virtual void setName(const QString name) = 0;
    virtual QString getName() const = 0;

};

#endif // TIMEINTERVALINTERFACE_H
