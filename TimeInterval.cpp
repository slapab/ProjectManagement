#include "TimeInterval.h"

TimeInterval::TimeInterval()
{}

TimeInterval::TimeInterval(QString name, QDateTime beginDate, QDateTime endDate)
    : m_Name(std::move(name))
    , m_BeginDate(std::move(beginDate))
    , m_EndDate(std::move(endDate))
{}

TimeInterval::~TimeInterval()
{}

std::pair<QDateTime, QDateTime> TimeInterval::GetDatesRange() const
{
    return std::pair<QDateTime, QDateTime>(m_BeginDate, m_EndDate);
}

void TimeInterval::setDatesRange(QDateTime begin, QDateTime end)
{
    m_BeginDate = std::move(begin);
    m_EndDate = std::move(end);
}

void TimeInterval::setBeginDate(QDateTime begin)
{
    m_BeginDate = std::move(begin);
}

void TimeInterval::setEndDate(QDateTime end)
{
    m_EndDate = std::move(end);
}

void TimeInterval::setName(QString name)
{
    m_Name = std::move(name);
}

QString TimeInterval::getName() const
{
    return m_Name;
}

