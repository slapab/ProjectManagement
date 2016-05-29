#include "ProjectItem.h"


ProjectItem::ProjectItem(int id, QString name, QString description, QDateTime beginDate, QDateTime endDate)
    : ProjectItemInterface()
    , m_ID(id)
    , m_Name(std::move(name))
    , m_Description(std::move(description))
    , m_CreationDate(std::move(beginDate))
    , m_EndDate(std::move(endDate))
    , m_TimeIntervals()
{}


ProjectItem::~ProjectItem()
{}

void ProjectItem::setBeginDate(QDateTime beginDate)
{
    m_CreationDate = std::move(beginDate);
}

void ProjectItem::setEndDate(QDateTime endDate)
{
    m_CreationDate = std::move(endDate);
}

std::pair<QDateTime, QDateTime> ProjectItem::getDates() const
{
    return std::make_pair(m_CreationDate, m_EndDate);
}

void ProjectItem::setTimeIntervalsContainer(ProjectItemInterface::TimeIntervalsContainerType &&storage)
{
    m_TimeIntervals = std::move(storage);
}

void ProjectItem::addTimeInterval(timeint_ptr_type item)
{
    m_TimeIntervals.push_back(std::move(item));
}

void ProjectItem::removeTimeInterval(int id)
{

    // predictate lambda for searching element with given ID
    // the item is TimeInterval
    auto predictate = [&](const auto & item) -> bool
    {
        return item->getID() == id;
    };

    auto it = std::find_if(m_TimeIntervals.begin(), m_TimeIntervals.end(), predictate);

    // if found, then delete it from the vector
    if (m_TimeIntervals.end() != it)
    {
        m_TimeIntervals.erase(it);
    }
}

const ProjectItem::TimeIntervalsContainerType & ProjectItem::getTimeIntervalsContainer() const
{
    return m_TimeIntervals;
}

void ProjectItem::setDescription(QString descr)
{
    m_Description = std::move(descr);
}

QString ProjectItem::getDescription() const
{
    return m_Description;
}

void ProjectItem::setName(QString name)
{
    m_Name = std::move(name);
}

QString ProjectItem::getName() const
{
    return m_Name;
}

int ProjectItem::getID() const
{
    return m_ID;
}

