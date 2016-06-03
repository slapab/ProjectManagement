#include "TaskItem.h"

TaskItem::TaskItem(int id, int intervalID, TaskPriority priority, TaskState state, QString name, QString description, QDateTime beginDate, QDateTime endDate)
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
    if (false == name.isEmpty())
    {
        m_Name = std::move(name);
    }
}

void TaskItem::setDescription(QString description)
{
    if (false == description.isEmpty())
    {
        m_Description = std::move(description);
    }
}

void TaskItem::setBeginDate(QDateTime beginDate)
{
    m_BeginDate = std::move(beginDate);
}

void TaskItem::setEndDate(QDateTime endDate)
{
    m_EndDate = std::move(endDate);
}

void TaskItem::setPriority(TaskPriority priority)
{
    m_Priority = priority;
}

void TaskItem::setState(TaskState state)
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

TaskPriority TaskItem::getPriority() const
{
    return m_Priority;
}

TaskState TaskItem::getState() const
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

std::pair<QDateTime, QDateTime> TaskItem::getDates() const
{
    return std::make_pair(m_BeginDate, m_EndDate);
}

