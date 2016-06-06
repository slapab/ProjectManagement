#include "TreeItemTimeInterval.h"

#include "TreeItemTask.h"

TreeItemTimeInterval::TreeItemTimeInterval(const timeint_ptr_type & timeIntItem, TreeItemInterface * parent)
    : TreeItemBase(parent)
    , m_TimeIntervalItem(timeIntItem)
{
    const auto & tasks = m_TimeIntervalItem->getTasksContainer();

    for (const auto & item : tasks)
    {
        m_Childs.push_back(std::make_unique<TreeItemTask>(item /*Reference to object within external container*/
                                                        , this /*this class is a parent*/));
    }
}


QVariant TreeItemTimeInterval::data(int column) const
{
    return QVariant(m_TimeIntervalItem->getName());
}


