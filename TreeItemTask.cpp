#include "TreeItemTask.h"

TreeItemTask::TreeItemTask(const task_ptr_type & taskItem, TreeItemInterface * parent)
    : TreeItemBase(parent)
    , m_TaskItem(taskItem)
{
    // Task item haven't children
}

QVariant TreeItemTask::data(int column) const
{
    return QVariant(m_TaskItem->getName());
}

ItemInterface & TreeItemTask::getUnderlaidData()
{
    return *m_TaskItem.get();
}
