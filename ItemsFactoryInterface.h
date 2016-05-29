#ifndef ITEMSFACTORYINTERFACE_H
#define ITEMSFACTORYINTERFACE_H

#include <memory>   //unique_ptr
#include "ProjectItemInterface.h"
#include "TimeIntervalInterface.h"

class ItemsFactoryInterface
{
public:
    ItemsFactoryInterface() = default;
    virtual ~ItemsFactoryInterface() {}


    virtual std::unique_ptr<ProjectItemInterface> GetProject(QString name, QString descr, QDateTime date) = 0;
    virtual std::unique_ptr<ProjectItemInterface> GetProject() = 0;

    virtual std::unique_ptr<TimeIntervalInterface> GetTimeInterval(QString name, QDateTime beginDate, QDateTime endDate) = 0;
    virtual std::unique_ptr<TimeIntervalInterface> GetTimeInterval() = 0;

    // todo get TaskItem
};

#endif // ITEMSFACTORYINTERFACE_H
