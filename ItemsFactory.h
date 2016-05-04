#ifndef ITEMSFACTORY_H
#define ITEMSFACTORY_H

#include "ItemsFactoryInterface.h"

class ItemsFactory : public virtual ItemsFactoryInterface
{
public:
    ItemsFactory();
    virtual ~ItemsFactory();


    std::unique_ptr<ProjectItemInterface> GetProject(const QString name, const QString descr, const QDate date) override;
    std::unique_ptr<ProjectItemInterface> GetProject() override;
};

#endif // ITEMSFACTORY_H
