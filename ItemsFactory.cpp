#include "ItemsFactory.h"
#include "ProjectItem.h"
#include "TimeInterval.h"

ItemsFactory::ItemsFactory()
    : ItemsFactoryInterface()
{}

ItemsFactory::~ItemsFactory()
{}

std::unique_ptr<ProjectItemInterface> ItemsFactory::GetProject(QString name, QString descr, QDate date)
{
    return std::make_unique<ProjectItem>(std::move(name), std::move(descr), std::move(date));
}

std::unique_ptr<ProjectItemInterface> ItemsFactory::GetProject()
{
    return std::make_unique<ProjectItem>();
}

std::unique_ptr<TimeIntervalInterface> ItemsFactory::GetTimeInterval(QString name, QDateTime beginDate, QDateTime endDate)
{
    return std::make_unique<TimeInterval>(std::move(name), std::move(beginDate), std::move(endDate));
}

std::unique_ptr<TimeIntervalInterface> ItemsFactory::GetTimeInterval()
{
    return std::make_unique<TimeInterval>();
}
