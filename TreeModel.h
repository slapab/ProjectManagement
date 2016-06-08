#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "TreeItemInterface.h"

#include "DataStorageAccessInterface.h"


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    using ProjectsContainerType = DataStorageAccessInterface::ProjectsContainerType;
    using ptr_type = TreeItemInterface::ptr_type;

    explicit TreeModel(DataStorageAccessInterface & dataAccessObject);

    ~TreeModel() = default;

    static TreeItemInterface * GetInternalPointer(const QModelIndex & index);

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:

    ptr_type m_rootItem;
    DataStorageAccessInterface & m_DataAccessObject;

    // Holds data read from database. Model tree just reference these data.
    ProjectsContainerType m_DataHierarchy;
};

#endif // TREEMODEL_H
