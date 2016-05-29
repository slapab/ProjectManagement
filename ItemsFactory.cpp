#include "ItemsFactory.h"
#include "ProjectItem.h"
#include "TimeInterval.h"

ItemsFactory::ItemsFactory()
    : ItemsFactoryInterface()
{}

ItemsFactory::~ItemsFactory()
{}

std::unique_ptr<ProjectItemInterface> ItemsFactory::GetProject(QString name, QString descr, QDateTime date)
{
    return std::make_unique<ProjectItem>(1, std::move(name), std::move(descr), std::move(date), QDateTime::currentDateTime());
}

std::unique_ptr<ProjectItemInterface> ItemsFactory::GetProject()
{
    return std::make_unique<ProjectItem>(1, "", "", QDateTime::currentDateTime(), QDateTime::currentDateTime());
}

std::unique_ptr<TimeIntervalInterface> ItemsFactory::GetTimeInterval(QString name, QDateTime beginDate, QDateTime endDate)
{
    return std::make_unique<TimeInterval>(1, 2, std::move(name), "", std::move(beginDate), std::move(endDate));
}

std::unique_ptr<TimeIntervalInterface> ItemsFactory::GetTimeInterval()
{
    return std::make_unique<TimeInterval>(1, 2, "", "", QDateTime::currentDateTime(), QDateTime::currentDateTime());
}
