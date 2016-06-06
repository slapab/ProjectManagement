#ifndef TREEITEMTASK_H
#define TREEITEMTASK_H

#include "TreeItemBase.h"

#include "TimeIntervalInterface.h" // get the task potr_type and TaskContainer Type

using task_ptr_type = TimeIntervalInterface::task_ptr_type;

class TreeItemTask : public TreeItemBase
{
public:
    explicit TreeItemTask(const task_ptr_type & taskItem, TreeItemInterface * parent);


    // TreeItemInterface interface
public:
    QVariant data(int column) const override;


private:
    const task_ptr_type & m_TaskItem;
};

#endif // TREEITEMTASK_H
