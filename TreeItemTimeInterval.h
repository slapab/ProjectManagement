#ifndef TREEITEMTIMEINTERVAL_H
#define TREEITEMTIMEINTERVAL_H

#include "TreeItemBase.h"
#include "TimeIntervalInterface.h"

using timeint_ptr_type = TimeIntervalInterface::timeint_ptr_type;

class TreeItemTimeInterval : public TreeItemBase
{
public:
    explicit TreeItemTimeInterval(const timeint_ptr_type & timeIntItem, TreeItemInterface * parent);

    // TreeItemInterface interface
public:
    QVariant data(int column) const override;

private:
    const timeint_ptr_type & m_TimeIntervalItem;

};

#endif // TREEITEMTIMEINTERVAL_H
