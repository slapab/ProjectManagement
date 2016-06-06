#ifndef TREEITEMPROJECT_H
#define TREEITEMPROJECT_H

#include "TreeItemBase.h"
#include "DataStorageAccessInterface.h" //get the data containers type

using project_ptr_type = DataStorageAccessInterface::project_ptr_type;


class TreeItemProject : public TreeItemBase
{
public:
    explicit TreeItemProject(const project_ptr_type & projItem, TreeItemInterface * parent);

    // TreeItemInterface interface
public:
    QVariant data(int column) const override;

private:
    const project_ptr_type & m_ProjectItem;


};

#endif // TREEITEMPROJECT_H
