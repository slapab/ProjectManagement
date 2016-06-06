#ifndef TREEITEMROOT_H
#define TREEITEMROOT_H

#include "TreeItemBase.h"
#include "DataStorageAccessInterface.h"

#include <QList>
#include <QVariant>

class TreeItemRoot : public TreeItemBase
{
public:
    using ProjectsContainerType = DataStorageAccessInterface::ProjectsContainerType;

    explicit TreeItemRoot(const ProjectsContainerType & projects, QList<QVariant> && data);

    // TreeItemInterface interface
public:
    QVariant data(int column) const override;


private:
    const ProjectsContainerType & m_ProjectsContainer;
    QList<QVariant> m_RootData;
};

#endif // TREEITEMROOT_H
