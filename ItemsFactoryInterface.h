#ifndef ITEMSFACTORYINTERFACE_H
#define ITEMSFACTORYINTERFACE_H

#include <memory>   //unique_ptr
#include "ProjectItemInterface.h"

class ItemsFactoryInterface
{
public:
    ItemsFactoryInterface() = default;
    virtual ~ItemsFactoryInterface() {}


    virtual std::unique_ptr<ProjectItemInterface> GetProject(const QString name, const QString descr, const QDate date) = 0;
    virtual std::unique_ptr<ProjectItemInterface> GetProject() = 0;

    // todo get IntervalTimeItem
    // todo get TaskItem
};

#endif // ITEMSFACTORYINTERFACE_H
