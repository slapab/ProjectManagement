#ifndef ITEMSFACTORY_H
#define ITEMSFACTORY_H

#include "ItemsFactoryInterface.h"
#include "TimeIntervalInterface.h"

class ItemsFactory : public virtual ItemsFactoryInterface
{
public:
    ItemsFactory();
    virtual ~ItemsFactory();


    std::unique_ptr<ProjectItemInterface> GetProject(const QString name, const QString descr, const QDate date) override;
    std::unique_ptr<ProjectItemInterface> GetProject() override;

    std::unique_ptr<TimeIntervalInterface> GetTimeInterval(const QString name, const QDateTime beginDate, const QDateTime endDate) override;
    std::unique_ptr<TimeIntervalInterface> GetTimeInterval() override;

};

#endif // ITEMSFACTORY_H
