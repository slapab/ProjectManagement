#ifndef TREEITEM_H
#define TREEITEM_H

#include "TreeItemInterface.h"
#include "DataStorageAccessInterface.h"


class TreeItem : public TreeItemInterface
{
public:
    using project_ptr_type = DataStorageAccessInterface::project_ptr_type;
    using task_ptr_type = TimeIntervalInterface::task_ptr_type;
    using timeint_ptr_type = TimeIntervalInterface::timeint_ptr_type;
    
    explicit TreeItem(project_ptr_type projItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject);
    explicit TreeItem(task_ptr_type taskItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject);
    explicit TreeItem(timeint_ptr_type timeintItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject);
    
    virtual ~TreeItem() {}

    // TreeItemInterface interface
public:
    TreeItemInterface * child(int number) override;
    int childCount() const override;
    int columnCount() const override;
    int childNumber(const TreeItemInterface * const child) const override;
    TreeItemInterface * parent() override;
    TreeItemType getType() const override;
    virtual QVariant data(int column) const override;
    virtual ItemInterface & getUnderlaidData() override;

protected:
    // Constructor for derived root tree item
    TreeItem(TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject);


protected:
    const TreeItemType m_TreeItemType;
    TreeItemInterface * m_pParent {nullptr};
    std::vector<std::unique_ptr<TreeItemInterface>> m_Childs; // auto delete
    std::unique_ptr<ItemInterface> m_itemData;
    DataStorageAccessInterface & m_DataAccessObject;


};

#endif // TREEITEM_H
