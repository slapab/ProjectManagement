#ifndef ITEMSFACTORY_H
#define ITEMSFACTORY_H

#include "ItemsFactoryInterface.h"
#include "TimeIntervalInterface.h"

class ItemsFactory : public virtual ItemsFactoryInterface
{
public:
    ItemsFactory();
    virtual ~ItemsFactory();


    std::unique_ptr<ProjectItemInterface> GetProject(QString name, QString descr, QDate date) override;
    std::unique_ptr<ProjectItemInterface> GetProject() override;

    std::unique_ptr<TimeIntervalInterface> GetTimeInterval(QString name, QDateTime beginDate, QDateTime endDate) override;
    std::unique_ptr<TimeIntervalInterface> GetTimeInterval() override;

};

#endif // ITEMSFACTORY_H
