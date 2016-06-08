#include <algorithm>
#include "TreeItemProject.h"

#include "TreeItemTimeInterval.h"

TreeItemProject::TreeItemProject(const project_ptr_type & projItem, TreeItemInterface * parent)
    : TreeItemBase(parent)
    , m_ProjectItem(projItem)
{
    auto & timeIntervals = projItem->getTimeIntervalsContainer();

    for (const auto & item : timeIntervals)
    {
         m_Childs.push_back(std::make_unique<TreeItemTimeInterval>(item, this));
    }
}

QVariant TreeItemProject::data(int column) const
{
    return QVariant(m_ProjectItem->getName());
}

ItemInterface & TreeItemProject::getUnderlaidData()
{
    return *m_ProjectItem.get();
}

