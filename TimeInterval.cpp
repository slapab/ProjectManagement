#include "TimeInterval.h"
#include <algorithm>        // std::find_if algorithm

TimeInterval::TimeInterval(int id, int projectID, QString name, QString description, QDateTime beginDate, QDateTime endDate)
    : TimeIntervalInterface()
    , m_ID(id)
    , m_ProjectID(projectID)
    , m_Name(std::move(name))
    , m_Description(std::move(description))
    , m_BeginDate(std::move(beginDate))
    , m_EndDate(std::move(endDate))
{}

TimeInterval::~TimeInterval()
{}

std::pair<QDateTime, QDateTime> TimeInterval::GetDates() const
{
    return std::pair<QDateTime, QDateTime>(m_BeginDate, m_EndDate);
}

void TimeInterval::setTasksContainer(TimeIntervalInterface::TasksContainerType && container)
{
    m_Tasks = std::move(container);
}

void TimeInterval::addTask(std::unique_ptr<TaskItem> item)
{
    m_Tasks.push_back(std::move(item));
}

void TimeInterval::removeTask(int id)
{
    // predictate lambda for searching element with given ID
    auto predictate = [&](const auto & item) -> bool
    {
        return item->getID() == id;
    };

    // start searching
    auto it = std::find_if(m_Tasks.begin(), m_Tasks.end(), predictate);

    // if found, then delete it from the vector
    if (m_Tasks.end() != it)
    {
        m_Tasks.erase(it);
    }
}

const TimeIntervalInterface::TasksContainerType & TimeInterval::getTasksContainer() const
{
    return m_Tasks;
}

void TimeInterval::setBeginDate(QDateTime beginDate)
{
    m_BeginDate = std::move(beginDate);
}

void TimeInterval::setEndDate(QDateTime endDate)
{
    m_EndDate = std::move(endDate);
}

void TimeInterval::setName(QString name)
{
    m_Name = std::move(name);
}

void TimeInterval::setDescription(QString description)
{
    m_Description = std::move(description);
}

QString TimeInterval::getName() const
{
    return m_Name;
}

QString TimeInterval::getDescription() const
{
    return m_Description;
}

int TimeInterval::getProjectID() const
{
    return m_ProjectID;
}

int TimeInterval::getID() const
{
    return m_ID;
}
