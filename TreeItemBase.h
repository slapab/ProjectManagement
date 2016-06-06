#ifndef TREEITEMBASE_H
#define TREEITEMBASE_H

#include "TreeItemInterface.h"

class TreeItemBase : public TreeItemInterface
{
public:
    TreeItemBase(TreeItemInterface * parent);

    // TreeItemInterface interface
public:
    TreeItemInterface * child(int number) override;
    int childCount() const override;
    int columnCount() const override;
    int childNumber(const std::unique_ptr<TreeItemInterface> & child) const override;
    int childNumber(const TreeItemInterface * const child) const override;
    TreeItemInterface * parent() override;

protected:
    TreeItemInterface * m_pParent {nullptr};
    std::vector<std::unique_ptr<TreeItemInterface>> m_Childs; // auto delete


};

#endif // TREEITEMBASE_H
