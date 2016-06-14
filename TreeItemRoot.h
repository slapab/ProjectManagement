#ifndef TREEITEMROOT_H
#define TREEITEMROOT_H

#include "TreeItem.h"

#include <QList>
#include <QVariant>

class TreeItemRoot : public TreeItem
{
public:
    explicit TreeItemRoot(QList<QVariant> && data, DataStorageAccessInterface & dataAccessObject);

    // Custom implementation of TreeItem methods
public:
    QVariant data(int column) const override;
    ItemInterface & getUnderlaidData() override;


private:
    QList<QVariant> m_RootData;

};

#endif // TREEITEMROOT_H
