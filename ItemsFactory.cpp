#include "ItemsFactory.h"
#include "ProjectItem.h"

ItemsFactory::ItemsFactory()
    : ItemsFactoryInterface()
{}

ItemsFactory::~ItemsFactory()
{}

std::unique_ptr<ProjectItemInterface> ItemsFactory::GetProject(const QString name, const QString descr, const QDate date)
{
    return std::make_unique<ProjectItem>(std::move(name), std::move(descr), std::move(date));
}

std::unique_ptr<ProjectItemInterface> ItemsFactory::GetProject()
{
    return std::make_unique<ProjectItem>();
}
