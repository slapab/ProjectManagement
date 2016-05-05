#include "ProjectItem.h"

ProjectItem::ProjectItem()
    : ProjectItemInterface()
{}

ProjectItem::ProjectItem(const QString name, const QDate date)
    : m_Name(std::move(name))
    , m_CreationDate(std::move(date))
{}

ProjectItem::ProjectItem(const QString name, const QString descr, const QDate date)
    : m_Name(std::move(name))
    , m_Description(std::move(descr))
    , m_CreationDate(std::move(date))
{}

ProjectItem::~ProjectItem()
{}

void ProjectItem::setDate(const QDate date)
{
    m_CreationDate = std::move(date);
}

QDate ProjectItem::getDate() const
{
    return m_CreationDate;
}

void ProjectItem::setDescription(const QString descr)
{
    m_Description = std::move(descr);
}

QString ProjectItem::getDescription() const
{
    return m_Description;
}

void ProjectItem::setName(const QString name)
{
    m_Name = std::move(name);
}

QString ProjectItem::getName() const
{
    return m_Name;
}

