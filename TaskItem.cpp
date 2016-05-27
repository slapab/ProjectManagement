#include "TaskItem.h"

TaskItem::TaskItem(int id, int intervalID, int priority, int state, QString name, QString description, QDateTime beginDate, QDateTime endDate)
    : m_ID(id)
    , m_IntervalID(intervalID)
    , m_Priority(priority)
    , m_State(state)
    , m_Name(std::move(name))
    , m_Description(std::move(description))
    , m_BeginDate(std::move(beginDate))
    , m_EndDate(std::move(endDate))
{}

TaskItem::~TaskItem()
{}

void TaskItem::setName(QString name)
{
    m_Name = std::move(name);
}

void TaskItem::setDescription(QString description)
{
    m_Description = std::move(description);
}

void TaskItem::setBeginDate(QDateTime beginDate)
{
    m_BeginDate = std::move(beginDate);
}

void TaskItem::setEndDate(QDateTime endDate)
{
    m_EndDate = std::move(endDate);
}

void TaskItem::setPriority(int priority)
{
    m_Priority = priority;
}

void TaskItem::setState(int state)
{
    m_State = state;
}

int TaskItem::getID() const
{
    return m_ID;
}

int TaskItem::getIntervalID() const
{
    return m_IntervalID;
}

int TaskItem::getPriority() const
{
    return m_Priority;
}

int TaskItem::getState() const
{
    return m_State;
}

QString TaskItem::getName() const
{
    return m_Name;
}

QString TaskItem::getDescription() const
{
    return m_Description;
}

std::pair<QDateTime, QDateTime> TaskItem::getDateRange() const
{
    return std::make_pair(m_BeginDate, m_EndDate);
}

